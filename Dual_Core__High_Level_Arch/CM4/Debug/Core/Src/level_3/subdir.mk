################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/level_3/colour_sensor.c \
../Core/Src/level_3/motor_master.c \
../Core/Src/level_3/motor_x.c \
../Core/Src/level_3/motor_z.c \
../Core/Src/level_3/proximity_sensor.c \
../Core/Src/level_3/servo_controller.c \
../Core/Src/level_3/solenoid.c \
../Core/Src/level_3/token_picker_master.c \
../Core/Src/level_3/token_separator_master.c \
../Core/Src/level_3/vac_pump.c 

OBJS += \
./Core/Src/level_3/colour_sensor.o \
./Core/Src/level_3/motor_master.o \
./Core/Src/level_3/motor_x.o \
./Core/Src/level_3/motor_z.o \
./Core/Src/level_3/proximity_sensor.o \
./Core/Src/level_3/servo_controller.o \
./Core/Src/level_3/solenoid.o \
./Core/Src/level_3/token_picker_master.o \
./Core/Src/level_3/token_separator_master.o \
./Core/Src/level_3/vac_pump.o 

C_DEPS += \
./Core/Src/level_3/colour_sensor.d \
./Core/Src/level_3/motor_master.d \
./Core/Src/level_3/motor_x.d \
./Core/Src/level_3/motor_z.d \
./Core/Src/level_3/proximity_sensor.d \
./Core/Src/level_3/servo_controller.d \
./Core/Src/level_3/solenoid.d \
./Core/Src/level_3/token_picker_master.d \
./Core/Src/level_3/token_separator_master.d \
./Core/Src/level_3/vac_pump.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/level_3/%.o Core/Src/level_3/%.su Core/Src/level_3/%.cyclo: ../Core/Src/level_3/%.c Core/Src/level_3/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32H755xx -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-level_3

clean-Core-2f-Src-2f-level_3:
	-$(RM) ./Core/Src/level_3/colour_sensor.cyclo ./Core/Src/level_3/colour_sensor.d ./Core/Src/level_3/colour_sensor.o ./Core/Src/level_3/colour_sensor.su ./Core/Src/level_3/motor_master.cyclo ./Core/Src/level_3/motor_master.d ./Core/Src/level_3/motor_master.o ./Core/Src/level_3/motor_master.su ./Core/Src/level_3/motor_x.cyclo ./Core/Src/level_3/motor_x.d ./Core/Src/level_3/motor_x.o ./Core/Src/level_3/motor_x.su ./Core/Src/level_3/motor_z.cyclo ./Core/Src/level_3/motor_z.d ./Core/Src/level_3/motor_z.o ./Core/Src/level_3/motor_z.su ./Core/Src/level_3/proximity_sensor.cyclo ./Core/Src/level_3/proximity_sensor.d ./Core/Src/level_3/proximity_sensor.o ./Core/Src/level_3/proximity_sensor.su ./Core/Src/level_3/servo_controller.cyclo ./Core/Src/level_3/servo_controller.d ./Core/Src/level_3/servo_controller.o ./Core/Src/level_3/servo_controller.su ./Core/Src/level_3/solenoid.cyclo ./Core/Src/level_3/solenoid.d ./Core/Src/level_3/solenoid.o ./Core/Src/level_3/solenoid.su ./Core/Src/level_3/token_picker_master.cyclo ./Core/Src/level_3/token_picker_master.d ./Core/Src/level_3/token_picker_master.o ./Core/Src/level_3/token_picker_master.su ./Core/Src/level_3/token_separator_master.cyclo ./Core/Src/level_3/token_separator_master.d ./Core/Src/level_3/token_separator_master.o ./Core/Src/level_3/token_separator_master.su ./Core/Src/level_3/vac_pump.cyclo ./Core/Src/level_3/vac_pump.d ./Core/Src/level_3/vac_pump.o ./Core/Src/level_3/vac_pump.su

.PHONY: clean-Core-2f-Src-2f-level_3

