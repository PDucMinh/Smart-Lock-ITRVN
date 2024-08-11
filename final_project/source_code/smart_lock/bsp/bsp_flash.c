/**
 * @file       bsp_flash.c
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license
 * @version    1.0.0
 * @date       2024-08-11
 * @author     Hung Nguyen
 *
 * @brief      <A brief description of the content of the file>
 *
 * @note
 * @example
 *
 */

/* Includes ----------------------------------------------------------- */
#include "bsp_flash.h"
#include "stm32f4xx_hal.h"

/* Private defines ---------------------------------------------------- */
#define PRIVATE_DEFINE_1 (0) /*!< Description of PRIVATE_DEFINE_1 */
#define PRIVATE_DEFINE_2 (0) /*!< Description of PRIVATE_DEFINE_2 */

/* Private enumerate/structure ---------------------------------------- */
/**
 * @brief <enum descriptiton>
 */
typedef enum
{
  PRIVATE_ENUM_1, /**< Description of PRIVATE_ENUM_1 */
  PRIVATE_ENUM_2, /**< Description of PRIVATE_ENUM_2 */
  PRIVATE_ENUM_3  /**< Description of PRIVATE_ENUM_3 */
} private_enum_type_t;

/**
 * @brief <structure descriptiton>
 */
typedef struct
{
  uint32_t member_1,   /**< Description of member_1 */
    uint32_t member_2, /**< Description of member_2 */
    uint32_t member_3  /**< Description of member_3 */
} private_struct_type_t;

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static uint8_t flash_erase_flag = 0;
static uint8_t flash_program_flag = 0;

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
static void private_function(void);
/* Function definitions ----------------------------------------------- */
bsp_state_t bsp_flash_write_register(uint32_t addr, uint64_t data)
{
  BSP_CHECK_RANGE(addr,
                  BSP_FLASH_START_ADDR_SECT6,
                  BSP_FLASH_START_ADDR_SECT7 + BSP_FLASH_SECT_SIZE - 1,
                  BSP_STATE_FAIL);
  HAL_FLASH_Unlock();
  if (HAL_FLASH_Program_IT(FLASH_TYPEPROGRAM_BYTE, addr, data) != HAL_OK)
  {
    return BSP_STATE_FAIL;
  }
  return BSP_STATE_PASS;
}

uint8_t bsp_flash_write_cplt(void)
{
  uint8_t ret_flag;
  ret_flag = flash_program_flag;
  if (flash_program_flag == 1)
  {
    flash_program_flag = 0;
  }
  return ret_flag;
}

bsp_state_t bsp_flash_erase_register(uint32_t addr)
{
  BSP_CHECK_NULL((addr == BSP_FLASH_START_ADDR_SECT6) || (addr == BSP_FLASH_START_ADDR_SECT7),
                 BSP_STATE_FAIL);
  HAL_FLASH_Unlock();
  FLASH_EraseInitTypeDef EraseInit;
  EraseInit.TypeErase = FLASH_TYPEERASE_SECTORS;
  EraseInit.Sector = addr;
  EraseInit.NbSectors = 1;
  EraseInit.VoltageRange = FLASH_VOLTAGE_RANGE_3;
  HAL_FLASHEx_Erase_IT(&EraseInit);
  return BSP_STATE_PASS;
}

uint8_t bsp_flash_erase_cplt(void)
{
  uint8_t ret_flag;
  ret_flag = flash_erase_flag;
  if (flash_erase_flag == 1)
  {
    flash_erase_flag = 0;
  }
  return ret_flag;
}

uint32_t bsp_flash_read(uint32_t addr)
{
  uint32_t data = *((volatile uint32_t*)addr);
  return data;
}
/* Private definitions ----------------------------------------------- */
static void HAL_FLASH_EndOfOperationCallback(uint32_t ReturnValue)
{
  if (ReturnValue == 0xFFFFFFFF)
  {
    flash_erase_flag = 1;
  }
  else
  {
    flash_program_flag = 1;
  }
  HAL_FLASH_Lock();
}
/* End of file -------------------------------------------------------- */
