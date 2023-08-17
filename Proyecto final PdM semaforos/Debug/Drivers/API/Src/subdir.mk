################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/API/Src/API_Semaphores.c \
../Drivers/API/Src/API_button.c \
../Drivers/API/Src/API_uart2.c 

OBJS += \
./Drivers/API/Src/API_Semaphores.o \
./Drivers/API/Src/API_button.o \
./Drivers/API/Src/API_uart2.o 

C_DEPS += \
./Drivers/API/Src/API_Semaphores.d \
./Drivers/API/Src/API_button.d \
./Drivers/API/Src/API_uart2.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/API/Src/%.o Drivers/API/Src/%.su Drivers/API/Src/%.cyclo: ../Drivers/API/Src/%.c Drivers/API/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/ktzam/STM32CubeIDE/workspace_1.13.0/Proyecto final PdM semaforos/Drivers/API" -I"C:/Users/ktzam/STM32CubeIDE/workspace_1.13.0/Proyecto final PdM semaforos/Drivers/API/Inc" -I"C:/Users/ktzam/STM32CubeIDE/workspace_1.13.0/Proyecto final PdM semaforos/Drivers/API/Src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-API-2f-Src

clean-Drivers-2f-API-2f-Src:
	-$(RM) ./Drivers/API/Src/API_Semaphores.cyclo ./Drivers/API/Src/API_Semaphores.d ./Drivers/API/Src/API_Semaphores.o ./Drivers/API/Src/API_Semaphores.su ./Drivers/API/Src/API_button.cyclo ./Drivers/API/Src/API_button.d ./Drivers/API/Src/API_button.o ./Drivers/API/Src/API_button.su ./Drivers/API/Src/API_uart2.cyclo ./Drivers/API/Src/API_uart2.d ./Drivers/API/Src/API_uart2.o ./Drivers/API/Src/API_uart2.su

.PHONY: clean-Drivers-2f-API-2f-Src

