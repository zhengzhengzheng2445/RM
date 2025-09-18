#ifndef IRQHANDLE_H
#define IRQHANDLE_H
#include "stm32f4xx.h"
extern int led_toggle;
extern uint16_t outpin;     //不管头文件源文件用了人家封装的东西就得引用
void TIM4_IRQHandler(void);
#endif 