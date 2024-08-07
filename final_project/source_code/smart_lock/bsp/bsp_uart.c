/**
 * @file       bsp_uart.c
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license
 * @version    1.0.0
 * @date       2024-08-07
 * @author     Hung Nguyen
 *
 * @brief      <A brief description of the content of the file>
 *
 * @note
 * @example
 */

/* Includes ----------------------------------------------------------- */
#include "bsp_uart.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static UART_HandleTypeDef huart6;
static uint8_t tx_cplt = 0;
static uint8_t rx_cplt = 0;

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
static void bsp_uart_receive_handler(UART_HandleTypeDef* huart);

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
static void bsp_uart_transmit_handler(UART_HandleTypeDef* huart);
/* Function definitions ----------------------------------------------- */
bsp_state_t bsp_uart_init(bsp_mcu_t* mcu)
{
  BSP_CHECK_NULL(mcu, BSP_STATE_FAIL);
  huart6 = mcu->huart6;
  huart6.RxCpltCallback = bsp_uart_receive_handler;
  huart6.TxCpltCallback = bsp_uart_transmit_handler;
  return BSP_STATE_PASS;
}

bsp_state_t bsp_uart_transmit_start(bsp_config_id_t id, uint8_t* pdata, uint16_t size);
{
  BSP_CHECK_NULL(pdata, BSP_STATE_FAIL);
  BSP_CHECK_RANGE(id, BSP_CONFIG_ID_MAX, BSP_STATE_FAIL);
  BSP_CHECK_NULL(size, BSP_STATE_FAIL);
  if (id == BSP_CONFIG_ID_PROTOCOL)
  {
    if (HAL_UART_Transmit_IT(&huart6, pdata, size) != HAL_OK)
    {
      return BSP_STATE_FAIL;
    }
  }
  return BSP_STATE_PASS;
}

bsp_state_t bsp_uart_receive_start(bsp_config_id_t id, uint8_t* pdata, uint16_t size);
{
  BSP_CHECK_NULL(pdata, BSP_STATE_FAIL);
  BSP_CHECK_RANGE(id, BSP_CONFIG_ID_MAX, BSP_STATE_FAIL);
  BSP_CHECK_NULL(size, BSP_STATE_FAIL);
  if (id == BSP_CONFIG_ID_PROTOCOL)
  {
    if (HAL_UART_Receive_IT(&huart6, pdata, size) != HAL_OK)
    {
      return BSP_STATE_FAIL;
    }
  }
  return BSP_STATE_PASS;
}

uint8_t bsp_uart_transmit_cplt(bsp_config_id_t id)
{
  if (id == BSP_CONFIG_ID_PROTOCOL)
  {
    uint8_t ret_flag;
    ret_flag = tx_cplt;
    if (tx_cplt == 1)
    {
      tx_cplt = 0;
    }
    return ret_flag;
  }
}

uint8_t bsp_uart_receive_cplt(bsp_config_id_t id)
{
  if (id == BSP_CONFIG_ID_PROTOCOL)
  {
    uint8_t ret_flag;
    ret_flag = rx_cplt;
    if (rx_cplt == 1)
    {
      rx_cplt = 0;
    }
    return ret_flag;
  }
}
/* Private definitions ----------------------------------------------- */
static void bsp_uart_transmit_handler(UART_HandleTypeDef* huart)
{
  tx_cplt = 1;
}

static void bsp_uart_receive_handler(UART_HandleTypeDef* huart)
{
  rx_cplt = 1;
}
/* End of file -------------------------------------------------------- */
