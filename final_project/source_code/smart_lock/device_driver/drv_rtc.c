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

/* Private function prototypes ---------------------------------------- */


/* Function definitions ----------------------------------------------- */
drv_rtc_status_t drv_rtc_init(drv_rtc_t *rtc)
{
  if (rtc == NULL)
  {
    return DRV_RTC_STATUS_FAIL;
  }
  rtc->i2c_write = bsp_i2c_write;
  rtc->i2c_read = bsp_i2c_read;
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
  uint8_t transmit_data[2] = {0};

  // Set year
  transmit_data[0] = DRV_RTC_REG_YEAR;
  transmit_data[1] = year;
  if (rtc->i2c_write(BSP_CONFIG_ID_RTC, rtc->dev_addr, transmit_data, sizeof(transmit_data)) != BSP_STATE_PASS)
    return DRV_RTC_STATUS_FAIL;

  // Set month
  transmit_data[0] = DRV_RTC_REG_MONTH;
  transmit_data[1] = month;
  if (rtc->i2c_write(BSP_CONFIG_ID_RTC, rtc->dev_addr, transmit_data, sizeof(transmit_data)) != BSP_STATE_PASS)
    return DRV_RTC_STATUS_FAIL;

  // Set date
  transmit_data[0] = DRV_RTC_REG_DATE;
  transmit_data[1] = date;
  if (rtc->i2c_write(BSP_CONFIG_ID_RTC, rtc->dev_addr, transmit_data, sizeof(transmit_data)) != BSP_STATE_PASS)
    return DRV_RTC_STATUS_FAIL;

  // Set day
  transmit_data[0] = DRV_RTC_REG_DAY;
  transmit_data[1] = day;
  if (rtc->i2c_write(BSP_CONFIG_ID_RTC, rtc->dev_addr, transmit_data, sizeof(transmit_data)) != BSP_STATE_PASS)
    return DRV_RTC_STATUS_FAIL;

  // Set hour
  transmit_data[0] = DRV_RTC_REG_HOUR;
  transmit_data[1] = hour;
  if (rtc->i2c_write(BSP_CONFIG_ID_RTC, rtc->dev_addr, transmit_data, sizeof(transmit_data)) != BSP_STATE_PASS)
    return DRV_RTC_STATUS_FAIL;

  // Set minute
  transmit_data[0] = DRV_RTC_REG_MINUTE;
  transmit_data[1] = minute;
  if (rtc->i2c_write(BSP_CONFIG_ID_RTC, rtc->dev_addr, transmit_data, sizeof(transmit_data)) != BSP_STATE_PASS)
    return DRV_RTC_STATUS_FAIL;

  // Set second
  transmit_data[0] = DRV_RTC_REG_SECOND;
  transmit_data[1] = second;
  if (rtc->i2c_write(BSP_CONFIG_ID_RTC, rtc->dev_addr, transmit_data, sizeof(transmit_data)) != BSP_STATE_PASS)
    return DRV_RTC_STATUS_FAIL;

  return DRV_RTC_STATUS_OK;
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