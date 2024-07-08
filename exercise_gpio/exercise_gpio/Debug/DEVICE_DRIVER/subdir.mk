################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DEVICE_DRIVER/DRIVER_BUTTON.c \
../DEVICE_DRIVER/DRIVER_LED.c \
../DEVICE_DRIVER/DRIVER_MCU.c 

OBJS += \
./DEVICE_DRIVER/DRIVER_BUTTON.o \
./DEVICE_DRIVER/DRIVER_LED.o \
./DEVICE_DRIVER/DRIVER_MCU.o 

C_DEPS += \
./DEVICE_DRIVER/DRIVER_BUTTON.d \
./DEVICE_DRIVER/DRIVER_LED.d \
./DEVICE_DRIVER/DRIVER_MCU.d 


# Each subdirectory must supply rules for building sources it contributes
DEVICE_DRIVER/%.o DEVICE_DRIVER/%.su DEVICE_DRIVER/%.cyclo: ../DEVICE_DRIVER/%.c DEVICE_DRIVER/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/ASUS/Desktop/06-2024-itr-intern-group-3/exercise_gpio/exercise_gpio/DEVICE_DRIVER" -I"C:/Users/ASUS/Desktop/06-2024-itr-intern-group-3/exercise_gpio/exercise_gpio/SYSTEM" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-DEVICE_DRIVER

clean-DEVICE_DRIVER:
	-$(RM) ./DEVICE_DRIVER/DRIVER_BUTTON.cyclo ./DEVICE_DRIVER/DRIVER_BUTTON.d ./DEVICE_DRIVER/DRIVER_BUTTON.o ./DEVICE_DRIVER/DRIVER_BUTTON.su ./DEVICE_DRIVER/DRIVER_LED.cyclo ./DEVICE_DRIVER/DRIVER_LED.d ./DEVICE_DRIVER/DRIVER_LED.o ./DEVICE_DRIVER/DRIVER_LED.su ./DEVICE_DRIVER/DRIVER_MCU.cyclo ./DEVICE_DRIVER/DRIVER_MCU.d ./DEVICE_DRIVER/DRIVER_MCU.o ./DEVICE_DRIVER/DRIVER_MCU.su

.PHONY: clean-DEVICE_DRIVER

