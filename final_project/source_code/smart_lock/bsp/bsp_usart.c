/**
 * @file       bsp_usart.c
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license
 * @version    1.0.0
 * @date       2024-08-03
 * @author     Hung Nguyen
 *
 * @brief      <A brief description of the content of the file>
 *
 * @note
 * @example
 */

/* Includes ----------------------------------------------------------- */
#include "bsp_usart.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static USART_HandleTypeDef husart2;
static uint8_t rcv_flag = 0;
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
static void bsp_usart_receive_handler(USART_HandleTypeDef* husart);
/* Function definitions ----------------------------------------------- */
bsp_state_t bsp_usart_init(bsp_mcu_t* mcu)
{
  BSP_CHECK_NULL(mcu, BSP_STATE_FAIL);
  husart2 = mcu->husart2;
  husart2.RxCpltCallback = bsp_usart_receive_handler;
  return BSP_STATE_PASS;
}

bsp_state_t bsp_usart_receive_start(bsp_config_id_t id, uint8_t* pdata, uint16_t size)
{
  BSP_CHECK_NULL(pdata, BSP_STATE_FAIL);
  BSP_CHECK_NULL(size, BSP_STATE_FAIL);
  BSP_CHECK_RANGE(id, BSP_CONFIG_ID_MAX, BSP_STATE_FAIL);
  if (id == BSP_CONFIG_ID_KEYPAD)
  {
    if (HAL_USART_Receive_IT(&husart2, pdata, size) != HAL_OK)
    {
      return BSP_STATE_FAIL;
    }
  }
  return BSP_STATE_PASS;
}

uint8_t bsp_usart_receive_cplt(bsp_config_id_t id)
{
  if (id == BSP_CONFIG_ID_KEYPAD)
  {
    uint8_t ret_flag;
    ret_flag = rcv_flag;
    if (rcv_flag == 1)
    {
        rcv_flag = 0;
    }
    return ret_flag;
  }
}
/* Private definitions ----------------------------------------------- */
static void bsp_usart_receive_handler(USART_HandleTypeDef* husart)
{
  if (husart->Instance == USART2)
  {
    rcv_flag = 1;
  }
}
/* End of file -------------------------------------------------------- */
