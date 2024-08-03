/**
 * @file       drv_keypad.h
 * @copyright  
 * @license
 * @version    1.0.0
 * @date       2024-08-01
 * @author     Phat Nguyen Tan
 * @author     
 *
 * @brief      <This file is header file for TTP 229 keypad module>
 *             <Using 16 inputs, 16 serial outputs, single key mode, active low>
 * @note
 * @example    
 *             
 * @example    
 *             
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __DRV_KEYPAD_H
#define __DRV_KEYPAD_H

/* Includes ----------------------------------------------------------- */
#include "bsp_config.h"
#include "bsp_usart.h"

/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief <keypad API status>
 */
typedef enum
{
  DRV_KEYPAD_STATUS_FAIL,    /**< Execute error */
  DRV_KEYPAD_STATUS_SUCCESS, /**< Execute success */
} drv_keypad_status_t;


/**
 * @brief <this enum defines "16 key and 1 error" input status for TTP229 module>
 */
typedef enum
{
  DRV_KEYPAD_BUTTON_0,
  DRV_KEYPAD_BUTTON_1,
  DRV_KEYPAD_BUTTON_2,
  DRV_KEYPAD_BUTTON_3,
  DRV_KEYPAD_BUTTON_4,
  DRV_KEYPAD_BUTTON_5,
  DRV_KEYPAD_BUTTON_6,
  DRV_KEYPAD_BUTTON_7,
  DRV_KEYPAD_BUTTON_8,
  DRV_KEYPAD_BUTTON_9,
  DRV_KEYPAD_BUTTON_STAR,
  DRV_KEYPAD_BUTTON_SHARP,
  DRV_KEYPAD_BUTTON_DELETE,
  DRV_KEYPAD_BUTTON_UP,
  DRV_KEYPAD_BUTTON_DOWN,
  DRV_KEYPAD_BUTTON_ENTER,
  DRV_KEYPAD_NONE,
  DRV_KEYPAD_ERROR,
} drv_keypad_button_t;


/**
 * @brief <this structure defines components to control keypad>
 */
typedef struct
{
  /**< This function pointer utilized to receive output data from TTP229 module */
  bsp_state_t (*usart_rx_active)(bsp_config_id_t id, uint8_t *pdata, uint8_t size); 
  bsp_state_t (*usart_rx_cplt)(bsp_config_id_t id);
  uint8_t pre_btn[2];
} drv_keypad_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief  <This function utilized to init keypad>
 *
 * @param[in]     <drv_keypad_t *keypad>  <pointer to a struct type>
 * @param[out]    None
 * @param[inout]  None
 *
 * @attention  <API attention note>
 *
 * @return
 *  - 0: DRV_KEYPAD_STATUS_FAIL
 *  - 1: DRV_KEYPAD_STATUS_SUCCESS
 */
drv_keypad_status_t drv_keypad_init(drv_keypad_t *keypad);


/**
 * @brief  <This function utilized to read data from TTP229 module by polling method>
 *
 * @param[in]     <drv_keypad_t *keypad>  <pointer to a struct type>
 * @param[out]    None
 * @param[inout]  None
 *
 * @attention  <API attention note>
 *
 * @return a value of enum defined above
 */
drv_keypad_button_t drv_keypad_read(drv_keypad_t *keypad);

/**
 * @brief  <This function utilized to read data from TTP229 module by polling method>
 *
 * @param[in]     <drv_keypad_t *keypad>  <pointer to a struct type>
 * @param[out]    None
 * @param[inout]  None
 *
 * @attention  <API attention note>
 *
 * @return a value of enum defined above
 */
drv_keypad_button_t drv_keypad_scan(drv_keypad_t *keypad);
#endif // __DRV_KEYPAD_H

/* End of file -------------------------------------------------------- */
