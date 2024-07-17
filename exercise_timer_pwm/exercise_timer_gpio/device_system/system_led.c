/**
 * @file       system_led.c
 * @copyright
 * @license
 * @version    major.minor.patch
 * @date       2024-07-11
 * @author     Hung Nguyen Nhat
 * @author     <first_name_2> <last_name_2>
 *
 * @brief      <A brief description of the content of the file>
 *
 * @note
 * @example
 */

/* Includes ----------------------------------------------------------- */
#include "system_led.h"

/* Private defines ---------------------------------------------------- */
#define SYSTEM_LED_MAX_COLOR (4)
/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */
static led_rgb_list[SYSTEM_LED_MAX_COLOR][3] = 
{
  /* Orange color */{255, 26, 0},
  /* Violet color */{238, 26, 238},
  /* Aqua color */  {0, 255, 255},
  /* No color */    {0, 0, 0}
};
/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
driver_state_t system_led_init(system_led_t* v_sled, driver_mcu_t* v_dmcu)
{
  DRIVER_CHECK_NULL(v_sled, DRIVER_STATE_FAIL);
  DRIVER_CHECK_NULL(v_dmcu, DRIVER_STATE_FAIL);
  if (driver_led_init(&(v_sled->ledR), v_dmcu) == DRIVER_STATE_FAIL)
  {
    return DRIVER_STATE_FAIL;
  }
  if (driver_led_init(&(v_sled->ledG), v_dmcu) == DRIVER_STATE_FAIL)
  {
    return DRIVER_STATE_FAIL;
  }
  if (driver_led_init(&(v_sled->ledB), v_dmcu) == DRIVER_STATE_FAIL)
  {
    return DRIVER_STATE_FAIL;
  }
  system_led_set(v_sled, v_dmcu, SYSTEM_LED_EVENT_OFF);
  return DRIVER_STATE_PASS;
}

uint16_t ledR_duty, ledG_duty, ledB_duty;
driver_state_t system_led_set(system_led_t* v_sled, driver_mcu_t* v_dmcu, system_led_event_t v_sled_event)
{
  DRIVER_CHECK_NULL(v_sled, DRIVER_STATE_FAIL);
  DRIVER_CHECK_NULL(v_dmcu, DRIVER_STATE_FAIL);
  v_sled->led_rgb_id[0] = led_rgb_list[v_sled_event][0];
  v_sled->led_rgb_id[1] = led_rgb_list[v_sled_event][1];
  v_sled->led_rgb_id[2] = led_rgb_list[v_sled_event][2];
  
  ledR_duty = (uint16_t)(round(99.0 * (v_sled->led_rgb_id[0]) / 255));
  ledG_duty = (uint16_t)(round(99.0 * (v_sled->led_rgb_id[1]) / 255));  
  ledB_duty = (uint16_t)(round(99.0 * (v_sled->led_rgb_id[2]) / 255));
  driver_led_set(v_dmcu, &(v_sled->ledR), ledR_duty);
  driver_led_set(v_dmcu, &(v_sled->ledG), ledG_duty);
  driver_led_set(v_dmcu, &(v_sled->ledB), ledB_duty);
  return DRIVER_STATE_PASS;
}
/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
