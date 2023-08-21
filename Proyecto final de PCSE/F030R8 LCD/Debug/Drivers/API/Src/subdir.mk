################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/API/Src/DFR0928.c \
../Drivers/API/Src/DFR0928_GFX.c \
../Drivers/API/Src/fonts.c \
../Drivers/API/Src/gpio.c \
../Drivers/API/Src/main.c \
../Drivers/API/Src/spi.c \
../Drivers/API/Src/usart.c 

OBJS += \
./Drivers/API/Src/DFR0928.o \
./Drivers/API/Src/DFR0928_GFX.o \
./Drivers/API/Src/fonts.o \
./Drivers/API/Src/gpio.o \
./Drivers/API/Src/main.o \
./Drivers/API/Src/spi.o \
./Drivers/API/Src/usart.o 

C_DEPS += \
./Drivers/API/Src/DFR0928.d \
./Drivers/API/Src/DFR0928_GFX.d \
./Drivers/API/Src/fonts.d \
./Drivers/API/Src/gpio.d \
./Drivers/API/Src/main.d \
./Drivers/API/Src/spi.d \
./Drivers/API/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/API/Src/%.o Drivers/API/Src/%.su Drivers/API/Src/%.cyclo: ../Drivers/API/Src/%.c Drivers/API/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030x8 -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/ktzam/STM32CubeIDE/workspace_1.13.0/F030R8 LCD/Drivers/API" -I"C:/Users/ktzam/STM32CubeIDE/workspace_1.13.0/F030R8 LCD/Drivers/API/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-API-2f-Src

clean-Drivers-2f-API-2f-Src:
	-$(RM) ./Drivers/API/Src/DFR0928.cyclo ./Drivers/API/Src/DFR0928.d ./Drivers/API/Src/DFR0928.o ./Drivers/API/Src/DFR0928.su ./Drivers/API/Src/DFR0928_GFX.cyclo ./Drivers/API/Src/DFR0928_GFX.d ./Drivers/API/Src/DFR0928_GFX.o ./Drivers/API/Src/DFR0928_GFX.su ./Drivers/API/Src/fonts.cyclo ./Drivers/API/Src/fonts.d ./Drivers/API/Src/fonts.o ./Drivers/API/Src/fonts.su ./Drivers/API/Src/gpio.cyclo ./Drivers/API/Src/gpio.d ./Drivers/API/Src/gpio.o ./Drivers/API/Src/gpio.su ./Drivers/API/Src/main.cyclo ./Drivers/API/Src/main.d ./Drivers/API/Src/main.o ./Drivers/API/Src/main.su ./Drivers/API/Src/spi.cyclo ./Drivers/API/Src/spi.d ./Drivers/API/Src/spi.o ./Drivers/API/Src/spi.su ./Drivers/API/Src/usart.cyclo ./Drivers/API/Src/usart.d ./Drivers/API/Src/usart.o ./Drivers/API/Src/usart.su

.PHONY: clean-Drivers-2f-API-2f-Src

