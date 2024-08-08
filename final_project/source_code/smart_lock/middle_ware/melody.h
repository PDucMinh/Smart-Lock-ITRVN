/**
 * @file       melody.h
 * @copyright  
 * @license    This project is released under the Fiot License.
 * @version    1.0.0
 * @date       2024-08-01
 * @author     Hung Nguyen
 *             
 * @brief      <A brief description of the content of the file>
 *             
 * @note          
 * @example    
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __MELODY_H
#define __MELODY_H

/* Includes ----------------------------------------------------------- */
#include "stm32f4xx_hal.h"
/* Public defines ----------------------------------------------------- */
#define MELODY_ID_FIRST_SONG (0u)
#define MELODY_ID_SECOND_SONG (1u)
#define MELODY_ID_THIRD_SONG (2u)
#define MELODY_ID_FOURTH_SONG (3u)
/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief <structure descriptiton>
 */
typedef struct 
{
  uint16_t* pnote_array; 
  uint32_t size; 
}
melody_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
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
 melody_t melody_read(uint16_t id);

#endif // __CODE_TEMPLATE_H

/* End of file -------------------------------------------------------- */
