#include "Driver_GPIO.h"

void MyGPIO_Init ( MyGPIO_Struct_TypeDef * GPIOStructPtr ){
	
	
	if (GPIOStructPtr->GPIO_Pin <=7){
		GPIOStructPtr->GPIO -> CRL &= ~(0xF<< (GPIOStructPtr->GPIO_Pin*4));
		GPIOStructPtr->GPIO -> CRL |= GPIOStructPtr->GPIO_Conf << (GPIOStructPtr->GPIO_Pin*4);
		
	}
	else{
		GPIOStructPtr->GPIO -> CRH &= ~(0xF<< (GPIOStructPtr->GPIO_Pin*4-32));
		GPIOStructPtr->GPIO -> CRH |= GPIOStructPtr->GPIO_Conf << (GPIOStructPtr->GPIO_Pin*4-32);
	}
	
	if ( GPIOStructPtr->GPIO_Conf == In_PullDown) {
		GPIOStructPtr->GPIO -> ODR &= ~(1<<(GPIOStructPtr->GPIO_Pin));
	}else if (GPIOStructPtr->GPIO_Conf == In_PullUp) {
		GPIOStructPtr->GPIO -> ODR |= 1<<(GPIOStructPtr->GPIO_Pin);
	}
	
}

int MyGPIO_Read(GPIO_TypeDef * GPIO , char GPIO_Pin ){  //  renvoie 0 ou autre chose different de 0
	uint32_t Etat = (GPIO -> IDR);
	Etat &= 1<<(GPIO_Pin);
	if (Etat != 1<<(GPIO_Pin)) {
		return 0;
	} else {
		return 1;
	}

}
void MyGPIO_Set(GPIO_TypeDef * GPIO , char GPIO_Pin ){
	GPIO -> ODR |= 1<<GPIO_Pin;

}

void MyGPIO_Reset(GPIO_TypeDef * GPIO , char GPIO_Pin ){

	GPIO -> ODR &= ~(1<<GPIO_Pin);
}

void MyGPIO_Toggle(GPIO_TypeDef * GPIO , char GPIO_Pin ){
	
	uint32_t Etat = (GPIO -> ODR);
	Etat &= 1<< GPIO_Pin;
	
	if (Etat != (1<< GPIO_Pin)) {
		MyGPIO_Set(GPIO, GPIO_Pin);
	} else {
		MyGPIO_Reset(GPIO, GPIO_Pin);
	}
	
}

int main(void)
{
	MyGPIO_Struct_TypeDef myGP2;
	MyGPIO_Struct_TypeDef myGP;
	int num;
	myGP.GPIO = GPIOB;
	myGP.GPIO_Conf = Out_Ppull;
	myGP.GPIO_Pin = 3;
	
	MyGPIO_Init ( &myGP );
	

	myGP2.GPIO = GPIOB;
	myGP2.GPIO_Conf = In_Analog;
	myGP2.GPIO_Pin = 4;
	MyGPIO_Init ( &myGP2 );
	MyGPIO_Set(GPIOB , 4 );
	num=MyGPIO_Read(GPIOB ,4);

	
	return 0;
}
