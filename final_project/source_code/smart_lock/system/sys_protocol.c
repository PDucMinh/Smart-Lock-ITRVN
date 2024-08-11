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
  switch (sys_protocol_state)
  {
  case SP_INIT:
    if (fifo_size(fifo_request) > 0)
    {
      fifo_pop(fifo_request, &sys_data_from_fifo);
      if (sys_data_from_fifo.protocol_req.req == SYS_REQ_PROTOCOL_ACCEPT_GUI)
      {
        bsp_uart_receive_start(BSP_CONFIG_ID_PROTOCOL, sprotocol_array_receive, MAX_FRAME_LENGTH);
        sys_protocol_state = SP_START;
      }
    }
  case SP_START:
    if (bsp_uart_receive_cplt(BSP_CONFIG_ID_PROTOCOL))
    {
      switch (sprotocol_array_receive[0])
      {
      case SPROTOCOL_SEND:
        sys_protocol_read_data_frame_from_array(&sprotocol_data_frame_receive, sprotocol_array_receive);

        sys_data_to_fifo.protocol_ev.ev = SYS_EVENT_PROTOCOL_RECEIVE;
        sys_data_to_fifo.protocol_ev.pdata = &sprotocol_data_frame_receive.data;
        sys_data_to_fifo.protocol_ev.data_size = sprotocol_data_frame_receive.length;
        fifo_push(fifo_response, &sys_data_to_fifo);

        sys_protocol_state = SP_START;
        bsp_uart_receive_start(BSP_CONFIG_ID_PROTOCOL, sprotocol_array_receive, MAX_FRAME_LENGTH);
      case SPROTOCOL_REQUEST:
        sys_data_to_fifo.protocol_ev.ev = SYS_EVENT_PROTOCOL_SEND;
        fifo_push(fifo_response, &sys_data_to_fifo);
        sys_protocol_state = SP_TRANSMIT;
        break;
      case SPROTOCOL_END:
        sys_data_to_fifo.protocol_ev.ev = SYS_EVENT_PROTOCOL_COMPLETE;
        fifo_push(fifo_response, &sys_data_to_fifo);
        sys_protocol_state = SP_INIT;
        break;
      case SPROTOCOL_TERMINATE:
        sys_data_to_fifo.protocol_ev.ev = SYS_EVENT_PROTOCOL_COMPLETE;
        fifo_push(fifo_response, &sys_data_to_fifo);
        sys_protocol_state = SP_INIT;
        break;
      default:
        break;
      }
    }
    break;
  case SP_RECEIVE:
    sys_protocol_state = SP_INIT;
    break;
  case SP_TRANSMIT:
    if (fifo_size(fifo_request) > 0)
    {
      fifo_pop(fifo_request, &sys_data_from_fifo);
      if (sys_data_from_fifo.protocol_req.req == SYS_REQ_PROTOCOL_INFO)
      {
        sprotocol_data_frame_transmit.header = SPROTOCOL_SEND;
        sprotocol_data_frame_transmit.sequence = 0x01;
        sprotocol_data_frame_transmit.command = 0xFF;
        sprotocol_data_frame_transmit.length = sys_data_from_fifo.protocol_req.data_size;
        for (int i = 0; i < sys_data_from_fifo.protocol_req.data_size; i++)
        {
          sprotocol_data_frame_transmit.data[i] = sys_data_from_fifo.protocol_req.pdata[i];
        }
        sys_protocol_write_data_frame_to_array(&sprotocol_data_frame_transmit, sprotocol_array_transmit);
        bsp_uart_transmit_start(BSP_CONFIG_ID_PROTOCOL, sprotocol_array_transmit, MAX_FRAME_LENGTH);
      }
      else if (bsp_uart_transmit_cplt(BSP_CONFIG_ID_PROTOCOL))
      {
        bsp_uart_receive_start(BSP_CONFIG_ID_PROTOCOL, sprotocol_array_receive, MAX_FRAME_LENGTH);
        sys_protocol_state = SP_START;
      }
    }
    else if (bsp_uart_transmit_cplt(BSP_CONFIG_ID_PROTOCOL))
    {
      bsp_uart_receive_start(BSP_CONFIG_ID_PROTOCOL, sprotocol_array_receive, MAX_FRAME_LENGTH);
      sys_protocol_state = SP_START;
    }
    break;
  default:
    sys_protocol_state = SP_START;
    break;
  }
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
