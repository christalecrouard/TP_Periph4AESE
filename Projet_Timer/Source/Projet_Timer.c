
#include "stm32f10x.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"

static MyGPIO_Struct_TypeDef myGPIO;
	

void Callback () {
	MyGPIO_Toggle(myGPIO.GPIO , myGPIO.GPIO_Pin);
	
}
	
int main(void)
{
	/*
	MyTimer_Struct_TypeDef mTIM;
	mTIM.Timer = TIM2;
	mTIM.ARR = 3599; // Pour une période de 500ms
	mTIM.PSC = 9999;
	
*/
	/*
	myGPIO.GPIO_Conf = Out_Ppull;
	myGPIO.GPIO_Pin = 5;
	myGPIO.GPIO = GPIOB;
	*/
	

		
	/*
RCC->APB2ENR |= (0x01<<2) | (0x01<<3) | (0x01<<4) ; //le registre prend la valeur 1110
	// période horloge * prescaler * autoreload = 500ms
	
	RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN; //On active le Timer 

	TIM2 -> ARR = 549; //On modifie ARR et PSC pour avoir une prériode de 500ms
	
	TIM2 -> PSC = 0xFFFF;
	
	TIM2 -> CR1 |= (TIM_CR1_CEN); //On start le timer
	*/
	
	
	MyTimer_Struct_TypeDef mTIM; //Question PWM
	mTIM.Timer = TIM2;
	mTIM.ARR = 720-1; // Pour une fréquence de 100kHz avec période horloge = 72MHz //une valeur plus élevée permet une précision plus grande
	mTIM.PSC = 1-1;
	
	MyTimer_Base_Init ( &mTIM ) ;
	
	
	//MyTimer_ActiveIT ( mTIM.Timer ,1, Callback);
	
	myGPIO.GPIO_Conf = AltOut_Ppull;
	myGPIO.GPIO = GPIOA;
	myGPIO.GPIO_Pin = 0;
	MyGPIO_Init ( &myGPIO );
	
	/* Différentes config en fonction du channel et timer
	if (Timer == TIM1) {
		if (Channel == 1) {
			MyGPIO.GPIO = GPIOA;
			MyGPIO.GPIO_Pin = 8;
		}
		if (Channel == 2) {
			MyGPIO.GPIO = GPIOA;
			MyGPIO.GPIO_Pin = 9;
		}
		if (Channel == 3) {
			MyGPIO.GPIO = GPIOA;
			MyGPIO.GPIO_Pin = 10;
		}
		if (Channel == 4) {
			MyGPIO.GPIO = GPIOA;
			MyGPIO.GPIO_Pin = 11;
		}
	}
	
	else if (Timer == TIM2){
		if (Channel == 1) {
			MyGPIO.GPIO = GPIOA;
			MyGPIO.GPIO_Pin = 0;
		}
		if (Channel == 2) {
			MyGPIO.GPIO = GPIOA;
			MyGPIO.GPIO_Pin = 1;
		}
		if (Channel == 3) {
			MyGPIO.GPIO = GPIOA;
			MyGPIO.GPIO_Pin = 2;
		}
		if (Channel == 4) {
			MyGPIO.GPIO = GPIOA;
			MyGPIO.GPIO_Pin = 3;
		}
	}
	
	else if (Timer == TIM3){
		if (Channel == 1) {
			MyGPIO.GPIO = GPIOA;
			MyGPIO.GPIO_Pin = 6;
		}
		if (Channel == 2) {
			MyGPIO.GPIO = GPIOA;
			MyGPIO.GPIO_Pin = 7;
		}
		if (Channel == 3) {
			MyGPIO.GPIO = GPIOB;
			MyGPIO.GPIO_Pin = 0;
		}
		if (Channel == 4) {
				MyGPIO.GPIO = GPIOB;
				MyGPIO.GPIO_Pin = 1;
			}

	}
	
	else if (Timer == TIM4){	
		if (Channel == 1) {
			MyGPIO.GPIO = GPIOB;
			MyGPIO.GPIO_Pin = 6;
		}
		if (Channel == 2) {
			MyGPIO.GPIO = GPIOB;
			MyGPIO.GPIO_Pin = 7;
		}
		if (Channel == 3) {
			MyGPIO.GPIO = GPIOB;
			MyGPIO.GPIO_Pin = 8;

		}
		if (Channel == 4) {
			MyGPIO.GPIO = GPIOB;
			MyGPIO.GPIO_Pin = 9;

		}
	} 
	*/

	MyTimer_PWM( mTIM.Timer , 1 ) ;
	Rapport_Cyclique (mTIM.Timer , 1,2000 );
	
	MyTimer_Base_Start(mTIM.Timer);
	
	while(1) ;
}
