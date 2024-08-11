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
UART_HandleTypeDef huart6;
CRC_HandleTypeDef hcrc;
static uint8_t tx_cplt = 0;
static uint8_t* pdata_receive;
static uint16_t data_receive_size = 0;
static uint16_t data_max_size = 0;
static uint32_t data_crc_buf[27];
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
static void bsp_uart_receive_handler(UART_HandleTypeDef* huart, uint16_t size);

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
static bsp_state_t
bsp_uart_convert_byte_to_word(uint8_t* pdata, uint16_t size, uint32_t* buf, uint32_t buf_len);
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
static bsp_state_t
bsp_uart_convert_word_to_byte(uint8_t* pdata, uint16_t size, uint32_t* buf, uint32_t buf_len);
/* Function definitions ----------------------------------------------- */
bsp_state_t bsp_uart_init(bsp_mcu_t* mcu)
{
  BSP_CHECK_NULL(mcu, BSP_STATE_FAIL);
  huart6 = mcu->huart6;
  huart6.RxEventCallback = bsp_uart_receive_handler;
  huart6.TxCpltCallback = bsp_uart_transmit_handler;
  hcrc = mcu->hcrc;
  return BSP_STATE_PASS;
}

bsp_state_t bsp_uart_transmit_start(bsp_config_id_t id, uint8_t* pdata, uint16_t size)
{
  BSP_CHECK_NULL(pdata, BSP_STATE_FAIL);
  BSP_CHECK_RANGE(id, 0, BSP_CONFIG_ID_MAX, BSP_STATE_FAIL);
  BSP_CHECK_NULL(size, BSP_STATE_FAIL);
  if (id == BSP_CONFIG_ID_PROTOCOL)
  {
    uint32_t buf_len, crc_val;
    uint8_t crc_buf[4];
    uint16_t crc_buf_size;
    if (bsp_uart_convert_byte_to_word(pdata, size, data_crc_buf, buf_len) == BSP_STATE_FAIL)
    {
      return BSP_STATE_FAIL;
    }
    crc_val = HAL_CRC_Calculate(&hcrc, data_crc_buf, buf_len);
    if (bsp_uart_convert_byte_to_word(crc_buf, crc_buf_size, &crc_val, 1) == BSP_STATE_FAIL)
    {
      return BSP_STATE_FAIL;
    }
    for (int i = 0; i < 4; i++)
    {
      pdata[size + i] = crc_buf[i];
    }
    if (HAL_UART_Transmit_IT(&huart6, pdata, size + 4) != HAL_OK)
    {
      return BSP_STATE_FAIL;
    }
  }
  return BSP_STATE_PASS;
}

bsp_state_t bsp_uart_receive_start(bsp_config_id_t id, uint8_t* pdata, uint16_t size)
{
  BSP_CHECK_NULL(pdata, BSP_STATE_FAIL);
  BSP_CHECK_RANGE(id, 0, BSP_CONFIG_ID_MAX, BSP_STATE_FAIL);
  BSP_CHECK_NULL(size, BSP_STATE_FAIL);
  if (id == BSP_CONFIG_ID_PROTOCOL)
  {
    data_max_size = size;
    pdata_receive = pdata;
    if (HAL_UARTEx_ReceiveToIdle_IT(&huart6, pdata, size) != HAL_OK)
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

uint16_t bsp_uart_receive_cplt(bsp_config_id_t id)
{
  if (id == BSP_CONFIG_ID_PROTOCOL)
  {
    uint32_t buf_len, crc_val, crc_rcv;
    bsp_uart_convert_byte_to_word(pdata_receive, data_receive_size - 4, data_crc_buf, buf_len);
    crc_val = HAL_CRC_Calculate(&hcrc, data_crc_buf, buf_len);
    crc_rcv = (uint32_t)(*(pdata_receive + data_receive_size - 4)) << 24 + 
              (uint32_t)(*(pdata_receive + data_receive_size - 3)) << 16 + 
              (uint32_t)(*(pdata_receive + data_receive_size - 2)) << 8 + 
              (uint32_t)(*(pdata_receive + data_receive_size - 1));
    if (crc_val != crc_rcv)
    {
      return 0;
    }
    else
    {
      return data_receive_size - 4;
    }
  }
}
/* Private definitions ----------------------------------------------- */
static void bsp_uart_transmit_handler(UART_HandleTypeDef* huart)
{
  tx_cplt = 1;
}

static void bsp_uart_receive_handler(UART_HandleTypeDef* huart, uint16_t size)
{
  data_receive_size = data_max_size - size;
}

static bsp_state_t
bsp_uart_convert_byte_to_word(uint8_t* pdata, uint16_t size, uint32_t* buf, uint32_t buf_len)
{
  BSP_CHECK_NULL(pdata, BSP_STATE_FAIL);
  BSP_CHECK_NULL(size, BSP_STATE_FAIL);
  BSP_CHECK_NULL(buf, BSP_STATE_FAIL);
  uint32_t tmp;
  buf_len = ((size % 4) == 0) ? size / 4 : size / 4 + 1;
  for (int i = 0; i < buf_len; i++)
  {
    tmp = (uint32_t)(*(pdata + 4 * i))
          << 24 + (uint32_t)(*(pdata + 4 * i + 1)) << 16 + (uint32_t)(*(pdata + 4 * i + 2))
          << 8 + (uint32_t)(*(pdata + 4 * i + 3));
    *(buf + i) = tmp;
  }
  return BSP_STATE_PASS;
}

static bsp_state_t
bsp_uart_convert_word_to_byte(uint8_t* pdata, uint16_t size, uint32_t* buf, uint32_t buf_len)
{
  BSP_CHECK_NULL(buf, BSP_STATE_FAIL);
  BSP_CHECK_NULL(buf_len, BSP_STATE_FAIL);
  BSP_CHECK_NULL(pdata, BSP_STATE_FAIL);
  uint8_t tmp;
  uint16_t byte_cnt = 4;
  for (int i = 0; i < 4; i++)
  {
    if ((*(buf + buf_len) & (0x000000FF << (8 * i))) == 0)
      byte_cnt--;
    else
      break;
  }
  size = (buf_len - 1) * 4 + byte_cnt;
  for (int i = 0; i < buf_len; i++)
  {
    *(pdata + 4 * i) = (uint8_t)((*(buf + i) & 0xFF000000) >> 24);
    *(pdata + 4 * i + 1) = (uint8_t)((*(buf + i) & 0x00FF0000) >> 16);
    *(pdata + 4 * i + 2) = (uint8_t)((*(buf + i) & 0x0000FF00) >> 8);
    *(pdata + 4 * i + 3) = (uint8_t)(*(buf + i) & 0x000000FF);
  }
  return BSP_STATE_PASS;
}
/* End of file -------------------------------------------------------- */
