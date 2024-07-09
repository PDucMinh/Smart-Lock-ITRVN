# IMPLEMENT LED BEHAVIOR BASE ON BUTTON SIGNAL
## Description
- Establish SYSTEM_MANAGER to execute led behavior base on state diagram below
- SYSTEM_MANAGER include 2 main API : system_manager_init and system_manager_loop
- system_manager_init will initialize MCU system include flash and system clock, driver button and driver led.
- system_manager_loop will execute repeatedly inside while loop 
- Input for switching system state in diagram is system_button_state provided by SYSTEM_BUTTON module
- Output in each state is controlling led with driver_led_set provided by DRIVER_LED module

## State diagram for implementing led behavior
![Led_state_diagram](https://github.com/BourneJH/string_detect_flowchart/assets/127610077/c6395aa9-a024-4708-970e-997f9af44af7)