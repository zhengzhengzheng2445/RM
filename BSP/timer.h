#ifndef TIMER_H
#define TIMER_H
void TIM4_Reuse_Init(void);
void TIM4_Init(int hz);//hz不能取任意数,只能取10000的约数,也不能是0,我不相信我们都是成年人,但我也不想叠甲了
#endif 