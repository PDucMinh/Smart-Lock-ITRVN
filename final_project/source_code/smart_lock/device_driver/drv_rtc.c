/**
 * @file       drv_rtc.c
 * @copyright
 * @license
 * @version    1.0.0
 * @date       2024-08-05
 * @author     Phat Nguyen Tan
 * @author
 *
 * @brief      <This file is source code file to define functions for DS1307 RTC module>
 *
 * @note
 */

/* Includes ----------------------------------------------------------- */
#include "drv_rtc.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static uint8_t ds1307_rx_data[7];

/* Private function prototypes ---------------------------------------- */
uint8_t ds1307_decode_BCD(uint8_t binary);
uint8_t ds1307_encode_BCD(uint8_t decimal);

/* Function definitions ----------------------------------------------- */
drv_rtc_status_t drv_rtc_init(drv_rtc_t *rtc)
{
  if (rtc == NULL)
  {
    return DRV_RTC_STATUS_FAIL;
  }
  rtc->i2c_write = bsp_i2c_transmit_start;
  rtc->i2c_read = bsp_i2c_receive_start;
  rtc->i2c_read_cplt = bsp_i2c_receive_cplt;
  rtc->i2c_write_cplt = bsp_i2c_transmit_cplt;
  rtc->dev_addr = DS1307_ADDRESS;

  return DRV_RTC_STATUS_OK;
}


drv_rtc_status_t drv_rtc_write(drv_rtc_t *rtc, drv_rtc_time_t time)
{
  if (rtc == NULL)
  {
    return DRV_RTC_STATUS_FAIL;
  }
  
  // Check if data is valid
  if ((time.year < 0) || (time.year > 99))
    return DRV_RTC_STATUS_FAIL;
  if ((time.month < 1) || (time.month > 12))
    return DRV_RTC_STATUS_FAIL;
  if ((time.date < 1) || (time.date > 31))
    return DRV_RTC_STATUS_FAIL;
  if ((time.day < 1) || (time.day > 7))
    return DRV_RTC_STATUS_FAIL;
  if ((time.hour < 0) || (time.hour > 23))
    return DRV_RTC_STATUS_FAIL;
  if ((time.minute < 0) || (time.minute > 59))
    return DRV_RTC_STATUS_FAIL;
  if ((time.second < 0) || (time.second > 59))
    return DRV_RTC_STATUS_FAIL;

  // Decode data 
  uint8_t year, month, date, day, hour, minute, second;
  year = ds1307_encode_BCD(time.year);
  month = ds1307_encode_BCD(time.month);
  date = ds1307_encode_BCD(time.date);
  day = ds1307_encode_BCD(time.day);
  hour = ds1307_encode_BCD(time.hour);
  minute = ds1307_encode_BCD(time.minute);
  second = ds1307_encode_BCD(time.second);

  // Buffer to transmit
  uint8_t transmit_data[7] = {second,
                              minute,
                              hour,
                              day,
                              date,
                              month,
                              year};
  
  // Define the starting register address for the data
  uint16_t start_reg_addr = DRV_RTC_REG_SECOND;

  // Set time 
  if (rtc->i2c_write(BSP_CONFIG_ID_RTC, rtc->dev_addr, start_reg_addr, transmit_data, sizeof(transmit_data)) != BSP_STATE_PASS)
    return DRV_RTC_STATUS_FAIL;

  return DRV_RTC_STATUS_OK;
}


drv_rtc_status_t drv_rtc_read_start(drv_rtc_t *rtc)
{
  // Define the starting register address for the data
  uint16_t start_reg_addr = DRV_RTC_REG_SECOND;

  // Get time
  if (rtc->i2c_read(BSP_CONFIG_ID_RTC, rtc->dev_addr, start_reg_addr, ds1307_rx_data, sizeof(ds1307_rx_data) != BSP_STATE_PASS));
    return DRV_RTC_STATUS_FAIL;

  return DRV_RTC_STATUS_OK;
}


drv_rtc_time_t drv_rtc_read_complete(drv_rtc_t *rtc)
{
  drv_rtc_time_t return_time;

  if (rtc->i2c_read_cplt(BSP_CONFIG_ID_RTC) == 1)
  {
    ds1307_rx_data[0] = ds1307_decode_BCD(ds1307_rx_data[0]);
    ds1307_rx_data[1] = ds1307_decode_BCD(ds1307_rx_data[1]);
    ds1307_rx_data[2] = ds1307_decode_BCD(ds1307_rx_data[2]);
    ds1307_rx_data[3] = ds1307_decode_BCD(ds1307_rx_data[3]);
    ds1307_rx_data[4] = ds1307_decode_BCD(ds1307_rx_data[4]);
    ds1307_rx_data[5] = ds1307_decode_BCD(ds1307_rx_data[5]);
    ds1307_rx_data[6] = ds1307_decode_BCD(ds1307_rx_data[6]);

    if ((ds1307_rx_data[6] >= 0) && (ds1307_rx_data[6] <= 99))
      return_time.year = ds1307_rx_data[6];

    if ((ds1307_rx_data[5] >= 1) && (ds1307_rx_data[5] <= 12))
      return_time.month = ds1307_rx_data[5];

    if ((ds1307_rx_data[4] >= 1) && (ds1307_rx_data[4] <= 31))
      return_time.date = ds1307_rx_data[4];

    if ((ds1307_rx_data[3] >= 1) && (ds1307_rx_data[3] <= 7))
      return_time.day = ds1307_rx_data[3];

    if ((ds1307_rx_data[2] >= 0) && (ds1307_rx_data[2] <= 23))
      return_time.hour = ds1307_rx_data[2];

    if ((ds1307_rx_data[1] >= 0) && (ds1307_rx_data[1] <= 59))
      return_time.minute = ds1307_rx_data[1];

    if ((ds1307_rx_data[0] >= 0) && (ds1307_rx_data[0] <= 59))
      return_time.second = ds1307_rx_data[0];
  }
  else
  {
    return_time.second = 0;
    return_time.minute = 0;
    return_time.hour = 0;
    return_time.day = 0;
    return_time.date = 0;
    return_time.month = 0;
    return_time.year = 0;
  }
    
  return return_time;
}

/* Private definitions ----------------------------------------------- */
uint8_t ds1307_decode_BCD(uint8_t binary)
{
  return ((binary & 0x0F) + ((binary & 0xF0) >> 4) * 10);
}

uint8_t ds1307_encode_BCD(uint8_t decimal)
{
  return ((decimal / 10) << 4) | (decimal % 10);
}

/* End of file -------------------------------------------------------- */
