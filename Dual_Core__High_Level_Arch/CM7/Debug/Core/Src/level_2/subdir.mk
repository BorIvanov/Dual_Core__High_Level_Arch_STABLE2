################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/level_2/UART_controller.c \
../Core/Src/level_2/game_controller.c \
../Core/Src/level_2/game_end.c \
../Core/Src/level_2/init_CM7.c \
../Core/Src/level_2/task_generator.c 

OBJS += \
./Core/Src/level_2/UART_controller.o \
./Core/Src/level_2/game_controller.o \
./Core/Src/level_2/game_end.o \
./Core/Src/level_2/init_CM7.o \
./Core/Src/level_2/task_generator.o 

C_DEPS += \
./Core/Src/level_2/UART_controller.d \
./Core/Src/level_2/game_controller.d \
./Core/Src/level_2/game_end.d \
./Core/Src/level_2/init_CM7.d \
./Core/Src/level_2/task_generator.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/level_2/%.o Core/Src/level_2/%.su Core/Src/level_2/%.cyclo: ../Core/Src/level_2/%.c Core/Src/level_2/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H755xx -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-level_2

clean-Core-2f-Src-2f-level_2:
	-$(RM) ./Core/Src/level_2/UART_controller.cyclo ./Core/Src/level_2/UART_controller.d ./Core/Src/level_2/UART_controller.o ./Core/Src/level_2/UART_controller.su ./Core/Src/level_2/game_controller.cyclo ./Core/Src/level_2/game_controller.d ./Core/Src/level_2/game_controller.o ./Core/Src/level_2/game_controller.su ./Core/Src/level_2/game_end.cyclo ./Core/Src/level_2/game_end.d ./Core/Src/level_2/game_end.o ./Core/Src/level_2/game_end.su ./Core/Src/level_2/init_CM7.cyclo ./Core/Src/level_2/init_CM7.d ./Core/Src/level_2/init_CM7.o ./Core/Src/level_2/init_CM7.su ./Core/Src/level_2/task_generator.cyclo ./Core/Src/level_2/task_generator.d ./Core/Src/level_2/task_generator.o ./Core/Src/level_2/task_generator.su

.PHONY: clean-Core-2f-Src-2f-level_2

