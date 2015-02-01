################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/DataRecord.cpp \
../src/WorkChunk.cpp \
../src/bdif1_test.cpp 

OBJS += \
./src/DataRecord.o \
./src/WorkChunk.o \
./src/bdif1_test.o 

CPP_DEPS += \
./src/DataRecord.d \
./src/WorkChunk.d \
./src/bdif1_test.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


