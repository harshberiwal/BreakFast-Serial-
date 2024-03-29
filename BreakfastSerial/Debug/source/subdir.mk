################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/cbfifo.c \
../source/command_processor.c \
../source/hexdump.c \
../source/main.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/sysclock.c \
../source/test_cbfifo.c \
../source/uart.c 

C_DEPS += \
./source/cbfifo.d \
./source/command_processor.d \
./source/hexdump.d \
./source/main.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/sysclock.d \
./source/test_cbfifo.d \
./source/uart.d 

OBJS += \
./source/cbfifo.o \
./source/command_processor.o \
./source/hexdump.o \
./source/main.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/sysclock.o \
./source/test_cbfifo.o \
./source/uart.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL25Z128VLK4 -D$(GEN_OPTS__FLAG) -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"C:\Users\Harsh\Documents\GitHub\PES_Assignment_6\BreakfastSerial\source" -I"C:\Users\Harsh\Documents\GitHub\PES_Assignment_6\BreakfastSerial" -I"C:\Users\Harsh\Documents\GitHub\PES_Assignment_6\BreakfastSerial\startup" -I"C:\Users\Harsh\Documents\GitHub\PES_Assignment_6\BreakfastSerial\CMSIS" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/cbfifo.d ./source/cbfifo.o ./source/command_processor.d ./source/command_processor.o ./source/hexdump.d ./source/hexdump.o ./source/main.d ./source/main.o ./source/mtb.d ./source/mtb.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o ./source/sysclock.d ./source/sysclock.o ./source/test_cbfifo.d ./source/test_cbfifo.o ./source/uart.d ./source/uart.o

.PHONY: clean-source

