# Data packet Design

## Data packet Structure

| HEADER | SEQUENCE | COMMAND | DATA |
| ------ | -------- | ------- | ---- |
| A 16-bits value includes the first byte marking the operation of transaction, the last bytes display the length of data payload | A 8-bits value denotes the order of the data packet transferred. This value will increase by one after new message is created and it will be reset to zero after reaching the end of transaction | A 8-bits value have the predefined system command ID | An array of 8-bits value containing the data needing to be transfered |


## Header field specification
This field contains 2 bytes of data: 
- 8-bits OPERATION field: Contains information of system behavior or device operation in transaction. More details decribed in table below. 

| Operation ID | Operation | Description | 
| -- | -- | -- |
| 0x01 | START | Start Session |
| 0x10 | TERMINATE | Terminate Session |
| 0x11 | DELETE | Delete data buffer | 
| 0x12 | END | Complete session or operation |
| 0x20 | REQUEST | Request data packet or operation |
| 0x21 | SEND | Send data packet or operation |

---
> Note: Operations begin with 0x1 or 0x0 followed by 0x00 data length

> For example: 0x0100

- 8-bits DATA LENGTH field: Contains information of packet length in transction. Some special mode modified in table below.

| Mode ID | Mode | Description | 
| -- | -- | -- | 
| 0x00 | NULL | No data in packet |
| 0xFF | FULL | Data packet have maximum size | 
| 0xXX | Size | Data packet have XX size |

---
> Note: The maximum length payload is 100, which mean XX can not be over 0x64

## Table of Command ID 
| Command ID | Command |
| -- | -- |  
| 0x10 | GET_TIME |
| 0x11 | SET_TIME |
| 0x12 | SET_ALARM |
| 0x13 | NOTIFY_ALARM |
| 0x14 | RESET_ALARM |
| 0x01 | ACK |
| 0x02 | NACK |