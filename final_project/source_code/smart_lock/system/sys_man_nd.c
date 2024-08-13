/**
 * @file       <file_name>.c
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    major.minor.patch
 * @date       yyyy-mm-dd
 * @author     Minh Pham Duc
 *
 * @brief      <A brief description of the content of the file>
 *
 * @note
 * @example    example_file_1.c
 *             Example_1 description
 * @example    example_file_2.c
 *             Example_2 description
 */

/* Includes ----------------------------------------------------------- */
#include "sys_man_nd.h"
#include "cmsis_compiler.h"
#include "bsp_mcu.h"
#include "bsp_gpio.h"
#include "bsp_timer.h"
#include "bsp_pwm.h"
#include "bsp_uart.h"
#include "scheduler.h" 
#include "bsp_exti.h" 

/* Private defines ---------------------------------------------------- */
#define SMAN_LCK_KEY 0xFF
/* Private enumerate/structure ---------------------------------------- */
typedef enum
{
  SYS_MANAGER_STATE_INIT,
  SYS_MANAGER_STATE_CLOSE,
  SYS_MANAGER_STATE_OPEN,
  SYS_MANAGER_STATE_DOUBLE_LOCK
} sys_manager_state_t;

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static uint8_t sys_manager_key = 0x11;
static uint8_t sys_manager_receive_key = 0x00;
static uint8_t sys_manager_timer_flag = 0;
static uint8_t sys_manager_wrong_pass_count = 0;

static drv_buzzer_t sys_manager_buzzer;
static drv_led_rgb_t sys_manager_led;
static drv_ir_t sys_manager_ir;

static sys_manager_state_t sys_manager_state;
/* Private function prototypes ---------------------------------------- */
void sys_manager_alarm(melody_t alarm_type);
void sys_manager_timer_run();
uint8_t sys_manager_check_flag();
uint8_t sys_manager_wrong_pass_threshold();
/* Function definitions ----------------------------------------------- */
void sys_manager_init(void)
{
  // init led
  // init uart
  // init buzzer
  // init ir
  // init pwm led
  // init timer scheduler
  bsp_mcu_t mcu;
  bsp_mcu_init_t mcu_init;
  mcu_init.is_tim2_used = BSP_MCU_PERIPH_TIM2;
  mcu_init.is_tim3_used = BSP_MCU_PERIPH_TIM3;
  mcu_init.is_tim4_used = BSP_MCU_PERIPH_TIM4;
  mcu_init.is_usart6_used = BSP_MCU_PERIPH_USART6_ASYNCH;
  bsp_mcu_init(&mcu_init, &mcu);
  bsp_uart_init(&mcu);
  bsp_timer_init(&mcu);
  bsp_pwm_init(&mcu);
  bsp_timer_register_callback(sch_add_task);
  bsp_gpio_pin_t ledr_pin, ledg_pin, ledb_pin;
  ledr_pin.io = (BSP_GPIO_PORT_B << 4) | BSP_GPIO_PIN_4;
  ledr_pin.mode = BSP_GPIO_AF_PP;
  ledr_pin.pull_type = BSP_GPIO_NOPULL;
  ledr_pin.speed = BSP_GPIO_FREQ_MEDIUM;
  ledr_pin.af = BSP_GPIO_AF2;
  bsp_gpio_pin_init(&ledr_pin);

  ledg_pin.io = (BSP_GPIO_PORT_B << 4) | BSP_GPIO_PIN_5;
  ledg_pin.mode = BSP_GPIO_AF_PP;
  ledg_pin.pull_type = BSP_GPIO_NOPULL;
  ledg_pin.speed = BSP_GPIO_FREQ_MEDIUM;
  ledg_pin.af = BSP_GPIO_AF2;
  bsp_gpio_pin_init(&ledg_pin);

  ledb_pin.io = (BSP_GPIO_PORT_B << 4) | BSP_GPIO_PIN_0;
  ledb_pin.mode = BSP_GPIO_AF_PP;
  ledb_pin.pull_type = BSP_GPIO_NOPULL;
  ledb_pin.speed = BSP_GPIO_FREQ_MEDIUM;
  ledb_pin.af = BSP_GPIO_AF2;
  bsp_gpio_pin_init(&ledb_pin);

  bsp_gpio_pin_t buzzer_pin;
  buzzer_pin.io = (BSP_GPIO_PORT_D << 4) | BSP_GPIO_PIN_12;
  buzzer_pin.mode = BSP_GPIO_AF_PP;
  buzzer_pin.pull_type = BSP_GPIO_NOPULL;
  buzzer_pin.speed = BSP_GPIO_FREQ_MEDIUM;
  buzzer_pin.af = BSP_GPIO_AF2;
  bsp_gpio_pin_init(&buzzer_pin);

  bsp_exti_init((BSP_GPIO_PORT_A << 4) | BSP_GPIO_PIN_2, BSP_EXTI_FALLING_EDGE);
  drv_buzzer_t dbuzzer;
  drv_buzzer_init(&dbuzzer);
  drv_ir_t dir_sensor;
  drv_ir_init(&dir_sensor);
  drv_led_rgb_t dled_rgb;
  drv_led_rgb_init(&dled_rgb);
  bsp_timer_start(&mcu);
}

void sys_manager_loop(void)
{
  switch (sys_manager_state)
  {
  case SYS_MANAGER_STATE_INIT:
    /* code */
    bsp_uart_receive_start(BSP_CONFIG_ID_PROTOCOL, &sys_manager_receive_key, 1);
    // melody_read(MELODY_ID_FOURTH_SONG); // alarm wrong pass
    sys_manager_state = SYS_MANAGER_STATE_CLOSE;
    break;
  case SYS_MANAGER_STATE_CLOSE:
    /* code */
    if (bsp_uart_receive_cplt(BSP_CONFIG_ID_PROTOCOL))
    {
      if (sys_manager_key == sys_manager_receive_key)
      {
        sys_manager_state = SYS_MANAGER_STATE_OPEN;
        sys_manager_alarm(melody_read(MELODY_ID_THIRD_SONG)); // alarm right pass
        bsp_uart_receive_start(BSP_CONFIG_ID_PROTOCOL, &sys_manager_key, 1);
        sch_add_task(&sys_manager_timer_run, 10000, 0);
      }
      else
      {
        sys_manager_state = SYS_MANAGER_STATE_INIT;
        if (sys_manager_wrong_pass_threshold())
        {
          sys_manager_state = SYS_MANAGER_STATE_DOUBLE_LOCK;
          sys_manager_alarm(melody_read(MELODY_ID_FIRST_SONG)); // alarm double lock
          sch_add_task(&sys_manager_timer_run, 5000, 0);
        }
        else
        {
          sys_manager_wrong_pass_count++;
          sys_manager_alarm(melody_read(MELODY_ID_FOURTH_SONG)); // alarm wrong pass
        }
      }
    }
    break;
  case SYS_MANAGER_STATE_OPEN:
    /* code */
    if (bsp_uart_receive_cplt(BSP_CONFIG_ID_PROTOCOL))
    {
      if (sys_manager_key == SMAN_LCK_KEY)
      {
        sys_manager_state = SYS_MANAGER_STATE_CLOSE;
        sys_manager_alarm(melody_read(MELODY_ID_THIRD_SONG)); // alarm close door
        bsp_uart_receive_start(BSP_CONFIG_ID_PROTOCOL, &sys_manager_key, 1);
      }
      else if (sys_manager_check_flag() && (drv_ir_state(&sys_manager_ir) == DRV_IR_STATE_NO_OBSTACLE))
      {
        sys_manager_state = SYS_MANAGER_STATE_OPEN;
        sys_manager_alarm(melody_read(MELODY_ID_SECOND_SONG)); // alarm not close
      }
    }
    break;
  case SYS_MANAGER_STATE_DOUBLE_LOCK:
    if (sys_manager_check_flag())
    {
      sys_manager_state = SYS_MANAGER_STATE_INIT;
      sys_manager_alarm(melody_read(MELODY_ID_THIRD_SONG)); // alarm out of double lock
    }
    break;
  default:
    sys_manager_state = SYS_MANAGER_STATE_INIT;
    break;
  }
}
/* Private definitions ----------------------------------------------- */
void sys_manager_alarm(melody_t alarm_type)
{
  // play melody
  // set led color
  // set buzzer
  do
  {

  } while (drv_buzzer_duration_cplt(&sys_manager_buzzer) == 0);
}

void sys_manager_timer_run()
{
  sys_manager_timer_flag = 1;
}

uint8_t sys_manager_check_flag()
{
  if (sys_manager_timer_flag)
  {
    sys_manager_timer_flag = 0;
    return 1;
  }
  return 0;
}
uint8_t sys_manager_wrong_pass_threshold()
{
  if (sys_manager_wrong_pass_count >= 3)
  {
    sys_manager_wrong_pass_count = 0;
    return 1;
  }
  return 0;
}
/* End of file -------------------------------------------------------- */
