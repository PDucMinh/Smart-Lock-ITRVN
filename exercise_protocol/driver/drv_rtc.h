/**
 * @file       drv_rtc.h
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    major.minor.patch
 * @date       yyyy-mm-dd
 * @author     <first_name_1> <last_name_1>
 * @author     <first_name_2> <last_name_2>
 *             
 * @brief      <A brief description of the content of the file>
 *             
 * @note          
 * @example    example_file_1.c
 *             Example_1 description
 * @example    example_file_2.c
 *             Example_2 description
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __DRV_RTC_H
#define __DRV_RTC_H

/* Includes ----------------------------------------------------------- */
#include "drv_mcu.h"
/* Public defines ----------------------------------------------------- */
/* rtc register ID */
#define DRV_RTC_REG_SECOND  (0x00)
#define DRV_RTC_REG_MINUTE  (0x01)
#define DRV_RTC_REG_HOUR    (0x02)
#define DRV_RTC_REG_DAY     (0x03)
#define DRV_RTC_REG_DATE    (0x04)
#define DRV_RTC_REG_MONTH   (0x05)
#define DRV_RTC_REG_YEAR    (0x06)
#define DRV_RTC_REG_CONTROL (0x07)

/* rtc day ID */
#define DRV_RTC_DAY_SUN  (0x01)
#define DRV_RTC_DAY_MON  (0x02)
#define DRV_RTC_DAY_TUE  (0x03)
#define DRV_RTC_DAY_WES  (0x04)
#define DRV_RTC_DAY_THU  (0x05)
#define DRV_RTC_DAY_FRI  (0x06)
#define DRV_RTC_DAY_SAT  (0x07)

/* Public enumerate/structure ----------------------------------------- */

/**
 * @brief <structure descriptiton>
 */
typedef struct 
{
  drv_mcu_pin_t data_pin; /**< Description of member_2 */
  drv_mcu_pin_t clk_pin;  /**< Description of member_3 */
}
drv_rtc_t;

/**
 * @brief <structure descriptiton>
 */
typedef struct 
{
  uint8_t second; /**< Description of member_1 */
  uint8_t minute; /**< Description of member_2 */
  uint8_t hour;
  uint8_t day;
  uint8_t date;
  uint8_t month;
  uint8_t year;  /**< Description of member_3 */
}
drv_rtc_time_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
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
 drv_state_t drv_rtc_init(drv_mcu_t* v_dmcu, drv_rtc_t* v_drtc);
 drv_state_t drv_rtc_enable_clk(drv_mcu_t* v_dmcu, drv_rtc_t* v_drtc);
 drv_rtc_time_t drv_rtc_read(drv_mcu_t* v_dmcu);
 drv_state_t drv_rtc_write(drv_mcu_t* v_dmcu, drv_rtc_time_t v_dtime);
 

#endif // __DRV_RTC_H

/* End of file -------------------------------------------------------- */
