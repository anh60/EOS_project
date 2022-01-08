################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/board.c \
../drivers/drv_adc.c \
../drivers/drv_clk.c \
../drivers/drv_common.c \
../drivers/drv_eth.c \
../drivers/drv_gpio.c \
../drivers/drv_hwtimer.c \
../drivers/drv_pwm.c \
../drivers/drv_qspi.c \
../drivers/drv_rtc.c \
../drivers/drv_sdio.c \
../drivers/drv_soft_i2c.c \
../drivers/drv_spi.c \
../drivers/drv_usart.c \
../drivers/drv_usbd.c \
../drivers/drv_usbh.c \
../drivers/drv_wdt.c 

OBJS += \
./drivers/board.o \
./drivers/drv_adc.o \
./drivers/drv_clk.o \
./drivers/drv_common.o \
./drivers/drv_eth.o \
./drivers/drv_gpio.o \
./drivers/drv_hwtimer.o \
./drivers/drv_pwm.o \
./drivers/drv_qspi.o \
./drivers/drv_rtc.o \
./drivers/drv_sdio.o \
./drivers/drv_soft_i2c.o \
./drivers/drv_spi.o \
./drivers/drv_usart.o \
./drivers/drv_usbd.o \
./drivers/drv_usbh.o \
./drivers/drv_wdt.o 

C_DEPS += \
./drivers/board.d \
./drivers/drv_adc.d \
./drivers/drv_clk.d \
./drivers/drv_common.d \
./drivers/drv_eth.d \
./drivers/drv_gpio.d \
./drivers/drv_hwtimer.d \
./drivers/drv_pwm.d \
./drivers/drv_qspi.d \
./drivers/drv_rtc.d \
./drivers/drv_sdio.d \
./drivers/drv_soft_i2c.d \
./drivers/drv_spi.d \
./drivers/drv_usart.d \
./drivers/drv_usbd.d \
./drivers/drv_usbh.d \
./drivers/drv_wdt.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DSOC_FAMILY_STM32 -DSOC_SERIES_STM32H7 -DUSE_HAL_DRIVER -DSTM32H747xx -DCORE_CM7 -I"C:\Users\Mja\Documents\EMECS\PoliTO\Operating systems for embedded systems\Project\EOS_project\STM32\drivers" -I"C:\Users\Mja\Documents\EMECS\PoliTO\Operating systems for embedded systems\Project\EOS_project\STM32\drivers\include" -I"C:\Users\Mja\Documents\EMECS\PoliTO\Operating systems for embedded systems\Project\EOS_project\STM32\drivers\include\config" -I"C:\Users\Mja\Documents\EMECS\PoliTO\Operating systems for embedded systems\Project\EOS_project\STM32\libraries\CMSIS\Device\ST\STM32H7xx\Include" -I"C:\Users\Mja\Documents\EMECS\PoliTO\Operating systems for embedded systems\Project\EOS_project\STM32\libraries\CMSIS\Include" -I"C:\Users\Mja\Documents\EMECS\PoliTO\Operating systems for embedded systems\Project\EOS_project\STM32\libraries\CMSIS\RTOS\Template" -I"C:\Users\Mja\Documents\EMECS\PoliTO\Operating systems for embedded systems\Project\EOS_project\STM32\libraries\STM32H7xx_HAL_Driver\Inc" -I"C:\Users\Mja\Documents\EMECS\PoliTO\Operating systems for embedded systems\Project\EOS_project\STM32\libraries\STM32H7xx_HAL_Driver\Inc\Legacy" -I"C:\Users\Mja\Documents\EMECS\PoliTO\Operating systems for embedded systems\Project\EOS_project\STM32" -I"C:\Users\Mja\Documents\EMECS\PoliTO\Operating systems for embedded systems\Project\EOS_project\STM32\applications" -I"C:\Users\Mja\Documents\EMECS\PoliTO\Operating systems for embedded systems\Project\EOS_project\STM32" -I"C:\Users\Mja\Documents\EMECS\PoliTO\Operating systems for embedded systems\Project\EOS_project\STM32\rt-thread\components\drivers\include" -I"C:\Users\Mja\Documents\EMECS\PoliTO\Operating systems for embedded systems\Project\EOS_project\STM32\rt-thread\components\finsh" -I"C:\Users\Mja\Documents\EMECS\PoliTO\Operating systems for embedded systems\Project\EOS_project\STM32\rt-thread\components\libc\compilers\common" -I"C:\Users\Mja\Documents\EMECS\PoliTO\Operating systems for embedded systems\Project\EOS_project\STM32\rt-thread\include" -I"C:\Users\Mja\Documents\EMECS\PoliTO\Operating systems for embedded systems\Project\EOS_project\STM32\rt-thread\libcpu\arm\common" -I"C:\Users\Mja\Documents\EMECS\PoliTO\Operating systems for embedded systems\Project\EOS_project\STM32\rt-thread\libcpu\arm\cortex-m7" -include"C:\Users\Mja\Documents\EMECS\PoliTO\Operating systems for embedded systems\Project\EOS_project\STM32\rtconfig_preinc.h" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

