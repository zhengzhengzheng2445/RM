#include "stm32f4xx.h"
#include "sys.h"
#include "delay.h"
#include "led.h"
#define OUTPIN GPIO_Pin_12
//说明:本作业在充分理解的情况下基于模板修改而来,如果这种做法有问题的话,麻烦学长告知一下

void TIM4_Init(void);
int main(void)
{
    LED_Init(OUTPIN);
	  GPIO_WriteBit(GPIOH,OUTPIN,1);  // 低电平灭,高电亮
   // TIM4_Init();

    while (1)
    {
             // 主循环空着，LED 由中断翻转
    }
}


// 初始化 TIM2，每 500ms 中断一次
void TIM4_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    // TIM2 时钟 72MHz，预分频 7200 → 10kHz
    TIM_TimeBaseStructure.TIM_Period = 9999;              // 10k / (9999+1) = 1Hz → 500ms 中断
    TIM_TimeBaseStructure.TIM_Prescaler = 7199;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM2, ENABLE);
}

// 中断服务函数
void TIM4_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        GPIOC->ODR ^= GPIO_Pin_13;  // 翻转 LED
    }
}
