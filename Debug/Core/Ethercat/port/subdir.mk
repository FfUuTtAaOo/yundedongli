################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Ethercat/port/el9800hw.c 

OBJS += \
./Core/Ethercat/port/el9800hw.o 

C_DEPS += \
./Core/Ethercat/port/el9800hw.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Ethercat/port/%.o Core/Ethercat/port/%.su Core/Ethercat/port/%.cyclo: ../Core/Ethercat/port/%.c Core/Ethercat/port/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I"D:/ST/workspace/codeing/yundedongli/Core/Ethercat/Inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Ethercat-2f-port

clean-Core-2f-Ethercat-2f-port:
	-$(RM) ./Core/Ethercat/port/el9800hw.cyclo ./Core/Ethercat/port/el9800hw.d ./Core/Ethercat/port/el9800hw.o ./Core/Ethercat/port/el9800hw.su

.PHONY: clean-Core-2f-Ethercat-2f-port

