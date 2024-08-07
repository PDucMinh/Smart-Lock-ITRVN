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
static bsp_state_t bsp_mcu_usart_init(bsp_mcu_periph_t periph, USART_HandleTypeDef* husart);

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
static void bsp_mcu_usart_mspinit(USART_HandleTypeDef* husart);

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
static bsp_state_t bsp_mcu_uart_init(bsp_mcu_periph_t periph, UART_HandleTypeDef* huart);

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
static void bsp_mcu_uart_mspinit(UART_HandleTypeDef* huart);

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
static bsp_state_t bsp_mcu_i2c_init(bsp_mcu_periph_t periph, I2C_HandleTypeDef* hi2c);

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
static void bsp_mcu_i2c_mspinit(I2C_HandleTypeDef* hi2c);
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
  if ((mcu_init->is_tim4_used) != BSP_MCU_PERIPH_NONE)
  {
    if (bsp_mcu_pwm_init(mcu_init->is_tim4_used, &(mcu->htim4)) == BSP_STATE_FAIL)
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
  if ((mcu_init->is_usart2_used) == BSP_MCU_PERIPH_USART2_SYNCH)
  {
    if (bsp_mcu_usart_init(mcu_init->is_usart2_used, &(mcu->husart2)) == BSP_STATE_FAIL)
    {
      return BSP_STATE_FAIL;
    }
  }
  if ((mcu_init->is_usart6_used) == BSP_MCU_PERIPH_USART6_ASYNCH)
  {
    if (bsp_mcu_uart_init(mcu_init->is_usart2_used, &(mcu->huart6)) == BSP_STATE_FAIL)
    {
      return BSP_STATE_FAIL;
    }
  }

  if ((mcu_init->is_i2c1_used) == BSP_MCU_PERIPH_I2C1)
  {
    if (bsp_mcu_i2c_init(mcu_init->is_i2c1_used, &(mcu->hi2c1)) == BSP_STATE_FAIL)
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
  else if (periph == BSP_MCU_PERIPH_TIM4)
  {
    TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
    TIM_MasterConfigTypeDef sMasterConfig = { 0 };
    TIM_OC_InitTypeDef sConfigOC = { 0 };

    /* USER CODE BEGIN TIM4_Init 1 */

    /* USER CODE END TIM4_Init 1 */
    htim->Instance = TIM4;
    (htim->Init).Prescaler = 999;
    (htim->Init).CounterMode = TIM_COUNTERMODE_UP;
    (htim->Init).Period = 9999;
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
    sConfigOC.Pulse = 4999;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel(htim, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
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

static bsp_state_t bsp_mcu_usart_init(bsp_mcu_periph_t periph, USART_HandleTypeDef* husart)
{
  BSP_CHECK_NULL(husart, BSP_STATE_FAIL);
  if (periph == BSP_MCU_PERIPH_USART2_SYNCH)
  {
    husart->Instance = USART2;
    (husart->Init).BaudRate = 115200;
    (husart->Init).WordLength = USART_WORDLENGTH_8B;
    (husart->Init).StopBits = USART_STOPBITS_1;
    (husart->Init).Parity = USART_PARITY_NONE;
    (husart->Init).Mode = USART_MODE_TX_RX;
    (husart->Init).CLKPolarity = USART_POLARITY_HIGH;
    (husart->Init).CLKPhase = USART_PHASE_2EDGE;
    (husart->Init).CLKLastBit = USART_LASTBIT_DISABLE;
    husart->MspInitCallback = bsp_mcu_usart_mspinit;
    if (HAL_USART_Init(husart) != HAL_OK)
    {
      return BSP_STATE_FAIL;
    }
  }
  return BSP_STATE_FAIL;
}

static bsp_state_t bsp_mcu_uart_init(bsp_mcu_periph_t periph, UART_HandleTypeDef* huart)
{
  BSP_CHECK_NULL(huart, BSP_STATE_FAIL);
  if (periph == BSP_MCU_PERIPH_USART6_ASYNCH)
  {
    (huart->Instance) = USART6;
    (huart->Init).BaudRate = 115200;
    (huart->Init).WordLength = UART_WORDLENGTH_8B;
    (huart->Init).StopBits = UART_STOPBITS_1;
    (huart->Init).Parity = UART_PARITY_NONE;
    (huart->Init).Mode = UART_MODE_TX_RX;
    (huart->Init).HwFlowCtl = UART_HWCONTROL_NONE;
    (huart->Init).OverSampling = UART_OVERSAMPLING_16;
    huart->MspInitCallback = bsp_mcu_uart_mspinit;
    if (HAL_UART_Init(huart) != HAL_OK)
    {
      return BSP_STATE_FAIL;
    }
  }
}

static bsp_state_t bsp_mcu_i2c_init(bsp_mcu_periph_t periph, I2C_HandleTypeDef* hi2c)
{
  (hi2c->Instance) = I2C1;
  (hi2c->Init).ClockSpeed = 100000;
  (hi2c->Init).DutyCycle = I2C_DUTYCYCLE_2;
  (hi2c->Init).OwnAddress1 = 0;
  (hi2c->Init).AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  (hi2c->Init).DualAddressMode = I2C_DUALADDRESS_DISABLE;
  (hi2c->Init).OwnAddress2 = 0;
  (hi2c->Init).GeneralCallMode = I2C_GENERALCALL_DISABLE;
  (hi2c->Init).NoStretchMode = I2C_NOSTRETCH_DISABLE;
  hi2c->MspInitCallback = bsp_mcu_i2c_mspinit;
  if (HAL_I2C_Init(hi2c) != HAL_OK)
  {
    return BSP_STATE_FAIL;
  }
}

static void bsp_mcu_pwm_mspinit(TIM_HandleTypeDef* htim)
{
  if (htim->Instance == TIM3)
  {
    __HAL_RCC_TIM3_CLK_ENABLE();
  }
  else if (htim->Instance == TIM4)
  {
    __HAL_RCC_TIM4_CLK_ENABLE();
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

static void bsp_mcu_usart_mspinit(USART_HandleTypeDef* husart)
{
  if (husart->Instance == USART2)
  {
    __HAL_RCC_USART2_CLK_ENABLE();
    HAL_NVIC_SetPriority(USART2_IRQn, 3, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
  }
}
static void bsp_mcu_uart_mspinit(UART_HandleTypeDef* huart)
{
  if (huart->Instance == USART6)
  {
    __HAL_RCC_USART6_CLK_ENABLE();
    HAL_NVIC_SetPriority(USART6_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(USART6_IRQn);
  }
}

static void bsp_mcu_i2c_mspinit(I2C_HandleTypeDef* hi2c)
{
  if (hi2c->Instance == I2C1)
  {
    __HAL_RCC_I2C1_CLK_ENABLE();
    HAL_NVIC_SetPriority(I2C1_EV_IRQn, 6, 0);
    HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
  }
}

void HAL_MspInit(void)
{
  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();
}
/* End of file -------------------------------------------------------- */
