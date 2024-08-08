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
/* rtc register ID */
#define DRV_RTC_REG_SECOND (0x00)
#define DRV_RTC_REG_MINUTE (0x01)
#define DRV_RTC_REG_HOUR (0x02)
#define DRV_RTC_REG_DAY (0x03)
#define DRV_RTC_REG_DATE (0x04)
#define DRV_RTC_REG_MONTH (0x05)
#define DRV_RTC_REG_YEAR (0x06)
#define DRV_RTC_REG_CONTROL (0x07)

/* rtc day ID */
#define DRV_RTC_DAY_SUN (0x01)
#define DRV_RTC_DAY_MON (0x02)
#define DRV_RTC_DAY_TUE (0x03)
#define DRV_RTC_DAY_WES (0x04)
#define DRV_RTC_DAY_THU (0x05)
#define DRV_RTC_DAY_FRI (0x06)
#define DRV_RTC_DAY_SAT (0x07)
/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static uint8_t drv_rtc_rx_data[7];
static uint8_t drv_rtc_tx_data[7];
/* Private function prototypes ---------------------------------------- */
uint8_t drv_rtc_decode_BCD(uint8_t binary);
uint8_t drv_rtc_encode_BCD(uint8_t decimal);

/* Function definitions ----------------------------------------------- */
drv_rtc_status_t drv_rtc_init(drv_rtc_t* rtc)
{
  if (rtc == NULL)
  {
    return DRV_RTC_STATUS_FAIL;
  }
  rtc->i2c_write = bsp_i2c_transmit_start;
  rtc->i2c_read = bsp_i2c_receive_start;
  rtc->i2c_read_cplt = bsp_i2c_receive_cplt;
  rtc->i2c_write_cplt = bsp_i2c_transmit_cplt;
  rtc->dev_addr = DRV_RTC_ADDRESS;

  return DRV_RTC_STATUS_OK;
}

drv_rtc_status_t drv_rtc_write(drv_rtc_t* rtc, drv_rtc_time_t time)
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
  drv_rtc_tx_data[6] = drv_rtc_encode_BCD(time.year);
  drv_rtc_tx_data[5] = drv_rtc_encode_BCD(time.month);
  drv_rtc_tx_data[4] = drv_rtc_encode_BCD(time.date);
  drv_rtc_tx_data[3] = drv_rtc_encode_BCD(time.day);
  drv_rtc_tx_data[2] = drv_rtc_encode_BCD(time.hour);
  drv_rtc_tx_data[1] = drv_rtc_encode_BCD(time.minute);
  drv_rtc_tx_data[0] = drv_rtc_encode_BCD(time.second);

  // Define the starting register address for the data
  uint16_t start_reg_addr = DRV_RTC_REG_SECOND;

  // Set time
  if (rtc->i2c_write(BSP_CONFIG_ID_RTC,
                     rtc->dev_addr,
                     start_reg_addr,
                     drv_rtc_tx_data,
                     sizeof(drv_rtc_tx_data)) != BSP_STATE_PASS)
    return DRV_RTC_STATUS_FAIL;

  return DRV_RTC_STATUS_OK;
}

drv_rtc_status_t drv_rtc_read_start(drv_rtc_t* rtc)
{
  // Define the starting register address for the data
  uint16_t start_reg_addr = DRV_RTC_REG_SECOND;

  // Get time
  if (rtc->i2c_read(BSP_CONFIG_ID_RTC,
                    rtc->dev_addr,
                    start_reg_addr,
                    drv_rtc_rx_data,
                    sizeof(drv_rtc_rx_data)) != BSP_STATE_PASS)
    ;
  return DRV_RTC_STATUS_FAIL;

  return DRV_RTC_STATUS_OK;
}

drv_rtc_status_t drv_rtc_read_cplt(drv_rtc_t* rtc)
{
  if (rtc->i2c_read_cplt(BSP_CONFIG_ID_RTC) == 1)
  {
    return DRV_RTC_STATUS_OK;
  }
  return DRV_RTC_STATUS_FAIL;
}

drv_rtc_time_t drv_rtc_get_data(void)
{
  drv_rtc_time_t return_time;
  return_time.second = drv_rtc_decode_BCD(drv_rtc_rx_data[0]);
  return_time.minute = drv_rtc_decode_BCD(drv_rtc_rx_data[1]);
  return_time.hour = drv_rtc_decode_BCD(drv_rtc_rx_data[2]);
  return_time.day = drv_rtc_decode_BCD(drv_rtc_rx_data[3]);
  return_time.date = drv_rtc_decode_BCD(drv_rtc_rx_data[4]);
  return_time.month = drv_rtc_decode_BCD(drv_rtc_rx_data[5]);
  return_time.year = drv_rtc_decode_BCD(drv_rtc_rx_data[6]);
  return return_time;
}

/* Private definitions ----------------------------------------------- */
uint8_t drv_rtc_decode_BCD(uint8_t binary)
{
  return ((binary & 0x0F) + ((binary & 0xF0) >> 4) * 10);
}

uint8_t drv_rtc_encode_BCD(uint8_t decimal)
{
  return ((decimal / 10) << 4) | (decimal % 10);
}

/* End of file -------------------------------------------------------- */
