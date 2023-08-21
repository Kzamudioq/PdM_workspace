################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/API/Scr/dht22.c \
../Drivers/API/Scr/gpio.c \
../Drivers/API/Scr/temperature.c \
../Drivers/API/Scr/tim.c \
../Drivers/API/Scr/usart.c 

OBJS += \
./Drivers/API/Scr/dht22.o \
./Drivers/API/Scr/gpio.o \
./Drivers/API/Scr/temperature.o \
./Drivers/API/Scr/tim.o \
./Drivers/API/Scr/usart.o 

C_DEPS += \
./Drivers/API/Scr/dht22.d \
./Drivers/API/Scr/gpio.d \
./Drivers/API/Scr/temperature.d \
./Drivers/API/Scr/tim.d \
./Drivers/API/Scr/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/API/Scr/%.o Drivers/API/Scr/%.su Drivers/API/Scr/%.cyclo: ../Drivers/API/Scr/%.c Drivers/API/Scr/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/ktzam/STM32CubeIDE/workspace_1.13.0/F401RE SENSOR/Drivers" -I"C:/Users/ktzam/STM32CubeIDE/workspace_1.13.0/F401RE SENSOR/Drivers/API" -I"C:/Users/ktzam/STM32CubeIDE/workspace_1.13.0/F401RE SENSOR/Drivers/API/Inc" -I"C:/Users/ktzam/STM32CubeIDE/workspace_1.13.0/F401RE SENSOR/Drivers/API/Scr" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-API-2f-Scr

clean-Drivers-2f-API-2f-Scr:
	-$(RM) ./Drivers/API/Scr/dht22.cyclo ./Drivers/API/Scr/dht22.d ./Drivers/API/Scr/dht22.o ./Drivers/API/Scr/dht22.su ./Drivers/API/Scr/gpio.cyclo ./Drivers/API/Scr/gpio.d ./Drivers/API/Scr/gpio.o ./Drivers/API/Scr/gpio.su ./Drivers/API/Scr/temperature.cyclo ./Drivers/API/Scr/temperature.d ./Drivers/API/Scr/temperature.o ./Drivers/API/Scr/temperature.su ./Drivers/API/Scr/tim.cyclo ./Drivers/API/Scr/tim.d ./Drivers/API/Scr/tim.o ./Drivers/API/Scr/tim.su ./Drivers/API/Scr/usart.cyclo ./Drivers/API/Scr/usart.d ./Drivers/API/Scr/usart.o ./Drivers/API/Scr/usart.su

.PHONY: clean-Drivers-2f-API-2f-Scr

