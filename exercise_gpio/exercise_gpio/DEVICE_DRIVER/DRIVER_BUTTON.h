/**
 * @file       DRIVER_BUTTON.h
 * @copyright  
 * @license    
 * @version   
 * @date       2024-07-07
 * @author     Hung Nguyen Nhat
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
#ifndef __DRIVER_BUTTON_H
#define __DRIVER_BUTTON_H

/* Includes ----------------------------------------------------------- */
/* Public defines ----------------------------------------------------- */
/* gpio port ID */
#define DRIVER_BUTTON_PORT_A (0x10)
#define DRIVER_BUTTON_PORT_B (0x20)
#define DRIVER_BUTTON_PORT_C (0x30)
#define DRIVER_BUTTON_PORT_D (0x40)
/* gpio pin ID */
#define DRIVER_BUTTON_PIN_0 (0x00)
#define DRIVER_BUTTON_PIN_1 (0x01)
#define DRIVER_BUTTON_PIN_2 (0x02)
#define DRIVER_BUTTON_PIN_3 (0x03)
#define DRIVER_BUTTON_PIN_4 (0x04)
#define DRIVER_BUTTON_PIN_5 (0x05)
#define DRIVER_BUTTON_PIN_6 (0x06)
#define DRIVER_BUTTON_PIN_7 (0x07)
#define DRIVER_BUTTON_PIN_8 (0x08)
#define DRIVER_BUTTON_PIN_9 (0x09)
#define DRIVER_BUTTON_PIN_10 (0x0A)
#define DRIVER_BUTTON_PIN_11 (0x0B)
#define DRIVER_BUTTON_PIN_12 (0x0C)
#define DRIVER_BUTTON_PIN_13 (0x0D)
#define DRIVER_BUTTON_PIN_14 (0x0E)
#define DRIVER_BUTTON_PIN_15 (0x0F)

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief status of button
 */
typedef enum
{
    DRIVER_BUTTON_IS_PUSHED, /**< Description of PUBLIC_ENUM_1 */
    DRIVER_BUTTON_NO_PUSHED, /**< Description of PUBLIC_ENUM_2 */
} driver_button_state_t;

/**
 * @brief type of button
 */
typedef enum
{
    DRIVER_BUTTON_PULL_UP,  /**< Description of PUBLIC_ENUM_1 */
    DRIVER_BUTTON_PULL_DOWN /**< Description of PUBLIC_ENUM_2 */
} driver_button_type_t;

/**
 * @brief <structure descriptiton>
 */
typedef struct
{
    driver_button_type_t driver_button_type;   /**< Description of member_2 */
    uint32_t driver_button_io;                 /**< Description of member_3 */
} driver_button_t;

/* Public macros ------------------------------------------------------ */
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
#define PUBLIC_MACRO(a)  do_something_with(a)

/* Public variables --------------------------------------------------- */
extern int g_var_1; /**< Description of public variable g_var_1 */
extern int g_var_2; /**< Description of public variable g_var_2 */

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
 void driver_button_init(driver_button_t *db);
 driver_button_state_t driver_button_read(driver_button_t *db);

#endif // __CODE_TEMPLATE_H

/* End of file -------------------------------------------------------- */
