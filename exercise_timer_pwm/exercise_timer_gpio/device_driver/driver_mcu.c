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

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */

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
driver_state_t driver_mcu_pwm_init(driver_mcu_t* v_dmcu);
driver_state_t driver_mcu_timer_init(driver_mcu_t* v_dmcu);
/* Function definitions ----------------------------------------------- */
driver_state_t driver_mcu_init(driver_mcu_t* v_dmcu)
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
  RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
  RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

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

driver_state_t driver_mcu_timer_init(driver_mcu_t* v_dmcu)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
  TIM_MasterConfigTypeDef sMasterConfig = { 0 };

  v_dmcu->htim3.Instance = TIM3;
  v_dmcu->htim3.Init.Prescaler = 9999;
  v_dmcu->htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  v_dmcu->htim3.Init.Period = 9;
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

driver_state_t driver_mcu_pwm_init(driver_mcu_t* v_dmcu)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
  TIM_MasterConfigTypeDef sMasterConfig = { 0 };
  TIM_OC_InitTypeDef sConfigOC = { 0 };

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  v_dmcu->htim4.Instance = TIM4;
  v_dmcu->htim4.Init.Prescaler = 9999;
  v_dmcu->htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  v_dmcu->htim4.Init.Period = 9999;
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
/* End of file -------------------------------------------------------- */
