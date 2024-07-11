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

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
driver_state_t system_led_init(system_led_t* v_sled, driver_mcu_t* v_dmcu)
{
  DRIVER_CHECK_NULL(v_sled, DRIVER_STATE_FAIL);
  DRIVER_CHECK_NULL(v_dmcu, DRIVER_STATE_FAIL);
  v_sled->led1.led_pin.io = DRIVER_MCU_PORT_D | DRIVER_MCU_PIN_12;
  v_sled->led1.led_pin.af = DRIVER_MCU_PWM_1;
  v_sled->led1.led_type = DRIVER_LED_TYPE_KCOMMON;
  if (driver_led_init(&(v_sled->led1), v_dmcu) == DRIVER_STATE_FAIL)
  {
    return DRIVER_STATE_FAIL;
  }
  v_sled->led2.led_pin.io = DRIVER_MCU_PORT_D | DRIVER_MCU_PIN_13;
  v_sled->led2.led_pin.af = DRIVER_MCU_PWM_2;
  v_sled->led2.led_type = DRIVER_LED_TYPE_KCOMMON;
  if (driver_led_init(&(v_sled->led2), v_dmcu) == DRIVER_STATE_FAIL)
  {
    return DRIVER_STATE_FAIL;
  }
  v_sled->led3.led_pin.io = DRIVER_MCU_PORT_D | DRIVER_MCU_PIN_14;
  v_sled->led3.led_pin.af = DRIVER_MCU_PWM_3;
  v_sled->led3.led_type = DRIVER_LED_TYPE_KCOMMON;
  if (driver_led_init(&(v_sled->led3), v_dmcu) == DRIVER_STATE_FAIL)
  {
    return DRIVER_STATE_FAIL;
  }
  return DRIVER_STATE_PASS;
}

driver_state_t system_led_set(system_led_t* v_sled, driver_mcu_t* v_dmcu, system_led_event_t v_sled_event)
{
  DRIVER_CHECK_NULL(v_sled, DRIVER_STATE_FAIL);
  DRIVER_CHECK_NULL(v_dmcu, DRIVER_STATE_FAIL);
  switch (v_sled_event)
  {
  case SYSTEM_LED_EVENT_LED1:
  {
    driver_led_set(v_dmcu, &(v_sled->led1), DRIVER_LED_STATE_BLINK);
    driver_led_set(v_dmcu, &(v_sled->led2), DRIVER_LED_STATE_OFF);
    driver_led_set(v_dmcu, &(v_sled->led3), DRIVER_LED_STATE_OFF);
    break;
  }
  case SYSTEM_LED_EVENT_LED2:
  {
    driver_led_set(v_dmcu, &(v_sled->led1), DRIVER_LED_STATE_OFF);
    driver_led_set(v_dmcu, &(v_sled->led2), DRIVER_LED_STATE_BLINK);
    driver_led_set(v_dmcu, &(v_sled->led3), DRIVER_LED_STATE_OFF);
    break;
  }
  case SYSTEM_LED_EVENT_LED3:
  {
    driver_led_set(v_dmcu, &(v_sled->led1), DRIVER_LED_STATE_OFF);
    driver_led_set(v_dmcu, &(v_sled->led2), DRIVER_LED_STATE_OFF);
    driver_led_set(v_dmcu, &(v_sled->led3), DRIVER_LED_STATE_BLINK);
    break;
  }
  case SYSTEM_LED_EVENT_OFF:
  {
    driver_led_set(v_dmcu, &(v_sled->led1), DRIVER_LED_STATE_OFF);
    driver_led_set(v_dmcu, &(v_sled->led2), DRIVER_LED_STATE_OFF);
    driver_led_set(v_dmcu, &(v_sled->led3), DRIVER_LED_STATE_OFF);
    break;
  }
  }
  return DRIVER_STATE_PASS;
}
/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
