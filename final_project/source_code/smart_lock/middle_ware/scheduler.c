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
  uint8_t sch_run;    /*!< sch_run flag */
  uint8_t sch_id;     /*!< task sch_id */
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
static uint32_t sch_tick_scaler = 1;       /*Scheduler tick scaler*/
static sch_task_t sch_tasks[SCH_MAX_TASK]; /*Task queue (sch_id from 0 to max_size - 1)*/
static uint8_t sch_task_id[SCH_MAX_TASK];  /*Array of Active Task sch_id*/

static uint8_t sch_active_size = 0;

/* Function definitions ----------------------------------------------- */
void sch_init(void)
{
  for (uint32_t index = 0; index < SCH_MAX_TASK; index++)
  {
    sch_tasks[index].task = 0x0000;
    sch_tasks[index].delay = 0;
    sch_tasks[index].period = 0;
    sch_tasks[index].sch_run = 0;
  }
}

void sch_update(void)
{
  if (sch_active_size >)
  {
    if (sch_tasks[0].delay > 0)
      sch_tasks[0].delay--;

    if (sch_tasks[0].delay == 0)
    {
      sch_tasks[0].sch_run = 1;
    }
  }
}

void sch_dispatch_task(void)
{
  if (sch_tasks[0].sch_run > 0)
  {
    (*sch_tasks[0].task)();
    sch_tasks[0].sch_run = 0;
    sch_task_t temp_task = sch_tasks[0];
    sch_delete_task(temp_task.sch_id);
    if (temp_task.period > 0)
    {
      sch_add_task(temp_task.task, temp_task.period, temp_task.period);
    }
  }
}

uint32_t sch_add_task(void(*task), uint32_t delay, uint32_t period)
{
  if (sch_active_size == SCH_MAX_TASK - 1)
    return SCH_FAIL;

  uint8_t flag = 0;
  uint32_t index = 0;

  for (index = 0; index < sch_active_size && flag == 0; index++)
  {
    if (delay > sch_tasks[index].delay)
    {
      delay -= sch_tasks[index].delay;
    }
    else
    {
      flag = 1;
      sch_tasks[index].delay -= delay;
      if (sch_tasks[index].delay == 0)
      {
        sch_tasks[index].sch_run = 1;
      }
    }
  }

  if (flag == 1)
  {
    index -= 1;
    for (uint32_t temp = sch_active_size; temp > index; temp--)
    {
      sch_tasks[temp] = sch_tasks[temp - 1];
      sch_tasks[temp].sch_id += 1;
    }
  }
  sch_tasks[index].task = task;
  sch_tasks[index].delay = delay;
  sch_tasks[index].period = period;
  sch_tasks[index].sch_run = (delay == 0) ? 1 : 0;
  sch_tasks[index].sch_id = index;

  sch_active_size += 1;

  return index;
}

uint8_t sch_delete_task(uint32_t task_id)
{
  if (sch_tasks[task_id].task == 0)
    return SCH_FAIL;

  sch_tasks[task_id + 1].delay += sch_tasks[task_id].delay;

  for (uint32_t temp = task_id; temp < sch_active_size - 1; temp++)
  {
    sch_tasks[temp] = sch_tasks[temp + 1];
    sch_tasks[temp].sch_id -= 1;
  }

  sch_active_size -= 1;
  return SCH_OK;
}
/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
