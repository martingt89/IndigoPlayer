################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Graphic/MainWindow.cpp 

OBJS += \
./src/Graphic/MainWindow.o 

CPP_DEPS += \
./src/Graphic/MainWindow.d 


# Each subdirectory must supply rules for building sources it contributes
src/Graphic/%.o: ../src/Graphic/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ `pkg-config gtkmm-2.4 --cflags --libs` -I/usr/include/gtkmm-2.4 -I/usr/include/giomm-2.4 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


