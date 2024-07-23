/**
 * @file       DRV_mcu.c
 * @copyright
 * @license
 * @version
 * @date       2024-07-07
 * @author     <first_name_1> <last_name_1>
 * @author     <first_name_2> <last_name_2>
 *
 * @brief      This file include the following function:
 *             - DRV_mcu_init() < This function initialize stm32f4 mcu'system
 *                                   include flash function, clock function >
 *
 * @note
 * @example
 *
 */

/* Includes ----------------------------------------------------------- */
#include "drv_mcu.h"

/* Private defines ---------------------------------------------------- */
#define DRV_MCU_NUM_PORT (5)
#define DRV_MCU_NUM_PIN (16)
/* Private enumerate/structure ---------------------------------------- */
/**
 * @brief <the state of being used of MCU's pin>
 */
typedef enum
{
  DRV_MCU_PIN_STATE_FREE,  /**< This pin is not initialized by any module */
  DRV_MCU_PIN_STATE_USED,  /**< This pin is initialized by another module */
  DRV_MCU_PIN_STATE_UNUSED /**< This pin is not allowed to be used        */
} drv_mcu_pin_state_t;
/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static drv_mcu_pin_state_t v_dmcu_pin_list[DRV_MCU_NUM_PORT][DRV_MCU_NUM_PIN] = {
  /* MCU_PORTA */
  { DRV_MCU_PIN_STATE_FREE,  /* MCU_PA0 */
    DRV_MCU_PIN_STATE_FREE,  /* MCU_PA1 */
    DRV_MCU_PIN_STATE_FREE,  /* MCU_PA2 */
    DRV_MCU_PIN_STATE_FREE,  /* MCU_PA3 */
    DRV_MCU_PIN_STATE_FREE,  /* MCU_PA4 */
    DRV_MCU_PIN_STATE_FREE,  /* MCU_PA5 */
    DRV_MCU_PIN_STATE_FREE,  /* MCU_PA6 */
    DRV_MCU_PIN_STATE_FREE,  /* MCU_PA7 */
    DRV_MCU_PIN_STATE_FREE,  /* MCU_PA8 */
    DRV_MCU_PIN_STATE_FREE,  /* MCU_PA9 */
    DRV_MCU_PIN_STATE_FREE,  /* MCU_PA10 */
    DRV_MCU_PIN_STATE_UNUSED,/* MCU_PA11 */
    DRV_MCU_PIN_STATE_FREE,  /* MCU_PA12 */
    DRV_MCU_PIN_STATE_FREE,  /* MCU_PA13 */
    DRV_MCU_PIN_STATE_FREE,  /* MCU_PA14 */
    DRV_MCU_PIN_STATE_FREE },/* MCU_PA15 */
  /* MCU_PORTB */
  { DRV_MCU_PIN_STATE_FREE,  /* MCU_PB0 */
    DRV_MCU_PIN_STATE_FREE,  /* MCU_PB1 */
    DRV_MCU_PIN_STATE_FREE,  /* MCU_PB2 */
    DRV_MCU_PIN_STATE_FREE,  /* MCU_PB3 */
    DRV_MCU_PIN_STATE_FREE,  /* MCU_PB4 */
    DRV_MCU_PIN_STATE_FREE,  /* MCU_PB5 */
    DRV_MCU_PIN_STATE_FREE,  /* MCU_PB6 */
    DRV_MCU_PIN_STATE_FREE,  /* MCU_PB7 */
    DRV_MCU_PIN_STATE_FREE,  /* MCU_PB8 */
    DRV_MCU_PIN_STATE_FREE,  /* MCU_PB9 */
    DRV_MCU_PIN_STATE_FREE,  /* MCU_PB10 */
    DRV_MCU_PIN_STATE_UNUSED,/* MCU_PB11 */ 
    DRV_MCU_PIN_STATE_FREE,  /* MCU_PB12 */
    DRV_MCU_PIN_STATE_FREE,  /* MCU_PB13 */
    DRV_MCU_PIN_STATE_FREE,  /* MCU_PB14 */
    DRV_MCU_PIN_STATE_FREE },/* MCU_PB15 */
  /* MCU_PORTC */
  { DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE },
  /* MCU_PORTD */
  { DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE },
  /* MCU_PORTE */
  { DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE,
    DRV_MCU_PIN_STATE_FREE }
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
drv_state_t drv_mcu_clock_init(void);

#ifdef HAL_TIM_MODULE_ENABLED
drv_state_t drv_mcu_pwm_init(drv_mcu_t* v_dmcu);
drv_state_t drv_mcu_timer_init(drv_mcu_t* v_dmcu);
#endif

#ifdef HAL_UART_MODULE_ENABLED
drv_state_t drv_mcu_uart_init(drv_mcu_t* v_dmcu);
void drv_mcu_uart_mspinit(UART_HandleTypeDef* huart);
#endif

#ifdef HAL_I2C_MODULE_ENABLED
drv_state_t drv_mcu_i2c_init(drv_mcu_t* v_dmcu);
#endif

#ifdef HAL_DMA_MODULE_ENABLED
drv_state_t drv_mcu_dma_init(drv_mcu_t* v_dmcu);
#endif
/* Function definitions ----------------------------------------------- */
drv_state_t drv_mcu_init(drv_mcu_t* v_dmcu)
{
  DRV_CHECK_NULL(v_dmcu, DRV_STATE_FAIL);
  HAL_Init();
  if (drv_mcu_clock_init() == DRV_STATE_FAIL)
  {
    return DRV_STATE_FAIL;
  }
#ifdef HAL_TIM_MODULE_ENABLED
  if (drv_mcu_timer_init(v_dmcu) == DRV_STATE_FAIL)
  {
    return DRV_STATE_FAIL;
  }
  if (drv_mcu_pwm_init(v_dmcu) == DRV_STATE_FAIL)
  {
    return DRV_STATE_FAIL;
  }
#endif

#ifdef HAL_UART_MODULE_ENABLED
  if (drv_mcu_uart_init(v_dmcu) == DRV_STATE_FAIL)
  {
    return DRV_STATE_FAIL;
  }
#endif

#ifdef HAL_I2C_MODULE_ENABLED
  if (drv_mcu_i2c_init(v_dmcu) == DRV_STATE_FAIL)
  {
    return DRV_STATE_FAIL;
  }
#endif

#ifdef HAL_DMA_MODULE_ENABLED
  if (drv_mcu_dma_init(v_dmcu) == DRV_STATE_FAIL)
  {
    return DRV_STATE_FAIL;
  }
#endif
  return DRV_STATE_PASS;
}

drv_state_t drv_mcu_pin_init(drv_mcu_pin_t* v_dpin)
{
  DRV_CHECK_NULL(v_dpin, DRV_STATE_FAIL);
  uint16_t port, pin;
  port = ((v_dpin->io) & 0xF0) >> 4;
  pin = (v_dpin->io) & 0x0F;
  if (v_dmcu_pin_list[port][pin] != DRV_MCU_PIN_STATE_FREE)
  {
    return DRV_STATE_FAIL;
  }
  else
  {
    v_dmcu_pin_list[port][pin] = DRV_MCU_PIN_STATE_USED;
  }
  GPIO_InitTypeDef GPIO_InitStruct = { 0 };
  GPIO_InitStruct.Pin = (uint16_t)1 << pin;
  GPIO_InitStruct.Mode = v_dpin->mode;
  GPIO_InitStruct.Pull = v_dpin->pull_type;
  GPIO_InitStruct.Speed = v_dpin->speed;
  GPIO_InitStruct.Alternate = v_dpin->af;
  switch (port)
  {
  case DRV_MCU_PORT_A:
  {
    __HAL_RCC_GPIOA_CLK_ENABLE();
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    break;
  }
  case DRV_MCU_PORT_B:
  {
    __HAL_RCC_GPIOB_CLK_ENABLE();
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    break;
  }
  case DRV_MCU_PORT_C:
  {
    __HAL_RCC_GPIOC_CLK_ENABLE();
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    break;
  }
  case DRV_MCU_PORT_D:
  {
    __HAL_RCC_GPIOD_CLK_ENABLE();
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
    break;
  }
  case DRV_MCU_PORT_E:
  {
    __HAL_RCC_GPIOE_CLK_ENABLE();
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
    break;
  }
  }
  return DRV_STATE_PASS;
}
/* Private definitions ----------------------------------------------- */
drv_state_t drv_mcu_clock_init(void)
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
    return DRV_STATE_FAIL;
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
    return DRV_STATE_FAIL;
  }
  return DRV_STATE_PASS;
}

#ifdef HAL_TIM_MODULE_ENABLED
drv_state_t drv_mcu_timer_init(drv_mcu_t* v_dmcu)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
  TIM_MasterConfigTypeDef sMasterConfig = { 0 };

  v_dmcu->htim3.Instance = TIM3;
  v_dmcu->htim3.Init.Prescaler = 99;
  v_dmcu->htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  v_dmcu->htim3.Init.Period = 999;
  v_dmcu->htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  v_dmcu->htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&(v_dmcu->htim3)) != HAL_OK)
  {
    return DRV_STATE_FAIL;
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&(v_dmcu->htim3), &sClockSourceConfig) != HAL_OK)
  {
    return DRV_STATE_FAIL;
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&(v_dmcu->htim3), &sMasterConfig) != HAL_OK)
  {
    return DRV_STATE_FAIL;
  }
  HAL_TIM_Base_Start_IT(&(v_dmcu->htim3));
  return DRV_STATE_PASS;
}

drv_state_t drv_mcu_pwm_init(drv_mcu_t* v_dmcu)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
  TIM_MasterConfigTypeDef sMasterConfig = { 0 };
  TIM_OC_InitTypeDef sConfigOC = { 0 };

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
    return DRV_STATE_FAIL;
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&(v_dmcu->htim4), &sClockSourceConfig) != HAL_OK)
  {
    return DRV_STATE_FAIL;
  }
  if (HAL_TIM_PWM_Init(&(v_dmcu->htim4)) != HAL_OK)
  {
    return DRV_STATE_FAIL;
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&(v_dmcu->htim4), &sMasterConfig) != HAL_OK)
  {
    return DRV_STATE_FAIL;
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&(v_dmcu->htim4), &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    return DRV_STATE_FAIL;
  }
  if (HAL_TIM_PWM_ConfigChannel(&(v_dmcu->htim4), &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    return DRV_STATE_FAIL;
  }
  if (HAL_TIM_PWM_ConfigChannel(&(v_dmcu->htim4), &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    return DRV_STATE_FAIL;
  }
  return DRV_STATE_PASS;
}
#endif

#ifdef HAL_UART_MODULE_ENABLED
drv_state_t drv_mcu_uart_init(drv_mcu_t* v_dmcu)
{
  v_dmcu->huart6.Instance = USART6;
  v_dmcu->huart6.Init.BaudRate = 115200;
  v_dmcu->huart6.Init.WordLength = UART_WORDLENGTH_8B;
  v_dmcu->huart6.Init.StopBits = UART_STOPBITS_1;
  v_dmcu->huart6.Init.Parity = UART_PARITY_NONE;
  v_dmcu->huart6.Init.Mode = UART_MODE_TX_RX;
  v_dmcu->huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  v_dmcu->huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  (v_dmcu->huart6).MspInitCallback = drv_mcu_uart_mspinit;
  if (HAL_UART_Init(&(v_dmcu->huart6)) != HAL_OK)
  {
    return DRV_STATE_FAIL;
  }
}

void drv_mcu_uart_mspinit(UART_HandleTypeDef* huart)
{
  if ((huart->Instance) == USART6)
  {
    __HAL_RCC_USART6_CLK_ENABLE();
    HAL_NVIC_SetPriority(USART6_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(USART6_IRQn);
  }
}
#endif

#ifdef HAL_I2C_MODULE_ENABLED
drv_state_t drv_mcu_i2c_init(drv_mcu_t* v_dmcu)
{
  (v_dmcu->hi2c1).Instance = I2C1;
  (v_dmcu->hi2c1).Init.ClockSpeed = 100000;
  (v_dmcu->hi2c1).Init.DutyCycle = I2C_DUTYCYCLE_2;
  (v_dmcu->hi2c1).Init.OwnAddress1 = 2;
  (v_dmcu->hi2c1).Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  (v_dmcu->hi2c1).Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  (v_dmcu->hi2c1).Init.OwnAddress2 = 0;
  (v_dmcu->hi2c1).Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  (v_dmcu->hi2c1).Init.NoStretchMode = I2C_NOSTRETCH_ENABLE;
  (v_dmcu->hi2c1).MspInitCallback = drv_mcu_i2c_mspinit;
  if (HAL_I2C_Init(&(v_dmcu->hi2c1)) != HAL_OK)
  {
    return DRV_STATE_FAIL;
  }
}

void drv_mcu_i2c_mspinit(I2C_HandleTypeDef* hi2c)
{
  if (hi2c->Instance == I2C1)
  {
    __HAL_RCC_I2C1_CLK_ENABLE();
    HAL_NVIC_SetPriority(I2C1_EV_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
  }
}
#endif

#ifdef HAL_DMA_MODULE_ENABLED
drv_state_t drv_mcu_dma_init(drv_mcu_t* v_dmcu)
{
  if ((v_dmcu->huart6).Instance == USART6)
  {
    /* DMA controller clock enable */
    __HAL_RCC_DMA2_CLK_ENABLE();

    /* DMA interrupt init */
    /* DMA2_Stream1_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);

    (v_dmcu->hdma_usart6_rx).Instance = DMA2_Stream1;
    (v_dmcu->hdma_usart6_rx).Init.Channel = DMA_CHANNEL_5;
    (v_dmcu->hdma_usart6_rx).Init.Direction = DMA_PERIPH_TO_MEMORY;
    (v_dmcu->hdma_usart6_rx).Init.PeriphInc = DMA_PINC_DISABLE;
    (v_dmcu->hdma_usart6_rx).Init.MemInc = DMA_MINC_ENABLE;
    (v_dmcu->hdma_usart6_rx).Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    (v_dmcu->hdma_usart6_rx).Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    (v_dmcu->hdma_usart6_rx).Init.Mode = DMA_CIRCULAR;
    (v_dmcu->hdma_usart6_rx).Init.Priority = DMA_PRIORITY_LOW;
    (v_dmcu->hdma_usart6_rx).Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&(v_dmcu->hdma_usart6_rx)) != HAL_OK)
    {
      return DRV_STATE_FAIL;
    }

    __HAL_LINKDMA(&(vdmcu->huart), hdmarx, v_dmcu->hdma_usart6_rx);
  }

  if (v_dmcu->hi2c1 == I2C1)
  {
    /* DMA controller clock enable */
    __HAL_RCC_DMA1_CLK_ENABLE();

    /* DMA interrupt init */
    /* DMA1_Stream0_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);
    (v_dmcu->hdma_i2c1_rx).Instance = DMA1_Stream0;
    (v_dmcu->hdma_i2c1_rx).Init.Channel = DMA_CHANNEL_1;
    (v_dmcu->hdma_i2c1_rx).Init.Direction = DMA_PERIPH_TO_MEMORY;
    (v_dmcu->hdma_i2c1_rx).Init.PeriphInc = DMA_PINC_DISABLE;
    (v_dmcu->hdma_i2c1_rx).Init.MemInc = DMA_MINC_ENABLE;
    (v_dmcu->hdma_i2c1_rx).Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    (v_dmcu->hdma_i2c1_rx).Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    (v_dmcu->hdma_i2c1_rx).Init.Mode = DMA_CIRCULAR;
    (v_dmcu->hdma_i2c1_rx).Init.Priority = DMA_PRIORITY_LOW;
    (v_dmcu->hdma_i2c1_rx).Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&(v_dmcu->hdma_i2c1_rx)) != HAL_OK)
    {
      return DRV_STATE_FAIL;
    }

    __HAL_LINKDMA(&(v_dmcu->hi2c1),hdmarx,v_dmcu->hdma_i2c1_rx);
  }
}
#endif
/* End of file -------------------------------------------------------- */
