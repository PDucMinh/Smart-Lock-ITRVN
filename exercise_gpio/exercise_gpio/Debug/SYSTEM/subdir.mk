################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SYSTEM/SYSTEM_BUTTON.c \
../SYSTEM/SYSTEM_MANAGER.c 

OBJS += \
./SYSTEM/SYSTEM_BUTTON.o \
./SYSTEM/SYSTEM_MANAGER.o 

C_DEPS += \
./SYSTEM/SYSTEM_BUTTON.d \
./SYSTEM/SYSTEM_MANAGER.d 


# Each subdirectory must supply rules for building sources it contributes
SYSTEM/%.o SYSTEM/%.su SYSTEM/%.cyclo: ../SYSTEM/%.c SYSTEM/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/ASUS/Desktop/06-2024-itr-intern-group-3/exercise_gpio/exercise_gpio/DEVICE_DRIVER" -I"C:/Users/ASUS/Desktop/06-2024-itr-intern-group-3/exercise_gpio/exercise_gpio/SYSTEM" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-SYSTEM

clean-SYSTEM:
	-$(RM) ./SYSTEM/SYSTEM_BUTTON.cyclo ./SYSTEM/SYSTEM_BUTTON.d ./SYSTEM/SYSTEM_BUTTON.o ./SYSTEM/SYSTEM_BUTTON.su ./SYSTEM/SYSTEM_MANAGER.cyclo ./SYSTEM/SYSTEM_MANAGER.d ./SYSTEM/SYSTEM_MANAGER.o ./SYSTEM/SYSTEM_MANAGER.su

.PHONY: clean-SYSTEM

