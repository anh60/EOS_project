################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../libraries/CMSIS/Device/ST/STM32H7xx/Source/Templates/gcc/startup_stm32h747xx.S 

OBJS += \
./libraries/CMSIS/Device/ST/STM32H7xx/Source/Templates/gcc/startup_stm32h747xx.o 

S_UPPER_DEPS += \
./libraries/CMSIS/Device/ST/STM32H7xx/Source/Templates/gcc/startup_stm32h747xx.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/CMSIS/Device/ST/STM32H7xx/Source/Templates/gcc/%.o: ../libraries/CMSIS/Device/ST/STM32H7xx/Source/Templates/gcc/%.S
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -x assembler-with-cpp -I"C:\Users\Mja\Documents\EMECS\PoliTO\Operating systems for embedded systems\Project\EOS_project\STM32" -Xassembler -mimplicit-it=thumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

