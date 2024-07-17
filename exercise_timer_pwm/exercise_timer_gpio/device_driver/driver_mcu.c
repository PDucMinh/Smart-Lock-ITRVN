/**
 * @file       driver_mcu.c
 * @copyright
 * @license
 * @version
 * @date       2024-07-07
 * @author     <first_name_1> <last_name_1>
 * @author     <first_name_2> <last_name_2>
 *
 * @brief      This file include the following function:
 *             - driver_mcu_init() < This function initialize stm32f4 mcu'system
 *                                   include flash function, clock function >
 *
 * @note
 * @example
 *
 */

/* Includes ----------------------------------------------------------- */
#include "driver_mcu.h"

/* Private defines ---------------------------------------------------- */
#define DRIVER_MCU_NUM_PORT (5)
#define DRIVER_MCU_NUM_PIN (16)
/* Private enumerate/structure ---------------------------------------- */
/**
 * @brief <the state of being used of MCU's pin>
 */
typedef enum
{
  DRIVER_MCU_PIN_STATE_FREE,  /**< This pin is not initialized by any module */
  DRIVER_MCU_PIN_STATE_USED,  /**< This pin is initialized by another module */
  DRIVER_MCU_PIN_STATE_UNUSED /**< This pin is not allowed to be used        */
} driver_mcu_pin_state_t;
/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static driver_mcu_pin_state_t v_dmcu_pin_list[DRIVER_MCU_NUM_PORT][DRIVER_MCU_NUM_PIN] = 
{
                 /* MCU_PIN0               | MCU_PIN1                 | MCU_PIN2                 | MCU_PIN3                 | MCU_PIN4                 | MCU_PIN5                 | MCU_PIN6                 | MCU_PIN7                 | MCU_PIN8                 | MCU_PIN9                 | MCU_PIN10                | MCU_PIN11                  | MCU_PIN12                | MCU_PIN13                | MCU_PIN14                | MCU_PIN15 */
  /* MCU_PORTA */{DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_UNUSED, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE},
  /* MCU_PORTB */{DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_UNUSED, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE},
  /* MCU_PORTC */{DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE  , DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE},
  /* MCU_PORTD */{DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE  , DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE},
  /* MCU_PORTE */{DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE  , DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE, DRIVER_MCU_PIN_STATE_FREE}
};
/* Private function prototypes ---------------------------------------- */
/**
 * @brief  <function description>
 *
 * @param[in]     <param_name>  <param_despcription>
 * @param[out]    <param_name>  <param_despcription>
 * @param[inout]  <param_name>  <param_despcription>
 *
 * @attention  <API attention note>
 *
 * @return
 *  - 0: Success
 *  - 1: Error
 */
driver_state_t driver_mcu_clock_init(void);
driver_state_t driver_mcu_pwm_init(driver_mcu_t *v_dmcu);
driver_state_t driver_mcu_timer_init(driver_mcu_t *v_dmcu);
/* Function definitions ----------------------------------------------- */
driver_state_t driver_mcu_init(driver_mcu_t *v_dmcu)
{
  DRIVER_CHECK_NULL(v_dmcu, DRIVER_STATE_FAIL);
  HAL_Init();
  if (driver_mcu_clock_init() == DRIVER_STATE_FAIL)
  {
    return DRIVER_STATE_FAIL;
  }
  if (driver_mcu_timer_init(v_dmcu) == DRIVER_STATE_FAIL)
  {
    return DRIVER_STATE_FAIL;
  }
  if (driver_mcu_pwm_init(v_dmcu) == DRIVER_STATE_FAIL)
  {
    return DRIVER_STATE_FAIL;
  }
  return DRIVER_STATE_PASS;
}
/* Private definitions ----------------------------------------------- */
driver_state_t driver_mcu_clock_init(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
   */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    return DRIVER_STATE_FAIL;
  }

  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType =
      RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    return DRIVER_STATE_FAIL;
  }
  return DRIVER_STATE_PASS;
}

driver_state_t driver_mcu_timer_init(driver_mcu_t *v_dmcu)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  v_dmcu->htim3.Instance = TIM3;
  v_dmcu->htim3.Init.Prescaler = 99;
  v_dmcu->htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  v_dmcu->htim3.Init.Period = 999;
  v_dmcu->htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  v_dmcu->htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&(v_dmcu->htim3)) != HAL_OK)
  {
    return DRIVER_STATE_FAIL;
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&(v_dmcu->htim3), &sClockSourceConfig) != HAL_OK)
  {
    return DRIVER_STATE_FAIL;
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&(v_dmcu->htim3), &sMasterConfig) != HAL_OK)
  {
    return DRIVER_STATE_FAIL;
  }
  HAL_TIM_Base_Start_IT(&(v_dmcu->htim3));
  return DRIVER_STATE_PASS;
}

driver_state_t driver_mcu_pwm_init(driver_mcu_t *v_dmcu)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  v_dmcu->htim4.Instance = TIM4;
  v_dmcu->htim4.Init.Prescaler = 999;
  v_dmcu->htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  v_dmcu->htim4.Init.Period = 99;
  v_dmcu->htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  v_dmcu->htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&(v_dmcu->htim4)) != HAL_OK)
  {
    return DRIVER_STATE_FAIL;
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&(v_dmcu->htim4), &sClockSourceConfig) != HAL_OK)
  {
    return DRIVER_STATE_FAIL;
  }
  if (HAL_TIM_PWM_Init(&(v_dmcu->htim4)) != HAL_OK)
  {
    return DRIVER_STATE_FAIL;
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&(v_dmcu->htim4), &sMasterConfig) != HAL_OK)
  {
    return DRIVER_STATE_FAIL;
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&(v_dmcu->htim4), &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    return DRIVER_STATE_FAIL;
  }
  if (HAL_TIM_PWM_ConfigChannel(&(v_dmcu->htim4), &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    return DRIVER_STATE_FAIL;
  }
  if (HAL_TIM_PWM_ConfigChannel(&(v_dmcu->htim4), &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    return DRIVER_STATE_FAIL;
  }
  return DRIVER_STATE_PASS;
}

driver_state_t driver_mcu_pin_init(driver_mcu_pin_t *v_dpin)
{
  DRIVER_CHECK_NULL(v_dpin, DRIVER_STATE_FAIL);
  uint16_t port, pin;
  port = ((v_dpin->io) & 0xF0) >> 4;
  pin = (v_dpin->io) & 0x0F;
  if(v_dmcu_pin_list[port][pin] != DRIVER_MCU_PIN_STATE_FREE)
  {
    return DRIVER_STATE_FAIL;
  }
  else
  {
    v_dmcu_pin_list[port][pin] = DRIVER_MCU_PIN_STATE_USED;
  }
  GPIO_InitTypeDef GPIO_InitStruct = { 0 };
  GPIO_InitStruct.Pin = (uint16_t)1 << pin;
  GPIO_InitStruct.Mode = v_dpin->mode;
  GPIO_InitStruct.Pull = v_dpin->pull_type;
  GPIO_InitStruct.Speed = v_dpin->speed;
  GPIO_InitStruct.Alternate = v_dpin->af;
  switch(port)
  {
    case DRIVER_MCU_PORT_A:
    {
      __HAL_RCC_GPIOA_CLK_ENABLE();
      HAL_GPIO_Init(GPIOA,&GPIO_InitStruct);
      break;
    }
    case DRIVER_MCU_PORT_B:
    {
      __HAL_RCC_GPIOB_CLK_ENABLE();
      HAL_GPIO_Init(GPIOB,&GPIO_InitStruct);
      break;
    }
    case DRIVER_MCU_PORT_C:
    {
      __HAL_RCC_GPIOC_CLK_ENABLE();
      HAL_GPIO_Init(GPIOC,&GPIO_InitStruct);
      break;
    }
    case DRIVER_MCU_PORT_D:
    {
      __HAL_RCC_GPIOD_CLK_ENABLE();
      HAL_GPIO_Init(GPIOD,&GPIO_InitStruct);
      break;
    }
    case DRIVER_MCU_PORT_E:
    {
      __HAL_RCC_GPIOE_CLK_ENABLE();
      HAL_GPIO_Init(GPIOE,&GPIO_InitStruct);
      break;
    } 
  }
  return DRIVER_STATE_PASS;
}
/* End of file -------------------------------------------------------- */
