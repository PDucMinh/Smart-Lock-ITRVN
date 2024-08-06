# Smart Door Lock Release Notes

## Version 1.0.0
### New Features
- Driver for controlling color of RGB led
- Bsp class supporting access to MCU's peripheral to control RGB led
### Bug Fixes
- Issue in generate PWM pulse with 0% duty cycle
- Issue in casting float data type to uint32 data type when driver calling to bsp API for generating PWM pulse.
- Choosing approriate brightness of led red, led green, led blue to have the correct color
## Version 1.0.1
### New Features
- Driver for IR sensor detection
- Middle ware layer: scheduler support timer
### Bug Fixes
- Issue in reading IR sensor state
- Issue in checking gpio mode when apply scheduler to read input