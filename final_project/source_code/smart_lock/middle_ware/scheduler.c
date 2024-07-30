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
  uint8_t sch_run;        /*!< sch_run flag */
  uint8_t sch_id;         /*!< task sch_id */
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
static uint8_t is_empty_task;              /*Flag to check empty task*/
/* Private function prototypes ---------------------------------------- */
/**
 * @brief  automatically generate task sch_id
 *
 * @attention  <API attention note>
 *
 * @return
 *  - SCH_FAIL: Error
 *  - Other: Task sch_id
 */
static uint8_t sch_generate_task_id(void);

/**
 * @brief  check exist task sch_id
 *
 * @attention  <API attention note>
 *
 * @return
 *  - SCH_OK: Task sch_id not activated
 *  - SCH_FAIL: Error sch_id
 *  - Others: Task sch_id activated
 */
static uint8_t sch_check_exist_id(uint8_t sch_id);

/* Function definitions ----------------------------------------------- */
void sch_init(void)
{
  is_empty_task = 1;
	for(uint32_t index = 0; index < SCH_MAX_TASK; index++) {
		sch_tasks[index].task = 0x0000;
		sch_tasks[index].delay = 0;
		sch_tasks[index].period = 0;
		sch_tasks[index].sch_run = 0;
	}
}

void sch_update(void)
{
  if ((sch_tasks[0].task) && (sch_tasks[0].sch_run == 0))
  {
    if (sch_tasks[0].delay > 0)
    {
      sch_tasks[0].delay = sch_tasks[0].delay - 1;
    }
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
  uint8_t new_task_index = 0;
  uint32_t sum_delay = 0;
  uint32_t new_delay = 0;

  for (new_task_index = 0; new_task_index < SCH_MAX_TASK; new_task_index++)
  {
    sum_delay = sum_delay + sch_tasks[new_task_index].delay;
    if (sum_delay > delay)
    {
      new_delay = delay - (sum_delay - sch_tasks[new_task_index].delay);
      sch_tasks[new_task_index].delay = sum_delay - delay;
      for (uint8_t i = SCH_MAX_TASK - 1; i > new_task_index; i--)
      {
        //				if(sch_tasks[i - 1].task != 0)
        {
          sch_tasks[i].task = sch_tasks[i - 1].task;
          sch_tasks[i].period = sch_tasks[i - 1].period;
          sch_tasks[i].delay = sch_tasks[i - 1].delay;
          sch_tasks[i].sch_id = sch_tasks[i - 1].sch_id;
        }
      }
      sch_tasks[new_task_index].task = task;
      sch_tasks[new_task_index].delay = new_delay;
      sch_tasks[new_task_index].period = period;
      if (sch_tasks[new_task_index].delay == 0)
      {
        sch_tasks[new_task_index].sch_run = 1;
      }
      else
      {
        sch_tasks[new_task_index].sch_run = 0;
      }
      sch_tasks[new_task_index].sch_id = sch_generate_task_id();
      return sch_tasks[new_task_index].sch_id;
    }
    else
    {
      if (sch_tasks[new_task_index].task == 0x0000)
      {
        sch_tasks[new_task_index].task = task;
        sch_tasks[new_task_index].delay = delay - sum_delay;
        sch_tasks[new_task_index].period = period;
        if (sch_tasks[new_task_index].delay == 0)
        {
          sch_tasks[new_task_index].sch_run = 1;
        }
        else
        {
          sch_tasks[new_task_index].sch_run = 0;
        }
        sch_tasks[new_task_index].sch_id = sch_generate_task_id();
        return sch_tasks[new_task_index].sch_id;
      }
    }
  }
  return sch_tasks[new_task_index].sch_id;
}

uint8_t sch_delete_task(uint32_t task_id)
{
}
/* Private definitions ----------------------------------------------- */
static uint8_t sch_generate_task_id(void)
{
  for (uint8_t i = 0; i < SCH_MAX_TASK; i++)
  {
    if (sch_task_id[i] == 0)
    {
      sch_task_id[i] = 1;
      return i;
    }
  }
  return SCH_FAIL;
}

static uint8_t sch_check_exist_id(uint8_t sch_id)
{
  CHECK_ID(sch_id);
  if (sch_task_id[sch_id] == 0)
  {
    return SCH_OK;
  }
  return sch_id;
}
/* End of file -------------------------------------------------------- */
