################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Configuration.cpp \
../src/PipeExchange.cpp 

OBJS += \
./src/Configuration.o \
./src/PipeExchange.o 

CPP_DEPS += \
./src/Configuration.d \
./src/PipeExchange.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ `pkg-config gtkmm-2.4 --cflags --libs` -I/usr/include/gtkmm-2.4 -I/usr/include/giomm-2.4 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


