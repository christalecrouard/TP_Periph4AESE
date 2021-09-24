#include "Driver_GPIO.h"

void MyGPIO_Init ( MyGPIO_Struct_TypeDef * GPIOStructPtr ){
	
	char Config = GPIOStructPtr->GPIO_Conf;
	
	RCC->APB2ENR |= (0x01<<2) | (0x01<<3) | (0x01<<4) ; //le registre prend la valeur 1110
	
	if (Config == In_PullUp) {
		GPIOStructPtr->GPIO -> ODR |= 1<<(GPIOStructPtr->GPIO_Pin);
		Config = In_PullDown;
	}
	
	if (GPIOStructPtr->GPIO_Pin <=7){ // Si le pin est entre 0 et 7, on doit modifier le registre CRL
		GPIOStructPtr->GPIO -> CRL &= ~(0xF<< (GPIOStructPtr->GPIO_Pin*4)); //On réinitialise les 4 bits dédiés au pin
		GPIOStructPtr->GPIO -> CRL |= Config << (GPIOStructPtr->GPIO_Pin*4); //Puis on remplace par la config qui nous intéresse
		
	}
	else{
		GPIOStructPtr->GPIO -> CRH &= ~(0xF<< (GPIOStructPtr->GPIO_Pin*4-32));
		GPIOStructPtr->GPIO -> CRH |= Config << (GPIOStructPtr->GPIO_Pin*4-32);
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

/*int main(void)
{
		
	MyGPIO_Struct_TypeDef myGP2;
	MyGPIO_Struct_TypeDef myGP;
	
	RCC->APB2ENR |= (0x01<<2) | (0x01<<3) | (0x01<<4) ; //le registre prend la valeur 1110
	
	myGP.GPIO = GPIOA;
	myGP.GPIO_Conf = AltOut_OD;
	myGP.GPIO_Pin = 2;
	
	MyGPIO_Init ( &myGP );
	

	myGP2.GPIO = GPIOA;
	myGP2.GPIO_Conf = In_Analog;
	myGP2.GPIO_Pin = 15;
	MyGPIO_Init ( &myGP2 );
	
	
	MyGPIO_Set(GPIOB , 3);
	
	MyGPIO_Read(GPIOB ,4);
	
	MyGPIO_Toggle(GPIOB, 3);
	
	MyGPIO_Toggle(GPIOB, 3);

	
} */
