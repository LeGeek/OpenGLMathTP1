################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Point3D.cpp \
../src/TpMathException.cpp \
../src/tpMath.cpp 

OBJS += \
./src/Point3D.o \
./src/TpMathException.o \
./src/tpMath.o 

CPP_DEPS += \
./src/Point3D.d \
./src/TpMathException.d \
./src/tpMath.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


