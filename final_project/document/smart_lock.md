# SMART DOOR LOCK
<img src = "smart_door_lock.png" alt = "smart_door_lock" width = "500" height = "300">

## Table of Contents
- [Technologies](#technologies)
- [Features](#features)
- [Usage](#usage)
- [Contributing](#contributing)
- [Demo Smart Door Lock](#demo-smart-door-lock)

## Technologies

* **STM32 Microcontroller**: This project is based on the STM32 microcontroller platform, which offers a wide range of microcontrollers with different performance levels and features.
*  **STM32CubeIDE**: This project was developed using popular IDEs which is STM32CubeIDE, provide tools for code development, debugging, and firmware deployment.
*  **Communication**: This project includes ways to communicate between MCU and modules: UART, I2C, SPI, PWM, GPIO.
*  **Peripheral Libraries**: The project utilizes peripheral libraries provided by the microcontroller manufacturer or third-party libraries to simplify the integration and configuration of peripherals.
*  **Other Device**: We intergrated a lot of device to increase experiment of customer and performance of device .

## Features

The Smart Door Lock project includes the following features:
1. **Unlock by entering password**: Users are able to enter password to unlock the door
2. **Unlock by scanning card**: Users can also swipe their card to unlock it instead of entering a password
3. **Record time**: The system can record the status of the door in real time, and then displayed on GUI
4. **Admin rights**: Admin can unlock all doors, monitor the system, and reset passwords
5. **Warning sound**: Alert users if the door is unlock or not
6. Read our [release note](./RELEASE_NOTE.md) for more details and Look forward to other exciting features in the future

## Usage

1. Clone the project repository from [GitHub ↗](https://github.com/vyluu-itr/06-2024-itr-intern-group-3/main/final_project).
2. Set up your development environment with the required IDE (STM32CubeIDE) and toolchain and open the project in the chosen IDE.
3. Read our [wire connect diagram](./wire_connection.png) to connect the necessary peripherals or sensors to the STM32 microcontroller.
4. Deploy the firmware to the STM32 microcontroller using the appropriate flashing method (e.g., ST-Link, DFU, or bootloader).





## Developer team
1. **Phạm Đức Minh**
2. **Nguyễn Nhật Hưng**
3. **Nguyễn Tấn Phát**
