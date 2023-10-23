#ifndef MOTOR_H_
#define MOTOR_H_
#include "stm32f10x.h"

#define EN ((1<<8)|(1<<9))
void GPIO_init2()
{
	RCC->APB2ENR|=(1<<2)|(1<<4);

	GPIOA->CRH=0x33333333;
}
void motor_maxspeed_front()
{
	
	GPIOA->ODR|=(1<<11)|(1<<13);
	GPIOA->ODR&=~(1<<10);
	GPIOA->ODR&=~(1<<12);
	GPIOA->ODR|=EN;
}
void motor_maxspeed_back()
{
	GPIOA->ODR|=(1<<10)|(1<<12);
	GPIOA->ODR&=~(1<<11);
	GPIOA->ODR&=~(1<<13);
	GPIOA->ODR|=EN;
}
void motor_left()
{
	GPIOA->ODR|=(1<<11);
	GPIOA->ODR&=~(1<<10);
	GPIOA->ODR&=~(1<<12);
	GPIOA->ODR&=~(1<<13);
	GPIOA->ODR|=EN;
}
void motor_right()
{
	GPIOA->ODR|=(1<<13);
	GPIOA->ODR&=~(1<<10);
	GPIOA->ODR&=~(1<<11);
	GPIOA->ODR&=~(1<<12);
	
	GPIOA->ODR|=EN;
}
void motor_stop()
{
	GPIOA->ODR&=~(1<<10);
	GPIOA->ODR&=~(1<<11);
	GPIOA->ODR&=~(1<<12);
	GPIOA->ODR&=~(1<<13);
}

#endif