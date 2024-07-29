/**
 * @file       drv_led_rgb.c
 * @copyright  Copyright (C) 2024. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    major.minor.patch
 * @date       yyyy-mm-dd
 * @author     Minh Pham Duc
 *
 * @brief      <A brief description of the content of the file>
 *
 * @note
 * @example    example_file_1.c
 *             Example_1 description
 * @example    example_file_2.c
 *             Example_2 description
 */

/* Includes ----------------------------------------------------------- */
#include "drv_led_rgb.h"
#include "bsp_pwm.h"
/* Private defines ---------------------------------------------------- */
#define NUMBER_OF_COLOR (6)
/* Private enumerate/structure ---------------------------------------- */

/**
 * @brief manage rbg color table
 */
typedef struct
{
  drv_led_rgb_state_t rgb_color;
  uint8_t rgb_code[3];
} drv_led_rgb_info_t;

/**
 * @brief <structure descriptiton>
 */

/* Private macros ----------------------------------------------------- */
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

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static drv_led_rgb_info_t led_rgb_info[6] = {
  { LED_RGB_OFF, { 0, 0, 0 } },    { LED_RGB_RED, { 255, 0, 0 } },      { LED_RGB_GREEN, { 0, 255, 0 } },
  { LED_RGB_BLUE, { 0, 0, 255 } }, { LED_RGB_ORANGE, { 255, 165, 0 } }, { LED_RGB_PURPLE, { 255, 0, 255 } }
};

static drv_led_rgb_state_t led_rgb_state;
/* Private function prototypes ---------------------------------------- */
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

/* Function definitions ----------------------------------------------- */
#ifndef __INIT_BY_VALUE
drv_led_rgb_func_status_t drv_led_rgb_init()
{
  // do something
  led_rgb_state = LED_RGB_OFF;
  bsp_pwm_start(&htim1, TIM_CHANNEL_1);
  bsp_pwm_start(&htim1, TIM_CHANNEL_2);
  bsp_pwm_start(&htim1, TIM_CHANNEL_3);
}
#else
drv_led_rgb_func_status_t drv_led_rgb_init()
{
  // do something
}
#endif

drv_led_rgb_func_status_t drv_led_rgb_set(drv_led_rgb_state_t color)
{

}

drv_led_rgb_state_t drv_led_rgb_state(void);

/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
