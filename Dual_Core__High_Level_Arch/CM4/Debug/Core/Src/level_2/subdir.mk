################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/level_2/board_opener.c \
../Core/Src/level_2/init_CM4.c \
../Core/Src/level_2/motor_controller.c \
../Core/Src/level_2/task_manager.c \
../Core/Src/level_2/token_colour_separator.c \
../Core/Src/level_2/token_picker_controller.c \
../Core/Src/level_2/user_detector.c 

OBJS += \
./Core/Src/level_2/board_opener.o \
./Core/Src/level_2/init_CM4.o \
./Core/Src/level_2/motor_controller.o \
./Core/Src/level_2/task_manager.o \
./Core/Src/level_2/token_colour_separator.o \
./Core/Src/level_2/token_picker_controller.o \
./Core/Src/level_2/user_detector.o 

C_DEPS += \
./Core/Src/level_2/board_opener.d \
./Core/Src/level_2/init_CM4.d \
./Core/Src/level_2/motor_controller.d \
./Core/Src/level_2/task_manager.d \
./Core/Src/level_2/token_colour_separator.d \
./Core/Src/level_2/token_picker_controller.d \
./Core/Src/level_2/user_detector.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/level_2/%.o Core/Src/level_2/%.su Core/Src/level_2/%.cyclo: ../Core/Src/level_2/%.c Core/Src/level_2/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32H755xx -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-level_2

clean-Core-2f-Src-2f-level_2:
	-$(RM) ./Core/Src/level_2/board_opener.cyclo ./Core/Src/level_2/board_opener.d ./Core/Src/level_2/board_opener.o ./Core/Src/level_2/board_opener.su ./Core/Src/level_2/init_CM4.cyclo ./Core/Src/level_2/init_CM4.d ./Core/Src/level_2/init_CM4.o ./Core/Src/level_2/init_CM4.su ./Core/Src/level_2/motor_controller.cyclo ./Core/Src/level_2/motor_controller.d ./Core/Src/level_2/motor_controller.o ./Core/Src/level_2/motor_controller.su ./Core/Src/level_2/task_manager.cyclo ./Core/Src/level_2/task_manager.d ./Core/Src/level_2/task_manager.o ./Core/Src/level_2/task_manager.su ./Core/Src/level_2/token_colour_separator.cyclo ./Core/Src/level_2/token_colour_separator.d ./Core/Src/level_2/token_colour_separator.o ./Core/Src/level_2/token_colour_separator.su ./Core/Src/level_2/token_picker_controller.cyclo ./Core/Src/level_2/token_picker_controller.d ./Core/Src/level_2/token_picker_controller.o ./Core/Src/level_2/token_picker_controller.su ./Core/Src/level_2/user_detector.cyclo ./Core/Src/level_2/user_detector.d ./Core/Src/level_2/user_detector.o ./Core/Src/level_2/user_detector.su

.PHONY: clean-Core-2f-Src-2f-level_2

