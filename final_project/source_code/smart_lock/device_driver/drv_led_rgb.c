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
/* Private defines ---------------------------------------------------- */
#define DRV_LED_RGB_NUMBER_OF_COLOR (6)
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
static drv_led_rgb_info_t led_rgb_info[DRV_LED_RGB_NUMBER_OF_COLOR] = {
  { DRV_LED_RGB_OFF, { 0, 0, 0 } },    { DRV_LED_RGB_RED, { 255, 0, 0 } },      { DRV_LED_RGB_GREEN, { 0, 255, 0 } },
  { DRV_LED_RGB_BLUE, { 0, 0, 255 } }, { DRV_LED_RGB_ORANGE, { 255, 165, 0 } }, { DRV_LED_RGB_PURPLE, { 255, 0, 255 } }
};

static drv_led_rgb_color_t led_rgb_state;
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
drv_led_rgb_status_t drv_led_rgb_init(drv_led_rgb_t* led)
{
  // do something
  led_rgb_state = DRV_LED_RGB_OFF;
  led->pwm_set = bsp_pwm_set_duty;
  led->pwm_start = bsp_pwm_start;
  led->pwm_start(BSP_CONFIG_ID_LED_RGB, BSP_CONFIG_LED_RED);
  led->pwm_start(BSP_CONFIG_ID_LED_RGB, BSP_CONFIG_LED_GREEN);
  led->pwm_start(BSP_CONFIG_ID_LED_RGB, BSP_CONFIG_LED_BLUE);
  drv_led_rgb_set(led, DRV_LED_RGB_COLOR_OFF);
}
#else
drv_led_rgb_func_status_t drv_led_rgb_init()
{
  // do something
}
#endif

drv_led_rgb_func_status_t drv_led_rgb_set(drv_led_rgb_t* led,drv_led_rgb_color_t color)
{
  if (color >= DRV_LED_RGB_NUMBER_OF_COLOR)
  {
    return DRV_LED_RGB_ERROR;
  }
  led_rgb_state = color;
  float red_led_duty = (led_rgb_info[color].rgb_code[0] / 255.0) * 100;
  float green_led_duty = (led_rgb_info[color].rgb_code[1] / 255.0) * 100;
  float blue_led_duty = (led_rgb_info[color].rgb_code[2] / 255.0) * 100;
  led->pwm_set(BSP_CONFIG_ID_LED_RGB, BSP_CONFIG_LED_RED, duty_red);
  led->pwm_set(BSP_CONFIG_ID_LED_RGB, BSP_CONFIG_LED_GREEN, duty_green);
  led->pwm_set(BSP_CONFIG_ID_LED_RGB, BSP_CONFIG_LED_BLUE, duty_blue);
  return DRV_LED_RGB_SUCCESS;
}

drv_led_rgb_color_t drv_led_rgb_state(void)
{
  return led_rgb_state;
}

/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
