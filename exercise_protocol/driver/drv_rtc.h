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
#define PUBLIC_DEFINE_1  (0) /*!< Description of PUBLIC_DEFINE_1 */
#define PUBLIC_DEFINE_2  (0) /*!< Description of PUBLIC_DEFINE_2 */

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief <enum descriptiton>
 */
typedef enum 
{
  DRV_RTC_REG_SECOND = 0x00, /**< Description of PUBLIC_ENUM_1 */
  DRV_RTC_REG_MINUTE = 0x01, /**< Description of PUBLIC_ENUM_2 */
  DRV_RTC_REG_HOUR = 0x02,
  DRV_RTC_REG_DAY = 0x03,
  DRV_RTC_REG_DATE = 0x04,
  DRV_RTC_REG_MONTH = 0x05,
  DRV_RTC_REG_YEAR = 0x06,
  DRV_RTC_REG_CONTROL = 0x07    /**< Description of PUBLIC_ENUM_3 */
}
drv_rtc_reg_t;

/**
 * @brief <structure descriptiton>
 */
typedef struct 
{
  drv_rtc_reg_t reg; /**< Description of member_1 */
  drv_mcu_pin_t data_pin; /**< Description of member_2 */
  drv_mcu_pin_t clk_pin;  /**< Description of member_3 */
}
drv_rtc_t;

/* Public macros ------------------------------------------------------ */
/**
 * @brief  <macro description>
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
#define PUBLIC_MACRO(a)  do_something_with(a)

/* Public variables --------------------------------------------------- */
extern int g_var_1; /**< Description of public variable g_var_1 */
extern int g_var_2; /**< Description of public variable g_var_2 */

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
 drv_state_t drv_rtc_read(drv_mcu_t* v_dmcu, drv_rtc_t* v_drtc);
 drv_state_t drv_rtc_write(drv_mcu_t* v_dmcu, drv_rtc_t* v_drtc);
 

#endif // __CODE_TEMPLATE_H

/* End of file -------------------------------------------------------- */
