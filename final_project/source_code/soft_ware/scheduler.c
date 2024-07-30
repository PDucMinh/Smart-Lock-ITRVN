/**
 * @file       scheduler.c
 * @copyright  Copyright (C). All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    major.minor.patch
 * @date       yyyy-mm-dd
 * @author     Minh Pham Duc
 *
 * @brief      <A brief description of the content of the file>
 *
 * @note
 */

/* Includes ----------------------------------------------------------- */
#include "scheduler.h"

/* Private defines ---------------------------------------------------- */
#define SCH_OK (SCH_MAX_TASK + 2)   /*Success action*/
#define SCH_FAIL (SCH_MAX_TASK + 1) /*Fail action*/

/**
 * @brief structure contain task information
 */
typedef struct
{
  void (*task)(void); /*!< Description of task */
  uint32_t delay;     /*!< remaining time before execute task */
  uint32_t period;    /*!< cycle of execution */
  uint8_t run;        /*!< run flag */
} sch_task_t;

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
#define CHECK_ID(a)        \
  do                       \
  {                        \
    if (a >= SCH_MAX_TASK) \
    {                      \
      return SCH_FAIL;     \
    }                      \
  } while (0)

/* Private variables -------------------------------------------------- */
static uint32_t sch_tick_scaler = 1; /*Scheduler tick scaler*/
static sch_task_t sch_tasks[SCH_MAX_TASK]; /*Task queue*/
static uint8_t sch_task_id[SCH_MAX_TASK] = 0; /*Array of Active Task ID*/

/* Private function prototypes ---------------------------------------- */
/**
 * @brief  automatically generate task ID
 *
 * @attention  <API attention note>
 *
 * @return
 *  - SCH_FAIL: Error
 *  - Other: Task ID
 */
static uint8_t sch_generate_task_id(void);

/**
 * @brief  check exist task ID
 *
 * @attention  <API attention note>
 *
 * @return
 *  - SCH_FAIL: Non active task ID
 *  - Others: Task ID
 */
static uint8_t sch_check_exist_id(uint8_t id);

/* Function definitions ----------------------------------------------- */
void sch_init(void)
{
}

void sch_update(void)
{
}

void sch_dispatch_task(void)
{
}

uint32_t sch_add_task(void(*task), uint32_t delay, uint32_t period)
{
}

uint8_t sch_delete_task(uint32_t task_id)
{
}
/* Private definitions ----------------------------------------------- */
static uint8_t sch_generate_task_id(void)
{
}

stactic uint8_t sch_check_exist_id(uint8_t id)
{
}
/* End of file -------------------------------------------------------- */
