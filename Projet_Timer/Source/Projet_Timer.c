
#include "stm32f10x.h"
#include "MyTimer.h"

	
int main(void)
{
	
	/*
RCC->APB2ENR |= (0x01<<2) | (0x01<<3) | (0x01<<4) ; //le registre prend la valeur 1110
	// période horloge * prescaler * autoreload = 500ms
	
	RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN; //On active le Timer 

	TIM2 -> ARR = 549; //On modifie ARR et PSC pour avoir une prériode de 500ms
	
	TIM2 -> PSC = 0xFFFF;
	
	TIM2 -> CR1 |= (TIM_CR1_CEN); //On start le timer
	*/
	
	MyTimer_Struct_TypeDef mTIM;
	mTIM.Timer = TIM1;
	mTIM.ARR = 3599;
	mTIM.PSC = 9999;
	
	MyTimer_Base_Init ( &mTIM ) ;
	
	MyTimer_Base_Start(mTIM.Timer);
	
	MyTimer_ActiveIT ( mTIM.Timer ,0);
	
	
	
	while(1) ;
}
