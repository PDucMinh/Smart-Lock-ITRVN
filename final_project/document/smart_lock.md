# SMART DOOR LOCK
<img src = "smart_door_lock.png" alt = "smart_door_lock" width = "500" height = "300">

## Purpose
The purpose of this project is to create a door lock that allows users to unlock it by entering a password or scanning a card. The system will record the chronological status of the door lock, this information is then displayed on the GUI. The system will emit a signal sound when the user unlocks (different sounds when unlocking successfully and vice versa). In this project, a RGB LED is utilized to simulate the status of the door. Furthermore, the system also allows admin rights to access, monitor or change passwords...

## Features
The Smart Door Lock project includes the following features:

## Required Modules
| Module                   | Functionality                                     |
| -------------------------| ------------------------------------------------- |
| STM32F411VE              | Main microcontroller for the system               |
| RFID NFC 13.56MHz RC522  | User can unlock system by using key tags          |
| TTP229 Touch Keypad      | Allows users to enter password                    |
| PL2102                   | Transmit data between GUI and system              |
| OLED LCD 0.96 inch       | Display information according to functions        |
| Buzzer                   | Alerts users if the password is correct or not    |
| RGB Led                  | Status indicator lights for the door              |
| RTC DS1307               | Real-time clock module for timekeeping            |

## Technologies
| Module                   |        |
| -------------------------| -------|
| RFID NFC 13.56MHz RC522  | SPI    |
| TTP229 Touch Keypad      | GPIO   |
| PL2102                   | UART   |
| OLED LCD 0.96 inch       | I2C    |
| Buzzer                   | PWM    |
| RGB Led                  | PWM    |
| RTC DS1307               | I2C    |

## Firmware Architecture

## Developer team
1. **Phạm Đức Minh**
2. **Nguyễn Nhật Hưng**
3. **Nguyễn Tấn Phát**
