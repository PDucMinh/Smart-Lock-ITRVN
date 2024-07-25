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

1. Clone the project repository from [GitHub ↗](https://github.com/vyluu-itr/06-2024-itr-intern-group-3/tree/main/final_project).
2. Set up your development environment with the required IDE (STM32CubeIDE) and toolchain and open the project in the chosen IDE.
3. Read our [wire connect diagram](./wire_connection.png) to connect the necessary peripherals or sensors to the STM32 microcontroller.
4. Deploy the firmware to the STM32 microcontroller using the appropriate flashing method (e.g., ST-Link, DFU, or bootloader).

## Contributing
We welcome contributions to this project! To ensure a smooth contribution process, please follow the guidelines below:

1. Make sure you have read and understood the Contribution Guide before getting started.
2. Check the Issues to see if there are any existing issues or requested features.
3. Create a new branch from main to work on your new feature: git checkout -b new-feature.
4. Make the necessary changes, additions, or bug fixes in the source code.
5. Double-check the code to ensure there are no errors and that it follows the coding guidelines.
6. Create a Pull Request with a detailed description of the changes you have made.
7. Wait for feedback and make any requested changes from the code reviewer.
8. Once your Pull Request is approved, thank you for your contribution and support!
* **Note**: Contributions to this project are welcome. If you find any issues or have suggestions for improvements, please submit a pull request or open an issue on the project's [GitHub repository](https://github.com/vyluu-itr/06-2024-itr-intern-group-3/tree/main/final_project) or contact us [ITR VN](https://itrvn.com/).

## Demo Smart Door Clock 
Below are a few typical features of Smart Door Lock 

## Developer team
1. **Phạm Đức Minh**
2. **Nguyễn Nhật Hưng**
3. **Nguyễn Tấn Phát**
