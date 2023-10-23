#ifndef SERVO_H_
#define SERVO_H_
#include "stm32f10x.h"

void TIM_init1(void);
void GPIO_init1(void);
void timer_delay1(int);

void timer_delay1(int value)
{
	
	for(int i=0;i<value;i++)
	{
		TIM2->CNT=0;
		while((TIM2->CNT)<1);
	}
	
}
void TIM_init1()
{
	RCC->APB1ENR|=0x01;
	TIM2->ARR=10000-1;//auto reload register
	TIM2->PSC=72-1;// prescaler value
	TIM2->PSC=20-1;
	TIM2->CCMR1=0x6060;//PWM
	TIM2->CCMR2=0x6060;//PWM 
	TIM2->CCR1=5500;
	
	TIM2->CCR3=550;
	TIM2->CCR4=3000;
	TIM2->CCER=0x1111;//enable capture/compare mode register
	TIM2->CR1=0x01;//enable counter
	TIM2->EGR=0x01;
	
	
}
void GPIO_init1()
{
	RCC->APB2ENR|=(1<<2)|(1<<4);
	GPIOA->CRL=0x33BBBB;

}
void servo_0()
{
	TIM2->CCR2=2000;
}
void servo_180()
{
	TIM2->CCR2=9000;
}
void servo_90()
{
	TIM2->CCR2=5000;
}
#endif