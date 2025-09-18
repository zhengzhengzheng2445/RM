#include "stm32f4xx.h"
#include "sys.h"
#include "led.h"
#include "timer.h"
#include "IRQHandle.h"
//说明:本作业在充分理解的情况下基于模板大幅修改而来,如果这种做法有问题的话,麻烦请学长告知一下
//参考模板我放在附件文件夹了
int led_toggle=1;
uint16_t outpin=GPIO_Pin_12; //变量定义在所有函数之外就是全局变量；跨文件用时再加 extern 声明即可。
int main(void)
{
    LED_Init(outpin);
	  GPIO_WriteBit(GPIOH,outpin,led_toggle);  // 低电平灭,高电亮
	  int hz=1;
	  TIM4_Init(hz);//这是中断频率1hz,实际上亮一秒灭一秒,每秒闪0.5次
    while (1)
    {
             // 主循环空着，LED 由中断翻转
    }
}


