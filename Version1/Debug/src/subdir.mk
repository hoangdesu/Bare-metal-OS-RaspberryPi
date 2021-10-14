################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/framebf.c \
../src/main.c \
../src/mbox.c \
../src/printf.c \
../src/uart.c 

S_UPPER_SRCS += \
../src/start.S 

OBJS += \
./src/framebf.o \
./src/main.o \
./src/mbox.o \
./src/printf.o \
./src/start.o \
./src/uart.o 

C_DEPS += \
./src/framebf.d \
./src/main.d \
./src/mbox.d \
./src/printf.d \
./src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	aarch64-none-elf-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.S src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Assembler'
	aarch64-none-elf-as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


