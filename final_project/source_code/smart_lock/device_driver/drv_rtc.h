/**
 * @file       drv_rtc.h
 * @copyright  
 * @license    
 * @version    1.0.0
 * @date       2024-08-05
 * @author     Phat Nguyen Tan
 * @author     
 *
 * @brief      <This file is header file for DS1307 RTC module>
 *
 * @note
 * @example    
 *             
 * @example    
 *             
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __DRV_RTC_H
#define __DRV_RTC_H

/* Includes ----------------------------------------------------------- */
#include "bsp_config.h"
#include "bsp_state.h"
#include "bsp_i2c.h"

/* Public defines ----------------------------------------------------- */
#define DS1307_ADDRESS       (0x68 << 1) 

/* rtc register ID */
#define DRV_RTC_REG_SECOND   (0x00)
#define DRV_RTC_REG_MINUTE   (0x01)
#define DRV_RTC_REG_HOUR     (0x02)
#define DRV_RTC_REG_DAY      (0x03)
#define DRV_RTC_REG_DATE     (0x04)
#define DRV_RTC_REG_MONTH    (0x05)
#define DRV_RTC_REG_YEAR     (0x06)
#define DRV_RTC_REG_CONTROL  (0x07)

/* rtc day ID */
#define DRV_RTC_DAY_SUN      (0x01)
#define DRV_RTC_DAY_MON      (0x02)
#define DRV_RTC_DAY_TUE      (0x03)
#define DRV_RTC_DAY_WES      (0x04)
#define DRV_RTC_DAY_THU      (0x05)
#define DRV_RTC_DAY_FRI      (0x06)
#define DRV_RTC_DAY_SAT      (0x07)

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief <This enum defines the executable code state for the DS1307 RTC module>
 */
typedef enum
{
  DRV_RTC_STATUS_FAIL,
  DRV_RTC_STATUS_OK
} drv_rtc_status_t;


/**
 * @brief <This structure defines components to control the DS1307 RTC module>
 */
typedef struct
{
  bsp_state_t (*i2c_write)(bsp_config_id_t id, uint16_t slv_addr, uint16_t reg_addr, uint8_t *pdata, uin32_t size);
  bsp_state_t (*i2c_read)(bsp_config_id_t id, uint16_t slv_addr, uint16_t reg_addr, uint8_t *pdata, uin32_t size);
  uint8_t (*i2c_read_cplt)(bsp_config_id_t id);
  uint8_t (*i2c_write_cplt)(bsp_config_id_t id);
  uint16_t dev_addr;
} drv_rtc_t;


/**
 * @brief <>
 */
typedef struct
{
  uint8_t second; 
  uint8_t minute; 
  uint8_t hour;
  uint8_t day;
  uint8_t date;
  uint8_t month;
  uint8_t year; 
} drv_rtc_time_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief  <This function utilized to init DS1307 RTC module>
 *
 * @param[in]     <drv_rtc_t *rtc>  <pointer to a struct type>
 * @param[out]    None
 * @param[inout]  None
 *
 * @attention  <API attention note>
 *
 * @return
 *  - 0: DRV_RTC_STATUS_FAIL
 *  - 1: DRV_RTC_STATUS_OK
 */
drv_rtc_status_t drv_rtc_init(drv_rtc_t *rtc);


/**
 * @brief  <This function utilized to read data from DS1307 RTC module>
 *
 * @param[in]     <drv_rtc_t *rtc>  <pointer to a struct type>
 * @param[out]    None
 * @param[inout]  None
 *
 * @attention  <API attention note>
 *
 * @return
 *  - 0: DRV_RTC_STATUS_FAIL
 *  - 1: DRV_RTC_STATUS_OK
 */
drv_rtc_status_t drv_rtc_read_start(drv_rtc_t *rtc);


/**
 * @brief  <This function utilized to write time data to DS1307 RTC module>
 *
 * @param[in]     <drv_rtc_t *rtc>  <pointer to a struct type>
 * @param[in]     <drv_rtc_time_t time>  <data of time which user set>
 * @param[out]    None
 * @param[inout]  None
 *
 * @attention  <API attention note>
 *
 * @return
 *  - 0: DRV_RTC_STATUS_FAIL
 *  - 1: DRV_RTC_STATUS_OK
 */
drv_rtc_status_t drv_rtc_write(drv_rtc_t *rtc, drv_rtc_time_t time);


/**
 * @brief  <This function utilized to check if read function completed>
 *
 * @param[in]     <drv_rtc_t *rtc>  <pointer to a struct type>
 * @param[out]    None
 * @param[inout]  None
 *
 * @attention  <API attention note>
 *
 * @return time
 */
drv_rtc_time_t drv_rtc_read_complete(drv_rtc_t *rtc);

#endif // __DRV_RTC_H

/* End of file -------------------------------------------------------- */
