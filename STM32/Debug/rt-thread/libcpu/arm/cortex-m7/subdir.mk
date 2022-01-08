################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rt-thread/libcpu/arm/cortex-m7/cpu_cache.c \
../rt-thread/libcpu/arm/cortex-m7/cpuport.c 

S_UPPER_SRCS += \
../rt-thread/libcpu/arm/cortex-m7/context_gcc.S 

OBJS += \
./rt-thread/libcpu/arm/cortex-m7/context_gcc.o \
./rt-thread/libcpu/arm/cortex-m7/cpu_cache.o \
./rt-thread/libcpu/arm/cortex-m7/cpuport.o 

S_UPPER_DEPS += \
./rt-thread/libcpu/arm/cortex-m7/context_gcc.d 

C_DEPS += \
./rt-thread/libcpu/arm/cortex-m7/cpu_cache.d \
./rt-thread/libcpu/arm/cortex-m7/cpuport.d 


# Each subdirectory must supply rules for building sources it contributes
rt-thread/libcpu/arm/cortex-m7/%.o: ../rt-thread/libcpu/arm/cortex-m7/%.S
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -x assembler-with-cpp -I"C:\Users\Mja\Documents\EMECS\PoliTO\Operating systems for embedded systems\Project\EOS_project\STM32" -Xassembler -mimplicit-it=thumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
rt-thread/libcpu/arm/cortex-m7/%.o: ../rt-thread/libcpu/arm/cortex-m7/%.c
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DSOC_FAMILY_STM32 -DSOC_SERIES_STM32H7 -DUSE_HAL_DRIVER -DSTM32H747xx -DCORE_CM7 -I"C:\Users\Mja\Documents\EMECS\PoliTO\Operating systems for embedded systems\Project\EOS_project\STM32\drivers" -I"C:\Users\Mja\Documents\EMECS\PoliTO\Operating systems for embedded systems\Project\EOS_project\STM32\drivers\include" -I"C:\Users\Mja\Documents\EMECS\PoliTO\Operating systems for embedded systems\Project\EOS_project\STM32\drivers\include\config" -I"C:\Users\Mja\Documents\EMECS\PoliTO\Operating systems for embedded systems\Project\EOS_project\STM32\libraries\CMSIS\Device\ST\STM32H7xx\Include" -I"C:\Users\Mja\Documents\EMECS\PoliTO\Operating systems for embedded systems\Project\EOS_project\STM32\libraries\CMSIS\Include" -I"C:\Users\Mja\Documents\EMECS\PoliTO\Operating systems for embedded systems\Project\EOS_project\STM32\libraries\CMSIS\RTOS\Template" -I"C:\Users\Mja\Documents\EMECS\PoliTO\Operating systems for embedded systems\Project\EOS_project\STM32\libraries\STM32H7xx_HAL_Driver\Inc" -I"C:\Users\Mja\Documents\EMECS\PoliTO\Operating systems for embedded systems\Project\EOS_project\STM32\libraries\STM32H7xx_HAL_Driver\Inc\Legacy" -I"C:\Users\Mja\Documents\EMECS\PoliTO\Operating systems for embedded systems\Project\EOS_project\STM32" -I"C:\Users\Mja\Documents\EMECS\PoliTO\Operating systems for embedded systems\Project\EOS_project\STM32\applications" -I"C:\Users\Mja\Documents\EMECS\PoliTO\Operating systems for embedded systems\Project\EOS_project\STM32" -I"C:\Users\Mja\Documents\EMECS\PoliTO\Operating systems for embedded systems\Project\EOS_project\STM32\rt-thread\components\drivers\include" -I"C:\Users\Mja\Documents\EMECS\PoliTO\Operating systems for embedded systems\Project\EOS_project\STM32\rt-thread\components\finsh" -I"C:\Users\Mja\Documents\EMECS\PoliTO\Operating systems for embedded systems\Project\EOS_project\STM32\rt-thread\components\libc\compilers\common" -I"C:\Users\Mja\Documents\EMECS\PoliTO\Operating systems for embedded systems\Project\EOS_project\STM32\rt-thread\include" -I"C:\Users\Mja\Documents\EMECS\PoliTO\Operating systems for embedded systems\Project\EOS_project\STM32\rt-thread\libcpu\arm\common" -I"C:\Users\Mja\Documents\EMECS\PoliTO\Operating systems for embedded systems\Project\EOS_project\STM32\rt-thread\libcpu\arm\cortex-m7" -include"C:\Users\Mja\Documents\EMECS\PoliTO\Operating systems for embedded systems\Project\EOS_project\STM32\rtconfig_preinc.h" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

