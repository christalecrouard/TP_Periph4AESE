#include "MyTimer.h"
#include "stm32f10x.h"
#include "Driver_GPIO.h"

void MyTimer_Base_Init ( MyTimer_Struct_TypeDef * Timer ) ;

void MyTimer_Base_Init ( MyTimer_Struct_TypeDef * Timer ){
	if (Timer -> Timer == TIM1)
		RCC -> APB2ENR |= RCC_APB2ENR_TIM1EN;
	if (Timer -> Timer == TIM2)
		RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN;
	if (Timer -> Timer == TIM3)
		RCC -> APB1ENR |= RCC_APB1ENR_TIM3EN;
	if (Timer -> Timer == TIM4) {
		RCC -> APB1ENR |= RCC_APB1ENR_TIM4EN;
	}
	
	Timer -> Timer -> ARR = Timer->ARR;
	
	Timer-> Timer -> PSC =Timer->PSC ;
	
	
}

/*
void MyTimer_ActiveIT ( TIM_TypeDef * Timer , char Prio ){
		Timer -> DIER |= 1;
	
		if (Timer == TIM1) {
			NVIC -> ISER[0] |= NVIC_ISER_SETENA_25;
			NVIC -> IP[25] |= (Prio<<4);
		}
		else if (Timer == TIM2){
			NVIC -> ISER[0] |= NVIC_ISER_SETENA_28;
			NVIC -> IP[28] |= (Prio<<4);
		}
		else if (Timer == TIM3){
			NVIC -> ISER[0] |= NVIC_ISER_SETENA_29;
			NVIC -> IP[29] |= (Prio<<4);
		}
		else if (Timer == TIM4){
			NVIC -> ISER[0] |= NVIC_ISER_SETENA_30;
			NVIC -> IP[30] |= (Prio<<4);
		}
	
}
*/

void MyTimer_ActiveIT ( TIM_TypeDef * Timer , char Prio, void(*IT_function )(void)){
		Timer -> DIER |= 1;
	
		if (Timer == TIM1) {
			NVIC -> ISER[0] |= NVIC_ISER_SETENA_25;
			NVIC -> IP[25] |= (Prio<<4);
		}
		else if (Timer == TIM2){
			NVIC -> ISER[0] |= NVIC_ISER_SETENA_28;
			NVIC -> IP[28] |= (Prio<<4);
		}
		else if (Timer == TIM3){
			NVIC -> ISER[0] |= NVIC_ISER_SETENA_29;
			NVIC -> IP[29] |= (Prio<<4);
		}
		else if (Timer == TIM4){
			NVIC -> ISER[0] |= NVIC_ISER_SETENA_30;
			NVIC -> IP[30] |= (Prio<<4);
		}
	
}

void TIM1_UP_IRQHandler ( void )
{
		TIM1 -> SR &= ~(TIM_SR_UIF);
		MyGPIO_Toggle(GPIOC , 5 );
}

void TIM2_IRQHandler ( void )
{
		TIM2 -> SR &= ~(TIM_SR_UIF);
		MyGPIO_Toggle(GPIOC , 5 );
}

void TIM3_IRQHandler ( void )
{
		TIM3 -> SR &= ~(TIM_SR_UIF);
		MyGPIO_Toggle(GPIOC , 5 );
}

void TIM4_IRQHandler ( void )
{
		TIM4 -> SR &= ~(TIM_SR_UIF);
		MyGPIO_Toggle(GPIOC , 5 );
}


