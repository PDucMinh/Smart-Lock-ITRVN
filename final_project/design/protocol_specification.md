# Data packet Design

## Data packet Structure

| HEADER | SEQUENCE | COMMAND (optional) | LENGTH | DATA (optional) | CRC |
| ------ | -------- | ------- | ------ | ---- | -- |
| A 8-bits value includes the first byte marking the operation of transaction, the last bytes display the length of data payload | A 8-bits value denotes the order of the data packet transferred. This value will increase by one after new message is created and it will be reset to zero after reaching the end of transaction | A 8-bits value have the predefined system command ID | A 8-bits value indicate length of data buffer | An array of 8-bits value containing the data needing to be transfered | On-going |
| 8 bits | 8 bits | 8 bits | 8 bits | Length * 8 bits | On-going |


## Header field specification
This field contains 2 bytes of data: 
- 8-bits OPERATION field: Contains information of system behavior or device operation in transaction. More details decribed in table below. 

| Operation ID | Operation | Description |
| -- | -- | -- |
| 0x01 | START | Start Session |
| 0x10 | TERMINATE | Terminate Session |
| 0x11 | DELETE | Delete data buffer have just sent | 
| 0x12 | END | Complete session or operation |
| 0x20 | REQUEST | Request data packet or operation |
| 0x21 | SEND | Send data packet or operation |


## LENGTH field specification
- 8-bits DATA LENGTH field: Contains information of packet length in transction. Some special mode modified in table below.

| Mode ID | Mode | Description | 
| -- | -- | -- | 
| 0x00 | NULL | No data in packet |
| 0xXX | Size | Data packet have XX size |

---
> Note: The maximum length payload is 100, which mean XX can not be over 0x64

## Table of Command ID 
| Command ID | Command Type | Command |
| -- | -- | -- |  
| | NONE | No command |
| | DELETE | Delete data at local |
| | SET | Write data to local |
| | REQUEST | Get data from local |

## Some example 

- 0x0100
