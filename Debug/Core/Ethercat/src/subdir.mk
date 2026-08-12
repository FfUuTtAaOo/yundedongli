################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Ethercat/src/SampleApplicationInterface.c \
../Core/Ethercat/src/aoeappl.c \
../Core/Ethercat/src/bootmode.c \
../Core/Ethercat/src/cia402appl.c \
../Core/Ethercat/src/coeappl.c \
../Core/Ethercat/src/diag.c \
../Core/Ethercat/src/ecataoe.c \
../Core/Ethercat/src/ecatappl.c \
../Core/Ethercat/src/ecatcoe.c \
../Core/Ethercat/src/ecateoe.c \
../Core/Ethercat/src/ecatfoe.c \
../Core/Ethercat/src/ecatslv.c \
../Core/Ethercat/src/ecatsoe.c \
../Core/Ethercat/src/emcy.c \
../Core/Ethercat/src/eoeappl.c \
../Core/Ethercat/src/foeappl.c \
../Core/Ethercat/src/mailbox.c \
../Core/Ethercat/src/objdef.c \
../Core/Ethercat/src/sampleappl.c \
../Core/Ethercat/src/sdoserv.c \
../Core/Ethercat/src/six_component_force.c \
../Core/Ethercat/src/testappl.c 

OBJS += \
./Core/Ethercat/src/SampleApplicationInterface.o \
./Core/Ethercat/src/aoeappl.o \
./Core/Ethercat/src/bootmode.o \
./Core/Ethercat/src/cia402appl.o \
./Core/Ethercat/src/coeappl.o \
./Core/Ethercat/src/diag.o \
./Core/Ethercat/src/ecataoe.o \
./Core/Ethercat/src/ecatappl.o \
./Core/Ethercat/src/ecatcoe.o \
./Core/Ethercat/src/ecateoe.o \
./Core/Ethercat/src/ecatfoe.o \
./Core/Ethercat/src/ecatslv.o \
./Core/Ethercat/src/ecatsoe.o \
./Core/Ethercat/src/emcy.o \
./Core/Ethercat/src/eoeappl.o \
./Core/Ethercat/src/foeappl.o \
./Core/Ethercat/src/mailbox.o \
./Core/Ethercat/src/objdef.o \
./Core/Ethercat/src/sampleappl.o \
./Core/Ethercat/src/sdoserv.o \
./Core/Ethercat/src/six_component_force.o \
./Core/Ethercat/src/testappl.o 

C_DEPS += \
./Core/Ethercat/src/SampleApplicationInterface.d \
./Core/Ethercat/src/aoeappl.d \
./Core/Ethercat/src/bootmode.d \
./Core/Ethercat/src/cia402appl.d \
./Core/Ethercat/src/coeappl.d \
./Core/Ethercat/src/diag.d \
./Core/Ethercat/src/ecataoe.d \
./Core/Ethercat/src/ecatappl.d \
./Core/Ethercat/src/ecatcoe.d \
./Core/Ethercat/src/ecateoe.d \
./Core/Ethercat/src/ecatfoe.d \
./Core/Ethercat/src/ecatslv.d \
./Core/Ethercat/src/ecatsoe.d \
./Core/Ethercat/src/emcy.d \
./Core/Ethercat/src/eoeappl.d \
./Core/Ethercat/src/foeappl.d \
./Core/Ethercat/src/mailbox.d \
./Core/Ethercat/src/objdef.d \
./Core/Ethercat/src/sampleappl.d \
./Core/Ethercat/src/sdoserv.d \
./Core/Ethercat/src/six_component_force.d \
./Core/Ethercat/src/testappl.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Ethercat/src/%.o Core/Ethercat/src/%.su Core/Ethercat/src/%.cyclo: ../Core/Ethercat/src/%.c Core/Ethercat/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I"D:/ST/workspace/codeing/yundedongli/Core/Ethercat/Inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Ethercat-2f-src

clean-Core-2f-Ethercat-2f-src:
	-$(RM) ./Core/Ethercat/src/SampleApplicationInterface.cyclo ./Core/Ethercat/src/SampleApplicationInterface.d ./Core/Ethercat/src/SampleApplicationInterface.o ./Core/Ethercat/src/SampleApplicationInterface.su ./Core/Ethercat/src/aoeappl.cyclo ./Core/Ethercat/src/aoeappl.d ./Core/Ethercat/src/aoeappl.o ./Core/Ethercat/src/aoeappl.su ./Core/Ethercat/src/bootmode.cyclo ./Core/Ethercat/src/bootmode.d ./Core/Ethercat/src/bootmode.o ./Core/Ethercat/src/bootmode.su ./Core/Ethercat/src/cia402appl.cyclo ./Core/Ethercat/src/cia402appl.d ./Core/Ethercat/src/cia402appl.o ./Core/Ethercat/src/cia402appl.su ./Core/Ethercat/src/coeappl.cyclo ./Core/Ethercat/src/coeappl.d ./Core/Ethercat/src/coeappl.o ./Core/Ethercat/src/coeappl.su ./Core/Ethercat/src/diag.cyclo ./Core/Ethercat/src/diag.d ./Core/Ethercat/src/diag.o ./Core/Ethercat/src/diag.su ./Core/Ethercat/src/ecataoe.cyclo ./Core/Ethercat/src/ecataoe.d ./Core/Ethercat/src/ecataoe.o ./Core/Ethercat/src/ecataoe.su ./Core/Ethercat/src/ecatappl.cyclo ./Core/Ethercat/src/ecatappl.d ./Core/Ethercat/src/ecatappl.o ./Core/Ethercat/src/ecatappl.su ./Core/Ethercat/src/ecatcoe.cyclo ./Core/Ethercat/src/ecatcoe.d ./Core/Ethercat/src/ecatcoe.o ./Core/Ethercat/src/ecatcoe.su ./Core/Ethercat/src/ecateoe.cyclo ./Core/Ethercat/src/ecateoe.d ./Core/Ethercat/src/ecateoe.o ./Core/Ethercat/src/ecateoe.su ./Core/Ethercat/src/ecatfoe.cyclo ./Core/Ethercat/src/ecatfoe.d ./Core/Ethercat/src/ecatfoe.o ./Core/Ethercat/src/ecatfoe.su ./Core/Ethercat/src/ecatslv.cyclo ./Core/Ethercat/src/ecatslv.d ./Core/Ethercat/src/ecatslv.o ./Core/Ethercat/src/ecatslv.su ./Core/Ethercat/src/ecatsoe.cyclo ./Core/Ethercat/src/ecatsoe.d ./Core/Ethercat/src/ecatsoe.o ./Core/Ethercat/src/ecatsoe.su ./Core/Ethercat/src/emcy.cyclo ./Core/Ethercat/src/emcy.d ./Core/Ethercat/src/emcy.o ./Core/Ethercat/src/emcy.su ./Core/Ethercat/src/eoeappl.cyclo ./Core/Ethercat/src/eoeappl.d ./Core/Ethercat/src/eoeappl.o ./Core/Ethercat/src/eoeappl.su ./Core/Ethercat/src/foeappl.cyclo ./Core/Ethercat/src/foeappl.d ./Core/Ethercat/src/foeappl.o ./Core/Ethercat/src/foeappl.su ./Core/Ethercat/src/mailbox.cyclo ./Core/Ethercat/src/mailbox.d ./Core/Ethercat/src/mailbox.o ./Core/Ethercat/src/mailbox.su ./Core/Ethercat/src/objdef.cyclo ./Core/Ethercat/src/objdef.d ./Core/Ethercat/src/objdef.o ./Core/Ethercat/src/objdef.su ./Core/Ethercat/src/sampleappl.cyclo ./Core/Ethercat/src/sampleappl.d ./Core/Ethercat/src/sampleappl.o ./Core/Ethercat/src/sampleappl.su ./Core/Ethercat/src/sdoserv.cyclo ./Core/Ethercat/src/sdoserv.d ./Core/Ethercat/src/sdoserv.o ./Core/Ethercat/src/sdoserv.su ./Core/Ethercat/src/six_component_force.cyclo ./Core/Ethercat/src/six_component_force.d ./Core/Ethercat/src/six_component_force.o ./Core/Ethercat/src/six_component_force.su ./Core/Ethercat/src/testappl.cyclo ./Core/Ethercat/src/testappl.d ./Core/Ethercat/src/testappl.o ./Core/Ethercat/src/testappl.su

.PHONY: clean-Core-2f-Ethercat-2f-src

