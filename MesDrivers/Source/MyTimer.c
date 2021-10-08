#include "MyTimer.h"
#include "stm32f10x.h"
#include "Driver_GPIO.h"


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

static void (* pFnc1) (void) ;
static void (* pFnc2) (void) ;
static void (* pFnc3) (void) ;
static void (* pFnc4) (void) ;

void MyTimer_ActiveIT ( TIM_TypeDef * Timer , char Prio, void(*IT_function )(void)){
		Timer -> DIER |= 1;
	
		if (Timer == TIM1) {
			NVIC -> ISER[0] |= NVIC_ISER_SETENA_25;
			NVIC -> IP[25] |= (Prio<<4);
			pFnc1 = IT_function;
		}
		else if (Timer == TIM2){
			NVIC -> ISER[0] |= NVIC_ISER_SETENA_28;
			NVIC -> IP[28] |= (Prio<<4);
			pFnc2 = IT_function;
		}
		else if (Timer == TIM3){
			NVIC -> ISER[0] |= NVIC_ISER_SETENA_29;
			NVIC -> IP[29] |= (Prio<<4);
			pFnc3 = IT_function;
		}
		else if (Timer == TIM4){
			NVIC -> ISER[0] |= NVIC_ISER_SETENA_30;
			NVIC -> IP[30] |= (Prio<<4);
			pFnc4 = IT_function;
		}
	
		}

/*
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
*/

void TIM1_UP_IRQHandler ( void )
{
	TIM1 -> SR &= ~(TIM_SR_UIF);
if (pFnc1 != 0)
(*pFnc1) (); /* appel indirect de la fonction */
}

void TIM2_IRQHandler ( void )
{
	TIM2 -> SR &= ~(TIM_SR_UIF);
if (pFnc2 != 0)
(*pFnc2) (); /* appel indirect de la fonction */
}

void TIM3_IRQHandler ( void )
{
	TIM3 -> SR &= ~(TIM_SR_UIF);
if (pFnc3 != 0)
(*pFnc3) (); /* appel indirect de la fonction */
}

void TIM4_IRQHandler ( void )
{
	TIM4 -> SR &= ~(TIM_SR_UIF);
if (pFnc4 != 0)
(*pFnc4) (); /* appel indirect de la fonction */
}



void MyTimer_PWM( TIM_TypeDef * Timer , char Channel ) {
	
		// Pin en alternate output
	if (Timer == TIM1) {
		// Le bit MOE du registre TIM1_CR2 doit être mis à 1
		TIM1 -> BDTR |= TIM_BDTR_MOE;
	}
	if (Channel == 1) {
		Timer -> CCMR1 |= TIM_CCMR1_OC1PE;
		Timer -> CCMR1 = TIM_CCMR1_OC1M;
		Timer -> CCMR1 &= ~(TIM_CCMR1_OC1M_0);
	}
	if (Channel == 2) {
		Timer -> CCMR1 |= TIM_CCMR1_OC2PE;
		Timer -> CCMR1 = TIM_CCMR1_OC2M;
		Timer -> CCMR1 &= ~(TIM_CCMR1_OC2M_0);
	}
	if (Channel == 3) {
		Timer -> CCMR2 |= TIM_CCMR2_OC3PE;
		Timer -> CCMR1 = TIM_CCMR2_OC3M;
		Timer -> CCMR1 &= ~(TIM_CCMR2_OC3M_0);
	}
	if (Channel == 4) {
		Timer -> CCMR2 |= TIM_CCMR2_OC4PE;
		Timer -> CCMR1 = TIM_CCMR2_OC4M;
		Timer -> CCMR1 &= ~(TIM_CCMR1_OC1M_0);
	}
	
	Timer -> CR1 |= TIM_CR1_ARPE;
	Timer -> EGR |= TIM_EGR_UG;
	Timer -> CCER |= TIM_CCER_CC1E;
}

void Rapport_Cyclique (TIM_TypeDef * Timer , char Channel, int DutyCycle) { //dutycyle multiplié par 1000
	int CCRx;
	CCRx = DutyCycle * ((Timer->ARR)+1)/10000;
	if (Channel == 1) {
		Timer -> CCR1 |= CCRx;
	}
	if (Channel == 2) {
		Timer -> CCR2 |= CCRx;
	}
	if (Channel == 3) {
		Timer -> CCR3 |= CCRx;
	}
	if (Channel == 4) {
		Timer -> CCR4 |= CCRx;
	}
}
	
	


