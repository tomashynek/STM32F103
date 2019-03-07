#include<stdint.h>
#include "stm32f103xb.h"

void delay(uint32_t value);

int main(){
	SystemCoreClockUpdate();
	// Enable clock to PortC
	RCC -> APB2ENR |= RCC_APB2ENR_IOPCEN_Msk;	
	
	// Set PC13 mode as output with max 50MHz update rate
	// write CNF1,CNF0,MODE1,MODE0 0011 to GPIOC -> CRH bits 23-20 (3UL<<20)
	uint8_t ledPin = 13;
	GPIOC -> CRH |= (3UL<<20);
	//GPIOC -> ODR |= (1UL<<ledPin);
	
	while(1){
		delay(1000000);
		GPIOC -> ODR ^= (1UL<<ledPin);
	}
	return 0;
}

// Simple delay function
void delay(uint32_t value){
	while(value){
		value --;
	}
}
