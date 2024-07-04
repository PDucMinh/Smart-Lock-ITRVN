/**
 * @file       <string_recognize>.c
 * @copyright  Copyright (C) 2024 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    0.0.0
 * @date       2024-09-30
 * @author     <Minh> <Pham Duc>
 * @author     <first_name_2> <last_name_2>
 *
 * @brief      <This is source file for exercise week 2: design fsm detect "10110">
 *
 * @note
 * @example    example_file_1.c
 *             Example_1 description
 * @example    example_file_2.c
 *             Example_2 description
 */

/* Includes ----------------------------------------------------------- */
#include "string_recognize.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */
/**
 * @brief <enum descriptiton>
 */

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
uint8_t string_recognize_fsm(uint8_t input)
{
  switch (fsm_state)
  {
  case INIT:
    fsm_state = input == 1 ? STATE_A : INIT;
    break;
  case STATE_A:
    fsm_state = input == 0 ? STATE_B : STATE_A;
    break;
  case STATE_B:
    fsm_state = input == 1 ? STATE_C : INIT;
    break;
  case STATE_C:
    fsm_state = input == 0 ? STATE_B : STATE_D;
    break;
  case STATE_D:
    fsm_state = input == 0 ? INIT : STATE_A;
    fsm_state == INIT ? printf("String recognized\n") : printf("");
    return input == 0 ? 1 : 0;
    break;
  default:
    fsm_state = input == 1 ? STATE_A : INIT;
    break;
  }
  return 0;
}
/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
