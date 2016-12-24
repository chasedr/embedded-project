#include "stm32f10x.h"

int TimingDelay=0;

void init_GPIO(){
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE,&GPIO_Initstructure);
}

void init_RCC(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	SysTick_Config(72000);
}

void TimingDelay_Decrement(void)
{
    if (TimingDelay != 0x00)
    {
        TimingDelay--;
    }
}

void delay_ms(int t){
	TimingDelay = t;
}

int main(){
	init_RCC();
	init_GPIO();
	while(1)
	{
		//GPIO_WriteBit(GPIOE, GPIO_Pin_2, Bit_SET);
		GPIO_SetBits(GPIOE,GPIO_Pin_2);
		delay_ms(500);
		//GPIO_WriteBit(GPIOE, GPIO_Pin_2, Bit_RESET);
		GPIO_ResetBits(GPIOE,GPIO_Pin_2);
		delay_ms(500);
	}
	return 1;
}

void SysTick_Handler(void)
{
    TimingDelay_Decrement();
}
