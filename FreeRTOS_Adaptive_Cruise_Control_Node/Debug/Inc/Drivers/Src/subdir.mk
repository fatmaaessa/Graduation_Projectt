################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/Drivers/Src/EXTI_program.c \
../Inc/Drivers/Src/GPIO_program.c \
../Inc/Drivers/Src/NVIC_program.c \
../Inc/Drivers/Src/RCC_program.c \
../Inc/Drivers/Src/SPI_program.c \
../Inc/Drivers/Src/TIM_program.c \
../Inc/Drivers/Src/USART_program.c 

OBJS += \
./Inc/Drivers/Src/EXTI_program.o \
./Inc/Drivers/Src/GPIO_program.o \
./Inc/Drivers/Src/NVIC_program.o \
./Inc/Drivers/Src/RCC_program.o \
./Inc/Drivers/Src/SPI_program.o \
./Inc/Drivers/Src/TIM_program.o \
./Inc/Drivers/Src/USART_program.o 

C_DEPS += \
./Inc/Drivers/Src/EXTI_program.d \
./Inc/Drivers/Src/GPIO_program.d \
./Inc/Drivers/Src/NVIC_program.d \
./Inc/Drivers/Src/RCC_program.d \
./Inc/Drivers/Src/SPI_program.d \
./Inc/Drivers/Src/TIM_program.d \
./Inc/Drivers/Src/USART_program.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/Drivers/Src/%.o Inc/Drivers/Src/%.su Inc/Drivers/Src/%.cyclo: ../Inc/Drivers/Src/%.c Inc/Drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Inc-2f-Drivers-2f-Src

clean-Inc-2f-Drivers-2f-Src:
	-$(RM) ./Inc/Drivers/Src/EXTI_program.cyclo ./Inc/Drivers/Src/EXTI_program.d ./Inc/Drivers/Src/EXTI_program.o ./Inc/Drivers/Src/EXTI_program.su ./Inc/Drivers/Src/GPIO_program.cyclo ./Inc/Drivers/Src/GPIO_program.d ./Inc/Drivers/Src/GPIO_program.o ./Inc/Drivers/Src/GPIO_program.su ./Inc/Drivers/Src/NVIC_program.cyclo ./Inc/Drivers/Src/NVIC_program.d ./Inc/Drivers/Src/NVIC_program.o ./Inc/Drivers/Src/NVIC_program.su ./Inc/Drivers/Src/RCC_program.cyclo ./Inc/Drivers/Src/RCC_program.d ./Inc/Drivers/Src/RCC_program.o ./Inc/Drivers/Src/RCC_program.su ./Inc/Drivers/Src/SPI_program.cyclo ./Inc/Drivers/Src/SPI_program.d ./Inc/Drivers/Src/SPI_program.o ./Inc/Drivers/Src/SPI_program.su ./Inc/Drivers/Src/TIM_program.cyclo ./Inc/Drivers/Src/TIM_program.d ./Inc/Drivers/Src/TIM_program.o ./Inc/Drivers/Src/TIM_program.su ./Inc/Drivers/Src/USART_program.cyclo ./Inc/Drivers/Src/USART_program.d ./Inc/Drivers/Src/USART_program.o ./Inc/Drivers/Src/USART_program.su

.PHONY: clean-Inc-2f-Drivers-2f-Src

