/**
 * @file       bsp_i2c.c
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
 *
 */

/* Includes ----------------------------------------------------------- */
#include "bsp_i2c.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static I2C_HandleTypeDef hi2c1;
static I2C_HandleTypeDef hi2c2;
static uint8_t tx_cplt_i2c1 = 0;
static uint8_t tx_cplt_i2c2 = 0;
static uint8_t rx_cplt_i2c2 = 0;
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
static void bsp_i2c_transmit_handler(I2C_HandleTypeDef* hi2c);

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
static void bsp_i2c_receive_handler(I2C_HandleTypeDef* hi2c);
/* Function definitions ----------------------------------------------- */
bsp_state_t bsp_i2c_init(bsp_mcu_t* mcu)
{
  BSP_CHECK_NULL(mcu, BSP_STATE_FAIL);
  hi2c1 = mcu->hi2c1;
  hi2c2 = mcu->hi2c2;
  hi2c1.MemTxCpltCallback = bsp_i2c_transmit_handler;
  hi2c2.MemTxCpltCallback = bsp_i2c_transmit_handler;
  hi2c2.MemRxCpltCallback = bsp_i2c_receive_handler;
  return BSP_STATE_PASS;
}

bsp_state_t bsp_i2c_transmit_start(bsp_config_id_t id,
                                   uint16_t slave_addr,
                                   uint16_t reg_addr,
                                   uint8_t* pdata,
                                   uint16_t data_size)
{
  BSP_CHECK_NULL(pdata, BSP_STATE_FAIL);
  BSP_CHECK_NULL(data_size, BSP_STATE_FAIL);
  BSP_CHECK_RANGE(id, 0, BSP_CONFIG_ID_MAX, BSP_STATE_FAIL);
  if (id == BSP_CONFIG_ID_RTC)
  {
    if (HAL_I2C_Mem_Write_IT(&hi2c2, slave_addr, reg_addr, I2C_MEMADD_SIZE_8BIT, pdata, data_size) != HAL_OK)
    {
      return BSP_STATE_FAIL;
    }
  }
  else if (id == BSP_CONFIG_ID_OLED)
  {
    if (HAL_I2C_Mem_Write_IT(&hi2c1, slave_addr, reg_addr, I2C_MEMADD_SIZE_8BIT, pdata, data_size) != HAL_OK)
    {
      return BSP_STATE_FAIL;
    }
  }
  return BSP_STATE_PASS;
}

bsp_state_t bsp_i2c_receive_start(bsp_config_id_t id,
                                  uint16_t slave_addr,
                                  uint16_t reg_addr,
                                  uint8_t* pdata,
                                  uint16_t data_size)
{
  BSP_CHECK_NULL(pdata, BSP_STATE_FAIL);
  BSP_CHECK_NULL(data_size, BSP_STATE_FAIL);
  BSP_CHECK_RANGE(id, 0, BSP_CONFIG_ID_MAX, BSP_STATE_FAIL);
  if (id == BSP_CONFIG_ID_RTC)
  {
    if (HAL_I2C_Mem_Read_IT(&hi2c2, slave_addr, reg_addr, I2C_MEMADD_SIZE_8BIT, pdata, data_size) != HAL_OK)
    {
      return BSP_STATE_FAIL;
    }
  }
  return BSP_STATE_PASS;
}

uint8_t bsp_i2c_transmit_cplt(bsp_config_id_t id)
{
  if (id == BSP_CONFIG_ID_RTC)
  {
    uint8_t ret_flag = 0;
    ret_flag = tx_cplt_i2c2;
    if (tx_cplt_i2c2 == 1)
    {
      tx_cplt_i2c2 = 0;
    }
    return ret_flag;
  }
  else if (id == BSP_CONFIG_ID_OLED)
  {
    uint8_t ret_flag = 0;
    ret_flag = tx_cplt_i2c1;
    if (tx_cplt_i2c1 == 1)
    {
      tx_cplt_i2c1 = 0;
    }
    return ret_flag;
  }
}

uint8_t bsp_i2c_receive_cplt(bsp_config_id_t id)
{
  if (id == BSP_CONFIG_ID_RTC)
  {
    uint8_t ret_flag = 0;
    ret_flag = rx_cplt_i2c2;
    if (rx_cplt_i2c2 == 1)
    {
      rx_cplt_i2c2 = 0;
    }
    return ret_flag;
  }
}
/* Private definitions ----------------------------------------------- */
static void bsp_i2c_transmit_handler(I2C_HandleTypeDef* hi2c)
{
  if (hi2c->Instance == I2C1)
  {
    tx_cplt_i2c1 = 1;
  }
  else if (hi2c->Instance == I2C2)
  {
    tx_cplt_i2c2 = 1;
  }
}

static void bsp_i2c_receive_handler(I2C_HandleTypeDef* hi2c)
{
  rx_cplt_i2c2 = 1;
}
/* End of file -------------------------------------------------------- */
