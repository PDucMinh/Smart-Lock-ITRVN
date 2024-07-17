/**
 * @file       SYSTEM_BUTTON.h
 * @copyright
 * @license
 * @version
 * @date       2024-07-07
 * @author     Minh Pham Duc
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
#ifndef __SYSTEM_BUTTON_H
#define __SYSTEM_BUTTON_H

/* Includes ----------------------------------------------------------- */
#include "driver_button.h"
/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief <return state of system button>
 */
typedef enum
{
  SYSTEM_BUTTON_IDLE,
  SYSTEM_BUTTON_1CLICK, /**< Description of PUBLIC_ENUM_1 */
  SYSTEM_BUTTON_2CLICK, /**< Description of PUBLIC_ENUM_2 */
  SYSTEM_BUTTON_HOLD,
  SYSTEM_BUTTON_RELEASE /**< Description of PUBLIC_ENUM_3 */
} system_button_state_t;

/**
 * @brief <process state of system button>
 */
typedef enum
{
  SYSTEM_BUTTON_PROCESS_ON_1CLICK,
  SYSTEM_BUTTON_PROCESS_OFF_1CLICK,
  SYSTEM_BUTTON_PROCESS_ON_2CLICK,
  SYSTEM_BUTTON_PROCESS_OFF_2CLICK,
  SYSTEM_BUTTON_PROCESS_ON_HOLD,
  SYSTEM_BUTTON_PROCESS_WAIT_RELEASE,
  SYSTEM_BUTTON_PROCESS_OFF_RELEASE,
  SYSTEM_BUTTON_PROCESS_FAULT,
  SYSTEM_BUTTON_PROCESS_INIT
} system_button_process_t;

/**
 * @brief <structure manage system button>
 */
typedef struct
{
  system_button_state_t button_state;
  driver_button_t button;
  uint8_t active;
  uint16_t button_time;
  uint8_t button_timeout;
  system_button_process_t button_process;
} system_button_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief  <Initializing a system button component>
 *
 * @param[in]     <v_sbutton>  <struct pointer manage system button>
 * @param[out]    none
 * @param[inout]  none
 *
 * @attention  
 *
 * @return        none
 *  
 */
void system_button_init(system_button_t *v_sbutton);

/**
 * @brief  <reading system button state>
 *
 * @param[in]     <v_sbutton>  <struct pointer manage system button> 
 * @param[out]    none
 *
 * @attention     
 *
 * @return        
 *  - SYSTEM_BUTTON_IDLE : Button is not clicked
 *  - SYSTEM_BUTTON_1CLICK : Button is clicked one time
 *  - SYSTEM_BUTTON_2CLICK : Button is clicked two times
 *  - SYSTEM_BUTTON_HOLD : Button is hold
 *  - SYSTEM_BUTTON_RELEASE : Button is released after being hold
 */
system_button_state_t system_button_read(system_button_t *v_sbutton);

/**
 * @brief  <This function will set system button state base on readings 
 *          from driver button>
 *
 * @param[in]     driver_button_t struct pointer manage button signal
 * @param[out]    system_button_state_t  button behavior number of click or release
 *
 * @attention  <This function need to be executed in while loop in main function>
 *
 * @return  none
 *  
 */
void system_button_loop(system_button_t *v_sbutton);

/**
 * @brief  <This function will set time out base on specification after receive
 *          a pushed event from driver button>
 *
 * @param[in]     <v_sbutton> <struct pointer manage system button>
 * @param[out]    none
 *
 * @attention  <This function need to be executed in timer interrupt routine>
 *
 * @return   none
 *  
 */
void system_button_timeout(system_button_t *v_sbutton);
#endif // __SYSTEM_BUTTON_H

/* End of file -------------------------------------------------------- */
