/**
 * @file       bsp_state.h
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    
 * @version    1.0.0
 * @date       2024-07-28
 * @author     Hung Nguyen
 *             
 * @brief      This file export common status for bsp API
 *             
 * @note          
 * @example    
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __BSP_STATE_H
#define __BSP_STATE_H

/* Includes ----------------------------------------------------------- */
/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief bsp status enum definition
 */
typedef enum
{
  BSP_STATE_FAIL, /**< return value when parameter is failed */
  BSP_STATE_PASS, /**< return value when parameter is passed */
} bsp_state_t;

/* Public macros ------------------------------------------------------ */
/**
 * @brief  Macro check whether the first parameter is equal to NULL. If it's
 * equal to NULL then return DRIVER_FAIL for second parameter, else do nothing.
 *
 *
 * @param[in]     A  <parameter need to be checked>
 * @param[out]    B  <parameter receive return value>
 *
 * @attention
 *
 * @return
 *  - BSP_STATE_PASS: first parameter is valid
 *  - BSP_STATE_FAIL: first parameter is invalid
 */
#define BSP_CHECK_NULL(A, B) \
  do                            \
  {                             \
    if (!(A != NULL))           \
      return B;                 \
  } while (0)

/**
 * @brief  Macro check whether the first parameter is out of range from 0 to B.
 * If it's out of range then return DRIVER_FAIL for second parameter, else do nothing.
 *
 *
 * @param[in]     A  <parameter need to be checked>
 * @param[out]    B  <parameter receive return value>
 *
 * @attention
 *
 * @return
 *  - BSP_STATE_PASS: first parameter is valid
 *  - BSP_STATE_FAIL: first parameter is invalid
 */
#define BSP_CHECK_RANGE(A, __RANGE__, B) \
  do                                        \
  {                                         \
    if (!(A < __RANGE__))                   \
      return B;                             \
  } while (0)

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */

#endif // __BSP_STATE_H

/* End of file -------------------------------------------------------- */
