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
  INIT,
  IDLE,
  START,
  SUB_START,
  RECEIVE,
  RECEIVE_REQUEST,
  RECEIVE_REQUEST_MIDDLE,
  RECEIVE_SEND,
  RECEIVE_END,
  RECEIVE_TERMINATE,
  IDLE_TIME_OUT,
  REQUEST_WAITING,
  PARSER
} sys_protocol_state_t;
/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static uint8_t array_frame_transmit[MAX_FRAME_LENGTH];
static uint8_t array_frame_receive[MAX_FRAME_LENGTH];
static sys_data_t sys_data_from_fifo;
static sys_data_t sys_data_to_fifo;
static uint8_t timer_1_flag = 0;
static sys_protocol_state_t sys_protocol_state;
static data_frame_t data_frame_receive;
static data_frame_t data_frame_transmit;
static
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
  static void
  timer_1_run(void);
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
}
void read_data_frame_from_string(data_frame_t *dest_data_frame, char *src_data_string)
{
  data_frame_t data_f;

  // First sscanf call to parse header, sequence, command, and length
  int result1 = sscanf(src_data_string,
                       "%2hhx%2hhx%2hhx%2hhx%*x",
                       &data_f.header,
                       &data_f.sequence,
                       &data_f.command,
                       &data_f.length);

  // Check if the first parsing was successful
  // Second sscanf call to parse data and CRC based on the length
  uint8_t temp;
  for (int i = 0; i < data_f.length; i++)
  {
    sscanf(src_data_string + 8 + i * 2, "%2hhx%*x", &temp);
    data_f.data[i] = temp;
  }

#ifdef ALLOW_CRC
  for (int i = 0; *(src_data_string + 8 + data_f.length * 2 + i * 2) != '\0'; i++)
  {
    sscanf(src_data_string + 8 + data_f.length * 2 + i * 2, "%2hhx%*x", &temp);
    data_f.crc[i] = temp;
  }
#endif

  dest_data_frame->header = data_f.header;
  dest_data_frame->sequence = data_f.sequence;
  dest_data_frame->command = data_f.command;
  dest_data_frame->length = data_f.length;
  for (int i = 0; i < data_f.length; i++)
    dest_data_frame->data[i] = data_f.data[i];

#ifdef ALLOW_CRC
  for (int i = 0; i < MAX_CRC_LENGTH; i++)
    dest_data_frame->crc[i] = data_f.crc[i];
#endif
}

char write_data_frame_to_string(data_frame_t *src_data_frame)
{
  char data_string[MAX_FRAME_LENGTH];
  sprintf(data_string,
          "%02x%02x%02x%02x",
          src_data_frame->header,
          src_data_frame->sequence,
          src_data_frame->command,
          src_data_frame->length);

  char frame_temp[MAX_DATA_LENGTH];
  for (int i = 0; i < src_data_frame->length; i++)
  {
    sprintf(frame_temp, "%02x", src_data_frame->data[i]);
    strcat(data_string, frame_temp);
  }

#ifdef ALLOW_CRC
  char crc_temp[MAX_CRC_LENGTH];
  for (int i = 0; i < HALF_MAX_CRC_LENGTH; i++)
  {
    sprintf(crc_temp, "%02x", src_data_frame->crc[i]);
    strcat(data_string, crc_temp);
  }
#endif

  return data_string;
}

void read_data_frame_from_uint8_array(data_frame_t *dest_data_frame, uint8_t *src_data_array)
{
  dest_data_frame->header = src_data_array[0];
  dest_data_frame->sequence = src_data_array[1];
  dest_data_frame->command = src_data_array[2];
  dest_data_frame->length = src_data_array[3];

  for (int i = 0; i < dest_data_frame->length; i++)
  {
    dest_data_frame->data[i] = src_data_array[4 + i];
  }

#ifdef ALLOW_CRC
  for (int i = 0; i < (sizeof(src_data_array) / sizeof(src_data_array[0])); i++)
  {
    dest_data_frame->crc[i] = src_data_array[4 + dest_data_frame->length + i];
  }
#endif
}

void write_data_frame_to_uint8_array(data_frame_t *src_data_frame, uint8_t *dest_data_array)
{
  dest_data_array[0] = src_data_frame->header;
  dest_data_array[1] = src_data_frame->sequence;
  dest_data_array[2] = src_data_frame->command;
  dest_data_array[3] = src_data_frame->length;

  for (int i = 0; i < src_data_frame->length; i++)
  {
    dest_data_array[4 + i] = src_data_frame->data[i];
  }

#ifdef ALLOW_CRC
  for (int i = 0; i < MAX_CRC_LENGTH; i++)
  {
    dest_data_array[4 + src_data_frame->length + i] = src_data_frame->crc[i];
  }
#endif
}

void sys_protocol_loop(fifo_buffer_info_t *fifo_request, fifo_buffer_info_t *fifo_response)
{
  switch (sys_protocol_state)
  {
  case INIT:
    if (fifo_size(fifo_request) > 0)
    {
      fifo_pop(fifo_request, &sys_data_from_fifo);
      switch (sys_data_from_fifo.protocol_req.req)
      {
      case SYS_REQ_PROTOCOL_ACCEPT_GUI:
        bsp_uart_receive_start(BSP_CONFIG_ID_PROTOCOL, array_frame_receive, MAX_FRAME_LENGTH);
        sch_add_task(timer_1_run, 6000, 0);
        sys_protocol_state = IDLE;
        break;
      }
    }
    else
    {
      // do something
    }
    break;
  case IDLE:
    if (bsp_uart_receive_cplt(BSP_CONFIG_ID_PROTOCOL))
    {
      read_data_frame_from_uint8_array(&data_frame_receive, array_frame_receive);
      if (data_frame_receive.header == START)
      {
        data_frame_transmit.header = SEND;
        data_frame_transmit.sequence = data_frame_receive.sequence;
        data_frame_transmit.command = ACK;
        data_frame_transmit.length = 0;

        write_data_frame_to_uint8_array(&data_frame_transmit, array_frame_transmit);
        bsp_uart_transmit_start(BSP_CONFIG_ID_PROTOCOL, array_frame_transmit, MAX_FRAME_LENGTH);
        sys_protocol_state = START;
      }
    }
    else if (check_timer_1_flag())
    {
      sys_protocol_state = IDLE_TIME_OUT;
      // do something to send PROTOCOL_COMPLETE
      // MERGE IDLE_TIME_OUT and IDLE
    }
  // MERGE START and SUB_START
  case START:
    // do something
    if (bsp_uart_transmit_cplt(BSP_CONFIG_ID_PROTOCOL))
    {
      bsp_uart_receive_start(BSP_CONFIG_ID_PROTOCOL, array_frame_receive, MAX_FRAME_LENGTH);
      sys_protocol_state = RECEIVE;
    }
    break;
  case RECEIVE:
    // do something
    if (bsp_uart_receive_cplt(BSP_CONFIG_ID_PROTOCOL))
    {
      read_data_frame_from_uint8_array(&data_frame_receive, array_frame_receive);
      switch (data_frame_receive.header)
      {
      case SEND:
        /* code */
        // bsp_uart_receive_start(BSP_CONFIG_ID_PROTOCOL, array_frame_receive, MAX_FRAME_LENGTH);
        sys_protocol_state = RECEIVE_SEND;
        break;
      case REQUEST:
        // do something to get data from mcu
        // do something with array_frame_transmit
        sys_data_to_fifo.protocol_ev = SYS_EVENT_PROTOCOL_SEND;
        fifo_push(fifo_response, &sys_data_to_fifo);
        sys_protocol_state = RECEIVE_REQUEST;
        break;

      case END:
      sys_protocol_state = RECEIVE_END;
        break;
      case TERMINATE:
      sys_protocol_state = RECEIVE_TERMINATE;
        break;
      default:
        break;
      }
    }
    break;
  // case RECEIVE_REQUEST_MIDDLE:
  //   // do something
  //   if (fifo_size(fifo_request) > 0)
  //   {
  //     bsp_uart_transmit_start(BSP_CONFIG_ID_PROTOCOL, array_frame_transmit, MAX_FRAME_LENGTH);
  //     sys_protocol_state
  //   }
  //   else
  //   {
  //     sys_protocol_state = RECEIVE;
  //   }
  //   break;
  case RECEIVE_REQUEST:
    // do something
    if (fifo_size(fifo_request) > 0)
    {
      fifo_pop(fifo_request, &sys_data_from_fifo);
      switch (sys_data_from_fifo.protocol_req.req)
      {
      case SYS_REQ_PROTOCOL_INFO:
        // do something
        data_frame_transmit.header = SEND;
        data_frame_transmit.sequence = 0x01;
        data_frame_transmit.command = NONE;
        data_frame_transmit.length = sys_data_from_fifo.log_req.data_size;
        for (int i = 0; i < sys_data_from_fifo.log_req.data_size; i++)
        {
          data_frame_transmit.data[i] = sys_data_from_fifo.log_req.pdata[i];
        }
        // read_data_frame_from_uint8_array(&data_frame_transmit, );
        write_data_frame_to_uint8_array(&data_frame_transmit, array_frame_transmit);
        break;
      default:
        // do something
        break;
      }
      bsp_uart_transmit_start(BSP_CONFIG_ID_PROTOCOL, array_frame_transmit, MAX_FRAME_LENGTH);
      sys_protocol_state = REQUEST_WAITING;
    }
    else
    {
      // sys_protocol_state = RECEIVE;
    }
    break;
  case REQUEST_WAITING:
    // do something
    if (bsp_uart_transmit_cplt(BSP_CONFIG_ID_PROTOCOL))
    {
      bsp_uart_receive_start(BSP_CONFIG_ID_PROTOCOL, array_frame_receive, MAX_FRAME_LENGTH);
      sys_protocol_state = RECEIVE;
    }
    break;
  case RECEIVE_SEND:
    // do something
    // if (bsp_uart_receive_cplt(BSP_CONFIG_ID_PROTOCOL))
    // {
    // }
    read_data_frame_from_uint8_array(&data_frame_receive, array_frame_receive);
    sys_data_to_fifo.protocol_ev = SYS_EVENT_PROTOCOL_RECEIVE;
    sys_data_to_fifo.protocol_ev.data_size = data_frame_receive.length;
    for (int i=0; i < data_frame_receive.length; i++)
    {
      sys_data_to_fifo.protocol_ev.pdata[i] = data_frame_receive.data[i];
    }
    fifo_push(fifo_response, &sys_data_to_fifo);
    break;
  case RECEIVE_END:
    // do something
    sys_data_to_fifo.protocol_ev = SYS_EVENT_PROTOCOL_COMPLETE;
    fifo_push(fifo_response, &sys_data_to_fifo);
    break;
  case RECEIVE_TERMINATE:
    // do something
        sys_data_to_fifo.protocol_ev = SYS_EVENT_PROTOCOL_COMPLETE;
    fifo_push(fifo_response, &sys_data_to_fifo);
    break;

  // case PARSER:
  //   // do something
  //   break;
  default:
    sys_protocol_state = INIT;
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
/* End of file -------------------------------------------------------- */
