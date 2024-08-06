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
drv_ir_t dir_sensor;
drv_ir_state_t dir_state;
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
  bsp_mcu_init(&bstmf411_init, &bstmf411);
  bsp_exti_init((BSP_GPIO_PORT_A << 4)|BSP_GPIO_PIN_2, BSP_EXTI_FALLING_RISING_EDGE);
  drv_ir_init(&dir_sensor);
  bsp_timer_init(&bstmf411);
  bsp_timer_register_callback(sch_update);
  bsp_timer_start(&bstmf411);
  

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
    dir_state = drv_ir_state(&dir_sensor);
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
