################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../shaders/ShaderProgram.cpp 

OBJS += \
./shaders/ShaderProgram.o 

CPP_DEPS += \
./shaders/ShaderProgram.d 


# Each subdirectory must supply rules for building sources it contributes
shaders/%.o: ../shaders/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


