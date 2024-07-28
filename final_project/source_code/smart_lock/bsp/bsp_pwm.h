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

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief  <Create pwm according to input on htim and channel>
 *
 * @param[in]     <*htim>  <TIM1, TIM2, TIM3,...>
 * @param[in]     <channel>  <CHANNEL_1 or CHANNEL_2 or CHANNEL_3,..>
 * @param[out]    none
 *
 * @attention  <API attention note>
 *
 * @return  None
 */
 void bsp_pwm_start(TIM_HandleTypedef *htim, uint16_t channel);


 /**
 * @brief  <Stop pwm according to input on htim and channel>
 *
 * @param[in]     <*htim>  <TIM1, TIM2, TIM3,...>
 * @param[in]     <channel>  <CHANNEL_1 or CHANNEL_2 or CHANNEL_3,..>
 * @param[out]    none
 *
 * @attention  <API attention note>
 *
 * @return  None
 */
 void bsp_pwm_stop(TIM_HandleTypedef *htim, uint16_t channel);


 /**
 * @brief  <Set duty cycle for pwm>
 *
 * @param[in]     <*htim>  <TIM1, TIM2, TIM3,...>
 * @param[in]     <channel>  <CHANNEL_1 or CHANNEL_2 or CHANNEL_3,..>
 * @param[in]     <duty>  <duty cycle: 0-100>
 * @param[out]    none
 *
 * @attention  <API attention note>
 *
 * @return  None
 */
 void bsp_pwm_set_duty(TIM_HandleTypedef *htim, uint16_t channel, uint32_t duty);


#endif // __BSP_PWM_H

/* End of file -------------------------------------------------------- */
