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
#include "bsp_state.h"
#include "bsp_config.h"
#include "bsp_mcu.h"

/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief  <initialize private handler for timer>
 *
 * @param[in]     mcu       <struct manage MCU peripheral>
 *
 * @attention  <This API will be call right after mcu init in system init>
 *
 * @return
 * - 0: BSP_STATE_FAIL
 * - 1: BSP_STATE_PASS
 */
bsp_state_t bsp_pwm_init(bsp_mcu_t* mcu);

/**
 * @brief  <Starting output pwm pulse with duty cycle base initial configuration>
 *
 * @param[in]     id       <driver ID to identify which peripheral needed>
 * @param[in]     channel  <TIM_CHANNEL_1 or TIM_CHANNEL_2 or TIM_CHANNEL_3,..>
 *
 * @attention  <API attention note>
 *
 * @return
 * - 0: BSP_STATE_FAIL
 * - 1: BSP_STATE_PASS
 */
bsp_state_t bsp_pwm_start(bsp_config_id_t id, uint32_t channel);

/**
 * @brief  <Stop output pwm pulse>
 *
 * @param[in]     id       <driver ID to identify which peripheral needed>
 * @param[in]     channel  <TIM_CHANNEL_1 or TIM_CHANNEL_2 or TIM_CHANNEL_3,..>
 *
 * @attention  <API attention note>
 *
 * @return
 * - 0: BSP_STATE_FAIL
 * - 1: BSP_STATE_PASS
 */
bsp_state_t bsp_pwm_stop(bsp_config_id_t id, uint32_t channel);

/**
 * @brief  <Set duty cycle for pwm>
 *
 * @param[in]     id         <driver ID to identify which peripheral needed>
 * @param[in]     channel  <TIM_CHANNEL_1 or TIM_CHANNEL_2 or TIM_CHANNEL_3,..>
 * @param[in]     duty     <duty cycle: 0-100>
 *
 * @attention  <API attention note>
 *
 * @return
 * - 0: BSP_STATE_FAIL
 * - 1: BSP_STATE_PASS
 */
bsp_state_t bsp_pwm_set_duty(bsp_config_id_t id, uint32_t channel, uint32_t duty);

/**
 * @brief  <Set duty cycle for pwm>
 *
 * @param[in]     id         <driver ID to identify which peripheral needed>
 * @param[in]     channel  <TIM_CHANNEL_1 or TIM_CHANNEL_2 or TIM_CHANNEL_3,..>
 * @param[in]     period     <autoreload counter: 0-65535>
 *
 * @attention  <API attention note>
 *
 * @return
 * - 0: BSP_STATE_FAIL
 * - 1: BSP_STATE_PASS
 */
bsp_state_t bsp_pwm_set_duty(bsp_config_id_t id, uint32_t channel, uint32_t period);
#endif // __BSP_PWM_H

/* End of file -------------------------------------------------------- */
