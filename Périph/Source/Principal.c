
#include "stm32f10x.h"
	int PosL = 8;
	int PosB = 4*8-32;
	int masque_8 = (1<<8);
int main(void)
{
RCC->APB2ENR |= (0x01<<2) | (0x01<<3) | (0x01<<4) ; //le registre prend la valeur 1110
	
	
	//setup LED
	GPIOC -> CRH &= ~(0xF<<PosL);
	//GPIOC -> CRH |= 0x1<<PosL; //config push-pull
	
	//En open drain
	GPIOC -> CRH |= 0x6<<PosL;
	
	
	//setup bouton
	GPIOC-> CRH &= ~(0xF<<PosB);
	GPIOC -> CRH |= 0x8<<PosB;
	GPIOC -> ODR |= GPIO_ODR_ODR8;

	
	
	do
	{
		//quand IDR pc10 = 0 on passe la led ODR de pc8 à 1
		uint32_t Bouton = (GPIOC -> IDR);
		Bouton &= masque_8;
		/*if (Bouton != masque_8){
			GPIOC -> ODR |= GPIO_ODR_ODR10;
		}
		else{
			GPIOC -> ODR &= ~(GPIO_ODR_ODR10);
		}*/
		if (Bouton != masque_8){
			GPIOC -> ODR &= ~(GPIO_ODR_ODR10);
		}
		else{
			GPIOC -> ODR |= GPIO_ODR_ODR10; //mettre à 1
		}
		
	}
	while(1) ;
}
