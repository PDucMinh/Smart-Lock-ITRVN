/**
 * @file       scheduler.h
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

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __SCHEDULER_H
#define __SCHEDULER_H

/* Includes ----------------------------------------------------------- */
/* Public defines ----------------------------------------------------- */
#define SCH_MAX_TASK (10) /*Maximum of queue*/

/* Public function prototypes ----------------------------------------- */
/**
 * @brief  initialize scheduler
 *
 * @attention  declare this function before using scheduler
 *
 */
void sch_init(void);

/**
 * @brief  calculate the time of the next task
 *
 * @attention  timer for this function must be set to 1ms (can be modified in
 * sch_init())
 *
 */
void sch_update(void);

/**
 * @brief  function to run task
 *
 * @attention  this function should be added in infinite loop
 *
 */
void sch_dispatch_task(void);

/**
 * @brief  add new task to scheduler
 *
 * @param[in]     (*task)  pointer to task function
 * @param[in]     (delay)  delay to first run task
 * @param[in]     (period) period of task (0: run once, >0: run after N ms)
 *
 * @attention
 *
 * @return
 *  - SCH_FAIL: Error
 *  - Others: Task ID
 */
uint32_t sch_add_task(void(*task), uint32_t delay, uint32_t period);

/**
 * @brief  delete task from scheduler
 *
 * @param[in]     (task_id) task ID
 *
 * @attention  
 *
 * @return  
 *  - SCH_OK: Success
 *  - SCH_FAIL: Error
 */
 uint8_t sch_delete_task(uint32_t task_id);

#endif // __CODE_TEMPLATE_H

/* End of file -------------------------------------------------------- */
