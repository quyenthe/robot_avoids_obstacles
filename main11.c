#include "stm32f10x.h"
#include "servo.h"
#include "motor.h"
#include <stdio.h>
#define TRIG (0x03300000)
#define ECHO (0x40000000)
void GPIO_init();
void TIM_init();
void delay_us(unsigned int );
int hc_sr04();
float distance();
void avoid_obstacles_1();
void avoid_obstacles_2();
int main()
{
	GPIO_init();
	TIM_init();
  GPIO_init1();
	TIM_init1();
	GPIO_init2();

	while(1)
	{
		
		avoid_obstacles_1();
	
		
	}
}
void GPIO_init()
{
	RCC->APB2ENR|=(1<<4);

	GPIOC->CRH|=TRIG;
	GPIOC->CRH|=ECHO;

}
void TIM_init()
{
	RCC->APB1ENR|=(1<<1);
	TIM3->ARR=0xFFFF;
	TIM3->PSC=72-1;
	TIM3->CR1=0x01;
	TIM3->EGR=0x01;
}
void delay_us(unsigned int delay)
{
	for(int i=0;i<delay;i++)
	{
		TIM3->CNT=0;
		while((TIM3->CNT)<1);
	}
}

int hc_sr04()
{
	unsigned int time;
	volatile unsigned int delay1=0,delay2=0;
	GPIOC->ODR&=~(1<<14);
	delay_us(2);
	GPIOC->ODR|=(1<<14);
	delay_us(12);
	GPIOC->ODR&=~(1<<14);
	while(!(GPIOC->IDR&(1<<15)))
	{
		delay1++;
		delay_us(1);
	}
	
	while((GPIOC->IDR&(1<<15)))
	{
		delay2++;
		delay_us(1);
	}
	
	return (delay2-delay1);
}
float distance()
{
	char a[10];
	int time=hc_sr04();
	sprintf(a,"%0.2f",(float)time*0.17);
	
	float d=(float)time*0.17;
	
	
	return d;
}
void avoid_obstacles_2()
{
	float d1,d2;
	motor_stop();
	servo_0();
	delay_us(1500000);
	d1=distance();
	servo_180();
	delay_us(1500000);
	d2=distance();
	servo_90();
	delay_us(1000000);
	if(d1<d2 && d2>20)
	{
		motor_right();
		delay_us(500000);
	}
	else if (d1>d2 &&  d1>20)
	{
		motor_left();
		delay_us(500000);
	}
	else if(d1<20 && d2<20)
	{
		motor_maxspeed_back();
		delay_us(2000000);
		return avoid_obstacles_2();
	}
	
}
void avoid_obstacles_1()
{
	float d;
	d=distance();
	
	if(d < 20)
	{
		avoid_obstacles_2();
	}
	else
		motor_maxspeed_front();
}
