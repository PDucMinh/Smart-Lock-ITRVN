/**
 * @file       sys_protocol.c
 * @copyright  Copyright (C). All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    major.minor.patch
 * @date       yyyy-mm-dd
 * @author     Minh Pham Duc
 *
 * @brief      <A brief description of the content of the file>
 *
 */

/* Includes ----------------------------------------------------------- */
#include "sys_protocol.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */
typedef enum
{
  SP_INIT,
  SP_IDLE,
  SP_START,
  SP_RECEIVE,
  SP_TRANSMIT,
  SP_END,
  SP_TERMINATE
} sys_protocol_state_t;
/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static uint8_t sprotocol_array_transmit[MAX_FRAME_LENGTH];
static uint8_t sprotocol_array_receive[MAX_FRAME_LENGTH];

static sys_data_t sys_data_from_fifo;
static sys_data_t sys_data_to_fifo;

static uint8_t timer_1_flag = 0;

static sys_protocol_state_t sys_protocol_state;

static data_frame_t sprotocol_data_frame_receive;
static data_frame_t sprotocol_data_frame_transmit;

int count = 0;
uint8_t temp[MAX_DATA_LENGTH];
drv_led_rgb_t led_rgb;
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
static void timer_1_run(void);
static uint8_t check_timer_1_flag(void);
/* Function definitions ----------------------------------------------- */
void sys_protocol_init(void)
{
  bsp_gpio_pin_t tx_pin, rx_pin;
  tx_pin.io = (BSP_GPIO_PORT_C << 4) | BSP_GPIO_PIN_6;
  tx_pin.mode = BSP_GPIO_AF_PP;
  tx_pin.pull_type = BSP_GPIO_NOPULL;
  tx_pin.speed = BSP_GPIO_FREQ_LOW;
  tx_pin.af = BSP_GPIO_AF8;
  bsp_gpio_pin_init(&tx_pin);

  rx_pin.io = (BSP_GPIO_PORT_C << 4) | BSP_GPIO_PIN_7;
  rx_pin.mode = BSP_GPIO_AF_PP;
  rx_pin.pull_type = BSP_GPIO_NOPULL;
  rx_pin.speed = BSP_GPIO_FREQ_LOW;
  rx_pin.af = BSP_GPIO_AF8;
  bsp_gpio_pin_init(&rx_pin);

  drv_led_rgb_init(&led_rgb);
}

void sys_protocol_write_data_frame_to_array(data_frame_t *source_data_frame, uint8_t *dest_array)
{
  dest_array[0] = source_data_frame->header;
  dest_array[1] = source_data_frame->sequence;
  dest_array[2] = source_data_frame->command;
  dest_array[3] = source_data_frame->length;
  for (int i = 0; i < source_data_frame->length; i++)
  {
    dest_array[4 + i] = source_data_frame->data[i];
  }
}

void sys_protocol_read_data_frame_from_array(data_frame_t *dest_data_frame, uint8_t *source_array)
{
  dest_data_frame->header = source_array[0];
  dest_data_frame->sequence = source_array[1];
  dest_data_frame->command = source_array[2];
  dest_data_frame->length = source_array[3];
  for (int i = 0; i < dest_data_frame->length; i++)
  {
    dest_data_frame->data[i] = source_array[4 + i];
  }
}

void sys_protocol_loop(fifo_buffer_info_t *fifo_request, fifo_buffer_info_t *fifo_response)
{

}
/* Private definitions ----------------------------------------------- */
static void timer_1_run(void)
{
  timer_1_flag = 1;
}

static uint8_t check_timer_1_flag(void)
{
  if (timer_1_flag)
  {
    timer_1_flag = 0;
    return 1;
  }
  return timer_1_flag;
}

/* SPROTOCOL_END of file -------------------------------------------------------- */
