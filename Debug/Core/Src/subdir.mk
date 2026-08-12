################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/EtherCAT_spi.c \
../Core/Src/at24c04.c \
../Core/Src/calibration.c \
../Core/Src/crc.c \
../Core/Src/dma.c \
../Core/Src/filter.c \
../Core/Src/flash_storage.c \
../Core/Src/gpio.c \
../Core/Src/i2c.c \
../Core/Src/lha7668-8.c \
../Core/Src/lha7668.c \
../Core/Src/main.c \
../Core/Src/ringbuf.c \
../Core/Src/rs485.c \
../Core/Src/rs485_cmd.c \
../Core/Src/self_test.c \
../Core/Src/spi.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/tim.c \
../Core/Src/usart.c 

OBJS += \
./Core/Src/EtherCAT_spi.o \
./Core/Src/at24c04.o \
./Core/Src/calibration.o \
./Core/Src/crc.o \
./Core/Src/dma.o \
./Core/Src/filter.o \
./Core/Src/flash_storage.o \
./Core/Src/gpio.o \
./Core/Src/i2c.o \
./Core/Src/lha7668-8.o \
./Core/Src/lha7668.o \
./Core/Src/main.o \
./Core/Src/ringbuf.o \
./Core/Src/rs485.o \
./Core/Src/rs485_cmd.o \
./Core/Src/self_test.o \
./Core/Src/spi.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/tim.o \
./Core/Src/usart.o 

C_DEPS += \
./Core/Src/EtherCAT_spi.d \
./Core/Src/at24c04.d \
./Core/Src/calibration.d \
./Core/Src/crc.d \
./Core/Src/dma.d \
./Core/Src/filter.d \
./Core/Src/flash_storage.d \
./Core/Src/gpio.d \
./Core/Src/i2c.d \
./Core/Src/lha7668-8.d \
./Core/Src/lha7668.d \
./Core/Src/main.d \
./Core/Src/ringbuf.d \
./Core/Src/rs485.d \
./Core/Src/rs485_cmd.d \
./Core/Src/self_test.d \
./Core/Src/spi.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/tim.d \
./Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I"D:/ST/workspace/codeing/yundedongli/Core/Ethercat/Inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/EtherCAT_spi.cyclo ./Core/Src/EtherCAT_spi.d ./Core/Src/EtherCAT_spi.o ./Core/Src/EtherCAT_spi.su ./Core/Src/at24c04.cyclo ./Core/Src/at24c04.d ./Core/Src/at24c04.o ./Core/Src/at24c04.su ./Core/Src/calibration.cyclo ./Core/Src/calibration.d ./Core/Src/calibration.o ./Core/Src/calibration.su ./Core/Src/crc.cyclo ./Core/Src/crc.d ./Core/Src/crc.o ./Core/Src/crc.su ./Core/Src/dma.cyclo ./Core/Src/dma.d ./Core/Src/dma.o ./Core/Src/dma.su ./Core/Src/filter.cyclo ./Core/Src/filter.d ./Core/Src/filter.o ./Core/Src/filter.su ./Core/Src/flash_storage.cyclo ./Core/Src/flash_storage.d ./Core/Src/flash_storage.o ./Core/Src/flash_storage.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/i2c.cyclo ./Core/Src/i2c.d ./Core/Src/i2c.o ./Core/Src/i2c.su ./Core/Src/lha7668-8.cyclo ./Core/Src/lha7668-8.d ./Core/Src/lha7668-8.o ./Core/Src/lha7668-8.su ./Core/Src/lha7668.cyclo ./Core/Src/lha7668.d ./Core/Src/lha7668.o ./Core/Src/lha7668.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/ringbuf.cyclo ./Core/Src/ringbuf.d ./Core/Src/ringbuf.o ./Core/Src/ringbuf.su ./Core/Src/rs485.cyclo ./Core/Src/rs485.d ./Core/Src/rs485.o ./Core/Src/rs485.su ./Core/Src/rs485_cmd.cyclo ./Core/Src/rs485_cmd.d ./Core/Src/rs485_cmd.o ./Core/Src/rs485_cmd.su ./Core/Src/self_test.cyclo ./Core/Src/self_test.d ./Core/Src/self_test.o ./Core/Src/self_test.su ./Core/Src/spi.cyclo ./Core/Src/spi.d ./Core/Src/spi.o ./Core/Src/spi.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su ./Core/Src/tim.cyclo ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su ./Core/Src/usart.cyclo ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su

.PHONY: clean-Core-2f-Src

