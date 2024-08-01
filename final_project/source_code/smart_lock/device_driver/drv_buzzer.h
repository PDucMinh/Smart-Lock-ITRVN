/**
 * @file       drv_buzzer.h
 * @copyright  
 * @license    
 * @version    1.0.0
 * @date       2024-07-31
 * @author     Phat Nguyen Tan
 * @author     
 *             
 * @brief      <This file is header file for buzzer>
 *             
 * @note          
 * @example    
 *             
 * @example    
 *             
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __DRV_BUZZER_H
#define __DRV_BUZZER_H

/* Includes ----------------------------------------------------------- */
#include "bsp_config.h"
#include "bsp_pwm.h"
#include "scheduler.h"
/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief <This enum defines the executable code state for the buzzer>
 */
typedef enum 
{
  DRV_BUZZER_STATUS_FAIL,    /**< Execute error */
  DRV_BUZZER_STATUS_SUCCESS, /**< Execute success */
}
drv_buzzer_status_t;

/**
 * @brief <This structure defines the component to control the buzzer>
 */
typedef struct 
{
  bsp_state_t (*pwm_set_freq)(bsp_config_id_t id, uint32_t channel, uint32_t period); /**< Set timer cycle */
  bsp_state_t (*pwm_start)(bsp_config_id_t id, uint32_t channel); /**< Start pwm channel, depend on user set */
  bsp_state_t (*pwm_stop)(bsp_config_id_t id, uint32_t channel);  /**< Stop pwm channel, depend on user set */
  bsp_state_t (*pwm_set_duty)(bsp_config_id_t id, uint32_t channel, uint32_t duty);
}
drv_buzzer_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief  <This function utilized to init buzzer>
 *
 * @param[in]     <drv_buzzer_t *buzzer>  <pointer to a struct type>
 * @param[out]    None
 * @param[inout]  None
 *
 * @attention  <API attention note>
 *
 * @return  
 *  - 0: DRV_BUZZER_STATUS_FAIL
 *  - 1: DRV_BUZZER_STATUS_SUCCESS
 */
 drv_buzzer_status_t drv_buzzer_init(drv_buzzer_t *buzzer);


 /**
 * @brief  <This function utilized to set frequency and duaration of this frequency for buzzer>
 *
 * @param[in]     <drv_buzzer_t *buzzer>  <pointer to a struct type>
 * @param[in]     <note>                  <set frequency for buzzer>
 * @param[in]     <duration>              <set duration for above frequency>
 * @param[out]    None
 * @param[inout]  None
 *
 * @attention  <API attention note>
 *
 * @return  
 *  - 0: DRV_BUZZER_STATUS_FAIL
 *  - 1: DRV_BUZZER_STATUS_SUCCESS
 */
 drv_buzzer_status_t drv_buzzer_set_note(drv_buzzer_t *buzzer, uint16_t note, uint32_t duration);


/**
 * @brief  <This function utilized to to receive flag duration callback and stop pwm>
 *
 * @param[in]     <drv_buzzer_t *buzzer>  <pointer to a struct type>
 * @param[out]    None
 * @param[inout]  None
 *
 * @attention  <API attention note>
 *
 * @return  
 */
 uint8_t drv_buzzer_duration_cplt(drv_buzzer_t *buzzer);

/**
 * @brief  <This function utilized to to receive flag duration callback and stop pwm>
 *
 * @param[in]     <drv_buzzer_t *buzzer>  <pointer to a struct type>
 * @param[out]    None
 * @param[inout]  None
 *
 * @attention  <API attention note>
 *
 * @return  
 */
drv_buzzer_status_t drv_buzzer_active(drv_buzzer_t *buzzer);

/**
 * @brief  <This function utilized to to receive flag duration callback and stop pwm>
 *
 * @param[in]     <drv_buzzer_t *buzzer>  <pointer to a struct type>
 * @param[out]    None
 * @param[inout]  None
 *
 * @attention  <API attention note>
 *
 * @return  
 */
drv_buzzer_status_t drv_buzzer_deactive(drv_buzzer_t *buzzer);
#endif // __DRV_BUZZER_H

/* End of file -------------------------------------------------------- */
