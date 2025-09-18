#include "stm32f4xx.h"
#include "sys.h"
#include "led.h"
void LED_Init(uint32_t pin) //初始化GPIOH的那几个led够了
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH,ENABLE);
    GPIO_InitStructure.GPIO_Pin=pin;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed=GPIO_Fast_Speed;
		GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOH, &GPIO_InitStructure);
}