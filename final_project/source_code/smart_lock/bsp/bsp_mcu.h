/**
 * @file       bsp_mcu.h
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license
 * @version    1.0.0
 * @date       2024-07-27
 * @author     Hung Nguyen
 *
 * @brief      Export initializing peripheral API for MCU
 *
 * @note
 * @example    
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __BSP_MCU_H
#define __BSP_MCU_H

/* Includes ----------------------------------------------------------- */
#include "bsp_state.h"
#include "stm32f4xx_hal.h"
/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief MCU peripheral ID
 */
typedef enum
{
  BSP_MCU_PERIPH_NONE,
  BSP_MCU_PERIPH_TIM1,
  BSP_MCU_PERIPH_TIM2,
  BSP_MCU_PERIPH_TIM3,
  BSP_MCU_PERIPH_TIM4,
  BSP_MCU_PERIPH_TIM5,
  BSP_MCU_PERIPH_TIM9,
  BSP_MCU_PERIPH_TIM10,
  BSP_MCU_PERIPH_TIM11,
  BSP_MCU_PERIPH_SPI1,
  BSP_MCU_PERIPH_SPI2,
  BSP_MCU_PERIPH_SPI3,
  BSP_MCU_PERIPH_SPI4,
  BSP_MCU_PERIPH_SPI5,
  BSP_MCU_PERIPH_I2C1,
  BSP_MCU_PERIPH_I2C2,
  BSP_MCU_PERIPH_I2C3,
  BSP_MCU_PERIPH_DMA1_STREAM0,
  BSP_MCU_PERIPH_DMA1_STREAM1,
  BSP_MCU_PERIPH_DMA1_STREAM2,
  BSP_MCU_PERIPH_DMA1_STREAM3,
  BSP_MCU_PERIPH_DMA1_STREAM4,
  BSP_MCU_PERIPH_DMA1_STREAM5,
  BSP_MCU_PERIPH_DMA1_STREAM6,
  BSP_MCU_PERIPH_DMA1_STREAM7,
  BSP_MCU_PERIPH_DMA2_STREAM0,
  BSP_MCU_PERIPH_DMA2_STREAM1,
  BSP_MCU_PERIPH_DMA2_STREAM2,
  BSP_MCU_PERIPH_DMA2_STREAM3,
  BSP_MCU_PERIPH_DMA2_STREAM4,
  BSP_MCU_PERIPH_DMA2_STREAM5,
  BSP_MCU_PERIPH_DMA2_STREAM6,
  BSP_MCU_PERIPH_DMA2_STREAM7,
  BSP_MCU_PERIPH_USART1,
  BSP_MCU_PERIPH_USART2,
  BSP_MCU_PERIPH_USART6,
  BSP_MCU_PERIPH_EXTI,
  BSP_MCU_PERIPH_FLASH,
} bsp_mcu_periph_t;

/**
 * @brief MCU init struct
 */
typedef struct
{
  bsp_mcu_periph_t is_spi_used;
  bsp_mcu_periph_t is_i2c_used;
  bsp_mcu_periph_t is_dma_used;
  bsp_mcu_periph_t is_usart_used;
  bsp_mcu_periph_t is_tim1_used;
  bsp_mcu_periph_t is_tim2_used;
  bsp_mcu_periph_t is_tim3_used;
  bsp_mcu_periph_t is_tim4_used;
  bsp_mcu_periph_t is_tim5_used;
  bsp_mcu_periph_t is_tim9_used;
  bsp_mcu_periph_t is_tim10_used;
  bsp_mcu_periph_t is_tim11_used;
} bsp_mcu_init_t;

/**
 * @brief MCU peripheral struct
 */
typedef struct
{
  SPI_HandleTypeDef hspi1;
  SPI_HandleTypeDef hspi2;
  SPI_HandleTypeDef hspi3;
  SPI_HandleTypeDef hspi4;
  SPI_HandleTypeDef hspi5;
  I2C_HandleTypeDef hi2c1;
  I2C_HandleTypeDef hi2c2;
  I2C_HandleTypeDef hi2c3;
  DMA_HandleTypeDef hdma1_str0;
  DMA_HandleTypeDef hdma1_str1;
  DMA_HandleTypeDef hdma1_str2;
  DMA_HandleTypeDef hdma1_str3;
  DMA_HandleTypeDef hdma1_str4;
  DMA_HandleTypeDef hdma1_str5;
  DMA_HandleTypeDef hdma1_str6;
  DMA_HandleTypeDef hdma1_str7;
  DMA_HandleTypeDef hdma2_str0;
  DMA_HandleTypeDef hdma2_str1;
  DMA_HandleTypeDef hdma2_str2;
  DMA_HandleTypeDef hdma2_str3;
  DMA_HandleTypeDef hdma2_str4;
  DMA_HandleTypeDef hdma2_str5;
  DMA_HandleTypeDef hdma2_str6;
  DMA_HandleTypeDef hdma2_str7;
  USART_HandleTypeDef husart1;
  USART_HandleTypeDef husart2;
  USART_HandleTypeDef husart6;
  UART_HandleTypeDef huart1;
  UART_HandleTypeDef huart2;
  UART_HandleTypeDef huart6;
  TIM_HandleTypeDef htim1;
  TIM_HandleTypeDef htim2;
  TIM_HandleTypeDef htim3;
  TIM_HandleTypeDef htim4;
  TIM_HandleTypeDef htim5;
  TIM_HandleTypeDef htim9;
  TIM_HandleTypeDef htim10;
  TIM_HandleTypeDef htim11;
} bsp_mcu_t;
/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief  <function description>
 *
 * @param[in]     mcu_init      list of init option for necessary peripheral
 * @param[out]    mcu           list of peripheral initialized
 *
 * @attention  this API will be called one time only 
 *
 * @return     none
 *  
 *  
 */
bsp_state_t bsp_mcu_init(bsp_mcu_init_t* mcu_init, bsp_mcu_t* mcu);

#endif // __BSP_MCU_H

/* End of file -------------------------------------------------------- */
