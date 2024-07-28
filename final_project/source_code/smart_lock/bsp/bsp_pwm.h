/**
 * @file       bsp_pwm.h
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    
 * @version    1.0.0
 * @date       2024-07-27
 * @author     Phat Nguyen
 *             
 * @brief      <A brief description of the content of the file>
 *             
 * @note          
 * @example    
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __BSP_PWM_H
#define __BSP_PWM_H

/* Includes ----------------------------------------------------------- */
#include "stm32f4xx_hal.h"
/* Public defines ----------------------------------------------------- */

/* Phat will define this himself.Will be discussed more */

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief <enum definition for result>
 */
typedef enum 
{
  SUCCESS, 
  FAIL,    
}
enum_result_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief  <Create pwm according to input on htim and channel>
 *
 * @param[in]     <*htim>  <htim1, htim2, htim3, or htim4,...>
 * @param[in]     <channel>  <TIM_CHANNEL_1 or TIM_CHANNEL_2 or TIM_CHANNEL_3,..>
 * @param[out]    none
 *
 * @attention  <API attention note>
 *
 * @return  SUCCESS or FAIL
 */
 enum_result_t bsp_pwm_start(TIM_HandleTypedef *htim, uint16_t channel);


 /**
 * @brief  <Stop pwm according to input on htim and channel>
 *
 * @param[in]     <*htim>  <htim1, htim2, htim3, or htim4,...>
 * @param[in]     <channel>  <TIM_CHANNEL_1 or TIM_CHANNEL_2 or TIM_CHANNEL_3,..>
 * @param[out]    none
 *
 * @attention  <API attention note>
 *
 * @return  SUCCESS or FAIL
 */
 enum_result_t bsp_pwm_stop(TIM_HandleTypedef *htim, uint16_t channel);


 /**
 * @brief  <Set duty cycle for pwm>
 *
 * @param[in]     <*htim>  <htim1, htim2, htim3, or htim4,...>
 * @param[in]     <channel>  <TIM_CHANNEL_1 or TIM_CHANNEL_2 or TIM_CHANNEL_3,..>
 * @param[in]     <duty>  <duty cycle: 0-100>
 * @param[out]    none
 *
 * @attention  <API attention note>
 *
 * @return  SUCCESS or FAIL
 */
 enum_result_t bsp_pwm_set_duty(TIM_HandleTypedef *htim, uint16_t channel, uint32_t duty);


#endif // __BSP_PWM_H

/* End of file -------------------------------------------------------- */
