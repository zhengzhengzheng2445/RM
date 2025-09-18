#include "stm32f4xx.h"
#include "sys.h"
#include "IRQHandle.h"
// 中断服务函数
void TIM4_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
			  led_toggle=!led_toggle;
			  GPIO_WriteBit(GPIOH,outpin,led_toggle);   // 翻转 LED,用寄存器是不可能用的
    }
}
