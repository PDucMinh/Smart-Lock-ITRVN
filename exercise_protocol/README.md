# Protocol Design

## Message Design
### Message Structure
- Message structure is defined with the following fields:
    + Header field: A 16-bit value includes the first byte marking the start of transaction and the content of transaction, the last bytes display the length of data payload. The maximum length of data payload is 100.
    + Sequence field: A 8-bit value denotes the order of the message and it will also indicate which command message that the received acknowlegdement message belong to. This value will increase by one after new message is created and it will be reset to zero after reaching the end of transaction.
    + Command field: A 8-bit value have the predefined command ID as listed bellow.
    + Data field: An array of 8-bit value containing the data needing to be transfered between app and MCU. The size of array is specified by to length field in header.
- Command ID list:
    + 0x10 : GET_TIME
    + 0x11 : SET_TIME
    + 0x12 : SET_ALARM
    + 0x13 : NOTIFY_ALARM
    + 0x14 : RESET_ALARM
    + 0x01 : ACK
    + 0x02 : NACK
- Header field:
    + Transaction denotion field:
        * 0xFF : Start of transaction
        * 0xEF : Content of transaction
    + Length denotion field:
        * 0x00 -> 0x64 : Lenght of data

### Table of definition

|   Header    |  Sequence   |  Command  |  Data  |
| ----------- | ----------- | --------- | ------ |
|   16 bits   |    8 bits   |  8 bits   | Length * 8 bits |

## Transmission Mechanism

### The transmission mechanism will be described in the following transmission diagram:
- The first diagram denote the case where there is no missing message on transmission line and response message from receiver is sent within time out period:

![no error transmission](https://github.com/user-attachments/assets/41f8a931-8cf5-4246-9cbf-67473eb465d6)

- The second diagram denote the case where there is missing message, the receiver detect the missing message within the time out period of transmitter and return NACK command to request the data to be re-transmitted. 

![FCC_FlowChart-protocol-error-msg drawio](https://github.com/user-attachments/assets/d77d9eee-24ff-4687-8fd1-2e9444df30ac)

- The third diagram denote the case where there is missing message. After time out period, the transmitter does not receive response and starts transmitting the same message again. In the second time, the receiver gets the message correctly but the ACK message is missing on transmission line. There for the transmitter transmits the message a third time after time out. The receiver after receiving the same message, it will not add the message to the buffer and start transmitting ACK message again. Due to receiving the ACK message correctly, the transmitter will reset time out counter, delete transmitted message from buffer.

![FCC_FlowChart-protocol-error-ack drawio](https://github.com/user-attachments/assets/70524bfd-ed78-4a69-b1e5-e04773c6d8bd)