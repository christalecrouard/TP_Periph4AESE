#include "Driver_GPIO.h"

void main() {
	
	
	MyGPIO_Struct_TypeDef LED;
	MyGPIO_Struct_TypeDef Bouton;
	
	LED.GPIO = GPIOC;
	LED.GPIO_Pin = 10;
	
	//setup LED en push-pull
	LED.GPIO_Conf = Out_Ppull;
	
	//En open drain
	LED.GPIO_Conf = Out_OD;
	
	MyGPIO_Init (&LED);
	
	
	Bouton.GPIO = GPIOC;
	Bouton.GPIO_Pin = 8;
	
	//setup bouton en pull-up
	Bouton.GPIO_Conf = In_PullUp;
	MyGPIO_Init (&Bouton);

	
	
	do
	{
		//quand IDR pc8 = 0 on passe la led ODR de pc10 à 1
		/*if (MyGPIO_Read(GPIOC, 8)) {
			MyGPIO_Reset(GPIOC, 10) ;
		}
		else{
			MyGPIO_Set(GPIOC, 10) ;
		}*/
		if (MyGPIO_Read(GPIOC, 8)){
			MyGPIO_Set(GPIOC, 10) ;
		}
		else{
			MyGPIO_Reset(GPIOC, 10) ; //mettre à 1
		}
		
	}
	while(1);
}