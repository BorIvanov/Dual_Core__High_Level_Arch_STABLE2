################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/peripheral_devices/adc.c \
../Core/Src/peripheral_devices/eth.c \
../Core/Src/peripheral_devices/gpio.c \
../Core/Src/peripheral_devices/i2c.c \
../Core/Src/peripheral_devices/tim.c \
../Core/Src/peripheral_devices/usart.c 

OBJS += \
./Core/Src/peripheral_devices/adc.o \
./Core/Src/peripheral_devices/eth.o \
./Core/Src/peripheral_devices/gpio.o \
./Core/Src/peripheral_devices/i2c.o \
./Core/Src/peripheral_devices/tim.o \
./Core/Src/peripheral_devices/usart.o 

C_DEPS += \
./Core/Src/peripheral_devices/adc.d \
./Core/Src/peripheral_devices/eth.d \
./Core/Src/peripheral_devices/gpio.d \
./Core/Src/peripheral_devices/i2c.d \
./Core/Src/peripheral_devices/tim.d \
./Core/Src/peripheral_devices/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/peripheral_devices/%.o Core/Src/peripheral_devices/%.su Core/Src/peripheral_devices/%.cyclo: ../Core/Src/peripheral_devices/%.c Core/Src/peripheral_devices/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32H755xx -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-peripheral_devices

clean-Core-2f-Src-2f-peripheral_devices:
	-$(RM) ./Core/Src/peripheral_devices/adc.cyclo ./Core/Src/peripheral_devices/adc.d ./Core/Src/peripheral_devices/adc.o ./Core/Src/peripheral_devices/adc.su ./Core/Src/peripheral_devices/eth.cyclo ./Core/Src/peripheral_devices/eth.d ./Core/Src/peripheral_devices/eth.o ./Core/Src/peripheral_devices/eth.su ./Core/Src/peripheral_devices/gpio.cyclo ./Core/Src/peripheral_devices/gpio.d ./Core/Src/peripheral_devices/gpio.o ./Core/Src/peripheral_devices/gpio.su ./Core/Src/peripheral_devices/i2c.cyclo ./Core/Src/peripheral_devices/i2c.d ./Core/Src/peripheral_devices/i2c.o ./Core/Src/peripheral_devices/i2c.su ./Core/Src/peripheral_devices/tim.cyclo ./Core/Src/peripheral_devices/tim.d ./Core/Src/peripheral_devices/tim.o ./Core/Src/peripheral_devices/tim.su ./Core/Src/peripheral_devices/usart.cyclo ./Core/Src/peripheral_devices/usart.d ./Core/Src/peripheral_devices/usart.o ./Core/Src/peripheral_devices/usart.su

.PHONY: clean-Core-2f-Src-2f-peripheral_devices

