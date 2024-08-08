/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
bsp_mcu_t bstmf411;
drv_led_rgb_t dled_rgb;
bsp_gpio_pin_t bled_pin_r;
bsp_gpio_pin_t bled_pin_g;
bsp_gpio_pin_t bled_pin_b;
bsp_gpio_pin_t bbuzzer_pin;
bsp_gpio_pin_t brtc_scl;
bsp_gpio_pin_t brtc_sda;
drv_ir_t dir_sensor;
drv_buzzer_t dbuzzer;
drv_ir_state_t dir_state;
drv_rtc_t ds1307;
drv_rtc_time_t time_tx = {.date = 7, .day = 4, .hour = 11, .minute = 14, .month = 8, .second = 50, .year = 24};
drv_rtc_time_t time_rx;
melody_t first_song;
uint8_t flag = 0;
uint8_t index_song = 0;
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
  bsp_mcu_init_t bstmf411_init;
  // bstmf411_init.is_tim3_used = BSP_MCU_PERIPH_TIM3;
  bstmf411_init.is_tim2_used = BSP_MCU_PERIPH_TIM2;
//  bstmf411_init.is_tim4_used = BSP_MCU_PERIPH_TIM4;
  bstmf411_init.is_i2c2_used = BSP_MCU_PERIPH_I2C2;
  bsp_mcu_init(&bstmf411_init, &bstmf411);

//  bbuzzer_pin.io = (BSP_GPIO_PORT_D << 4) | BSP_GPIO_PIN_12;
//  bbuzzer_pin.mode = BSP_GPIO_AF_PP;
//  bbuzzer_pin.af = BSP_GPIO_AF2;
//  bbuzzer_pin.pull_type = BSP_GPIO_NOPULL;
//  bbuzzer_pin.speed = BSP_GPIO_FREQ_LOW;
//  bsp_gpio_pin_init(&bbuzzer_pin);
  brtc_scl.io = (BSP_GPIO_PORT_B << 4) | BSP_GPIO_PIN_10;
  brtc_scl.mode = BSP_GPIO_AF_OD;
  brtc_scl.af = BSP_GPIO_AF4;
  brtc_scl.pull_type = BSP_GPIO_NOPULL;
  brtc_scl.speed = BSP_GPIO_FREQ_LOW;
  bsp_gpio_pin_init(&brtc_scl);

  brtc_sda.io = (BSP_GPIO_PORT_B << 4) | BSP_GPIO_PIN_3;
  brtc_sda.mode = BSP_GPIO_AF_OD;
  brtc_sda.af = BSP_GPIO_AF9;
  brtc_sda.pull_type = BSP_GPIO_NOPULL;
  brtc_sda.speed = BSP_GPIO_FREQ_LOW;
  bsp_gpio_pin_init(&brtc_sda);

  // bsp_pwm_init(&bstmf411);
  bsp_timer_init(&bstmf411);
  bsp_timer_register_callback(sch_update);
  bsp_i2c_init(&bstmf411);
  drv_rtc_init(&ds1307);
  bsp_timer_start(&bstmf411);
  drv_rtc_write(&ds1307, time_tx);
  // drv_buzzer_init(&dbuzzer);
  // drv_buzzer_active(&dbuzzer);
  // first_song = melody_read(MELODY_ID_SECOND_SONG);
  /* bsp_exti_init((BSP_GPIO_PORT_A << 4)|BSP_GPIO_PIN_2, BSP_EXTI_FALLING_RISING_EDGE);
  drv_ir_init(&dir_sensor);
  bsp_timer_init(&bstmf411);
  bsp_timer_register_callback(sch_update);
  bsp_timer_start(&bstmf411); */

  /* bled_pin_r.af = BSP_GPIO_AF2;
  bled_pin_r.io = (BSP_GPIO_PORT_B << 4) | BSP_GPIO_PIN_4;
  bled_pin_r.mode = BSP_GPIO_AF_PP;
  bled_pin_r.pull_type = BSP_GPIO_NOPULL;
  bled_pin_r.speed = BSP_GPIO_FREQ_HIGH;
  bsp_gpio_pin_init(&bled_pin_r);

  bled_pin_g.af = BSP_GPIO_AF2;
  bled_pin_g.io = (BSP_GPIO_PORT_B << 4) | BSP_GPIO_PIN_5;
  bled_pin_g.mode = BSP_GPIO_AF_PP;
  bled_pin_g.pull_type = BSP_GPIO_NOPULL;
  bled_pin_g.speed = BSP_GPIO_FREQ_HIGH;
  bsp_gpio_pin_init(&bled_pin_g);

  bled_pin_b.af = BSP_GPIO_AF2;
  bled_pin_b.io = (BSP_GPIO_PORT_B << 4) | BSP_GPIO_PIN_0;
  bled_pin_b.mode = BSP_GPIO_AF_PP;
  bled_pin_b.pull_type = BSP_GPIO_NOPULL;
  bled_pin_b.speed = BSP_GPIO_FREQ_HIGH;
  bsp_gpio_pin_init(&bled_pin_b);

  bsp_pwm_init(&bstmf411);
  drv_led_rgb_init(&dled_rgb);
  drv_led_rgb_set(&dled_rgb, DRV_LED_RGB_ORANGE); */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    sch_dispatch_task();
    if (ds1307.i2c_write_cplt(BSP_CONFIG_ID_RTC) == 1)
    {
    	drv_rtc_read_start(&ds1307);
    }
    if (ds1307.i2c_read_cplt(BSP_CONFIG_ID_RTC) == 1)
    {
        time_rx = drv_rtc_read_complete(&ds1307);
    }
    // if (flag == 0)
    // {
    //   drv_buzzer_set_note(&dbuzzer, first_song.pnote_array[index_song].note_freq, first_song.pnote_array[index_song].duration_ms);
    //   flag = 1;
    // }
    // if (drv_buzzer_duration_cplt(&dbuzzer))
    // {
    // 	index_song++;
    //   flag = 0;
    // 	if(index_song == first_song.size)
    // 	{
    // 		index_song = first_song.size;
    //     flag = 1;
    // 	}
    // }
    
    // dir_state = drv_ir_state(&dir_sensor);
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
