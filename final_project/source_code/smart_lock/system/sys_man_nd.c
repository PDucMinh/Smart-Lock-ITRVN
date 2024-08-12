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
