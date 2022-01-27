################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/src/dynamixel.c \
../Drivers/src/gps.c \
../Drivers/src/led.c \
../Drivers/src/pwm.c \
../Drivers/src/qep.c \
../Drivers/src/segment.c \
../Drivers/src/serial.c \
../Drivers/src/serial_halfduflex.c \
../Drivers/src/system_config.c \
../Drivers/src/timer.c 

OBJS += \
./Drivers/src/dynamixel.o \
./Drivers/src/gps.o \
./Drivers/src/led.o \
./Drivers/src/pwm.o \
./Drivers/src/qep.o \
./Drivers/src/segment.o \
./Drivers/src/serial.o \
./Drivers/src/serial_halfduflex.o \
./Drivers/src/system_config.o \
./Drivers/src/timer.o 

C_DEPS += \
./Drivers/src/dynamixel.d \
./Drivers/src/gps.d \
./Drivers/src/led.d \
./Drivers/src/pwm.d \
./Drivers/src/qep.d \
./Drivers/src/segment.d \
./Drivers/src/serial.d \
./Drivers/src/serial_halfduflex.d \
./Drivers/src/system_config.d \
./Drivers/src/timer.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/src/dynamixel.o: ../Drivers/src/dynamixel.c Drivers/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Drivers/inc -I../Drivers/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/src/dynamixel.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/src/gps.o: ../Drivers/src/gps.c Drivers/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Drivers/inc -I../Drivers/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/src/gps.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/src/led.o: ../Drivers/src/led.c Drivers/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Drivers/inc -I../Drivers/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/src/led.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/src/pwm.o: ../Drivers/src/pwm.c Drivers/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Drivers/inc -I../Drivers/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/src/pwm.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/src/qep.o: ../Drivers/src/qep.c Drivers/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Drivers/inc -I../Drivers/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/src/qep.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/src/segment.o: ../Drivers/src/segment.c Drivers/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Drivers/inc -I../Drivers/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/src/segment.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/src/serial.o: ../Drivers/src/serial.c Drivers/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Drivers/inc -I../Drivers/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/src/serial.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/src/serial_halfduflex.o: ../Drivers/src/serial_halfduflex.c Drivers/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Drivers/inc -I../Drivers/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/src/serial_halfduflex.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/src/system_config.o: ../Drivers/src/system_config.c Drivers/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Drivers/inc -I../Drivers/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/src/system_config.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/src/timer.o: ../Drivers/src/timer.c Drivers/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Drivers/inc -I../Drivers/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/src/timer.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

