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

