#include "stm32f4xx.h"
#include "sys.h"
#include "timer.h"
#include "assert.h"
void TIM4_Reuse_Init(void){
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	  GPIO_InitTypeDef gpio;
    gpio.GPIO_Pin   = GPIO_Pin_14;
    gpio.GPIO_Mode  = GPIO_Mode_AF;        // 复用功能，不是 Out_PP
    gpio.GPIO_Speed = GPIO_Speed_100MHz;
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_Init(GPIOD, &gpio);
	  GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
}
// 初始化 TIM4
void TIM4_Init(int hz)//hz不能取任意数,只能取10000的约数,也不能是0,我不相信我们都是成年人,但我也不想叠甲了
{
	  assert (hz>0&&hz<10001);        //还是浅浅处理一下吧
	  TIM4_Reuse_Init();
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseStructure.TIM_Period = 10000/hz-1;          //若定时器的时钟频率是84MHz就是84M/((PSE+1)*(ARR+1))= f→500ms,周期计算1/(f+1)//具体把这个给ai让他告诉你吧
    TIM_TimeBaseStructure.TIM_Prescaler = 8399;            
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	  TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM4, ENABLE);
}