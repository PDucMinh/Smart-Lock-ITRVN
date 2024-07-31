/**
 * @file       bsp_mcu.c
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license
 * @version    1.0.0
 * @date       2024-07-28
 * @author     Hung Nguyen
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
#include "bsp_mcu.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */
/**
 * @brief  <function description>
 *
 * @param[in]     none
 *
 * @attention  <API attention note>
 *
 * @return
 *  - 0: Success
 *  - 1: Error
 */
static bsp_state_t bsp_mcu_clk_init(void);

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
static bsp_state_t bsp_mcu_pwm_init(bsp_mcu_periph_t periph, TIM_HandleTypeDef* htim);

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
static void bsp_mcu_pwm_mspinit(TIM_HandleTypeDef* htim);

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
static bsp_state_t bsp_mcu_timer_init(bsp_mcu_periph_t periph, TIM_HandleTypeDef* htim);

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
static void bsp_mcu_timer_mspinit(TIM_HandleTypeDef* htim);
/* Function definitions ----------------------------------------------- */
bsp_state_t bsp_mcu_init(bsp_mcu_init_t* mcu_init, bsp_mcu_t* mcu)
{
  BSP_CHECK_NULL(mcu_init, BSP_STATE_FAIL);
  BSP_CHECK_NULL(mcu, BSP_STATE_FAIL);
  HAL_Init();
  if (bsp_mcu_clk_init() == BSP_STATE_FAIL)
  {
    return BSP_STATE_FAIL;
  }
  if ((mcu_init->is_tim3_used) != BSP_MCU_PERIPH_NONE)
  {
    if (bsp_mcu_pwm_init(mcu_init->is_tim3_used, &(mcu->htim3)) == BSP_STATE_FAIL)
    {
      return BSP_STATE_FAIL;
    }
  }
  if ((mcu_init->is_tim2_used) != BSP_MCU_PERIPH_NONE)
  {
    if (bsp_mcu_timer_init(mcu_init->is_tim2_used, &(mcu->htim2)) == BSP_STATE_FAIL)
    {
      return BSP_STATE_FAIL;
    }
  }
  return BSP_STATE_PASS;
}
/* Private definitions ----------------------------------------------- */
static bsp_state_t bsp_mcu_clk_init(void)
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
    return BSP_STATE_FAIL;
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
    return BSP_STATE_FAIL;
  }
  return BSP_STATE_PASS;
}

static bsp_state_t bsp_mcu_pwm_init(bsp_mcu_periph_t periph, TIM_HandleTypeDef* htim)
{
  BSP_CHECK_NULL(htim, BSP_STATE_FAIL);
  if (periph == BSP_MCU_PERIPH_TIM3)
  {
    TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
    TIM_MasterConfigTypeDef sMasterConfig = { 0 };
    TIM_OC_InitTypeDef sConfigOC = { 0 };

    /* USER CODE BEGIN TIM4_Init 1 */

    /* USER CODE END TIM4_Init 1 */
    htim->Instance = TIM3;
    (htim->Init).Prescaler = 999;
    (htim->Init).CounterMode = TIM_COUNTERMODE_UP;
    (htim->Init).Period = 99;
    (htim->Init).ClockDivision = TIM_CLOCKDIVISION_DIV1;
    (htim->Init).AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    htim->Base_MspInitCallback = bsp_mcu_pwm_mspinit;
    if (HAL_TIM_Base_Init(htim) != HAL_OK)
    {
      return BSP_STATE_FAIL;
    }

    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(htim, &sClockSourceConfig) != HAL_OK)
    {
      return BSP_STATE_FAIL;
    }
    if (HAL_TIM_PWM_Init(htim) != HAL_OK)
    {
      return BSP_STATE_FAIL;
    }

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(htim, &sMasterConfig) != HAL_OK)
    {
      return BSP_STATE_FAIL;
    }

    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel(htim, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
    {
      return BSP_STATE_FAIL;
    }
    if (HAL_TIM_PWM_ConfigChannel(htim, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
    {
      return BSP_STATE_FAIL;
    }
    if (HAL_TIM_PWM_ConfigChannel(htim, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
    {
      return BSP_STATE_FAIL;
    }
  }
  return BSP_STATE_PASS;
}

static bsp_state_t bsp_mcu_timer_init(bsp_mcu_periph_t periph, TIM_HandleTypeDef* htim)
{
  BSP_CHECK_NULL(htim, BSP_STATE_FAIL);
  if (periph == BSP_MCU_PERIPH_TIM2)
  {
    TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
    TIM_MasterConfigTypeDef sMasterConfig = { 0 };

    /* USER CODE BEGIN TIM2_Init 1 */

    /* USER CODE END TIM2_Init 1 */
    (htim->Instance) = TIM2;
    (htim->Init).Prescaler = 99;
    (htim->Init).CounterMode = TIM_COUNTERMODE_UP;
    (htim->Init).Period = 999;
    (htim->Init).ClockDivision = TIM_CLOCKDIVISION_DIV1;
    (htim->Init).AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    htim->Base_MspInitCallback = bsp_mcu_timer_mspinit;
    if (HAL_TIM_Base_Init(htim) != HAL_OK)
    {
      return BSP_STATE_FAIL;
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(htim, &sClockSourceConfig) != HAL_OK)
    {
      return BSP_STATE_FAIL;
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(htim, &sMasterConfig) != HAL_OK)
    {
      return BSP_STATE_FAIL;
    }
  }
  return BSP_STATE_PASS;
}

static void bsp_mcu_pwm_mspinit(TIM_HandleTypeDef* htim)
{
  if (htim->Instance == TIM3)
  {
    __HAL_RCC_TIM3_CLK_ENABLE();
  }
}

static void bsp_mcu_timer_mspinit(TIM_HandleTypeDef* htim)
{
  if (htim->Instance == TIM2)
  {
    __HAL_RCC_TIM2_CLK_ENABLE();
    /* TIM2 interrupt Init */
    HAL_NVIC_SetPriority(TIM2_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
  }
}

void HAL_MspInit(void)
{
  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();
}
/* End of file -------------------------------------------------------- */
