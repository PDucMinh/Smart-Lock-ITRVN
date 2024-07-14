/**
 * @file       driver.h
 * @copyright
 * @license
 * @version
 * @date       2024-07-08
 * @author     Hung Nguyen Nhat
 *
 * @brief      This file provide driver status enum for checking parameter
 *
 * @note
 * @example
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __DRIVER_H
#define __DRIVER_H

/* Includes ----------------------------------------------------------- */
/* Public defines ----------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief <enum descriptiton>
 */
typedef enum
{
  DRIVER_STATE_FAIL, /**< return value when parameter is failed */
  DRIVER_STATE_PASS, /**< return value when parameter is passed */
} driver_state_t;

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
 *  - DRIVER_PASS: first parameter is valid
 *  - DRIVER_FAIL: first parameter is invalid
 */
#define DRIVER_CHECK_NULL(A, B) \
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
 *  - DRIVER_PASS: first parameter is valid
 *  - DRIVER_FAIL: first parameter is invalid
 */
#define DRIVER_CHECK_RANGE(A, __RANGE__, B) \
  do                                        \
  {                                         \
    if (!(A < __RANGE__))                   \
      return B;                             \
  } while (0)
/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */

#endif // __CODE_TEMPLATE_H

/* End of file -------------------------------------------------------- */
