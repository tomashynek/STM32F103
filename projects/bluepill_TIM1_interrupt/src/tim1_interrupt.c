#include<stdint.h>
#include "stm32f103xb.h"

void delay(uint32_t value);
void delay_timer_1sec(void);

int main(){
	SystemCoreClockUpdate();
	// Enable clock to PortC - Led on pin PC13
	RCC -> APB2ENR |= RCC_APB2ENR_IOPCEN;	
	
    // Enable clock to PortB - output pin on PB11
    RCC -> APB2ENR |= RCC_APB2ENR_IOPBEN;

    // Enable clock to TIM1
    RCC -> APB2ENR |= RCC_APB2ENR_TIM1EN;

	// Set PC13 mode as output with max 50MHz update rate
	// write CNF1,CNF0,MODE1,MODE0 0011 to GPIOC -> CRH bits 23-20 (3UL<<20)
	uint8_t ledPin = 13;
	GPIOC -> CRH |= (3U << GPIO_CRH_MODE13_Pos);
	GPIOC -> CRH &=  ~GPIO_CRH_CNF13_Msk;
    
	// Set PB11 mode as output with max 50MHz update rate
	// write CNF1,CNF0,MODE1,MODE0 0011 to GPIOB -> CRH bits 15-12 (3UL<<12)
    // write 0 to output
	GPIOB -> CRH |= (3U << GPIO_CRH_MODE11_Pos);
	GPIOB -> CRH &= ~GPIO_CRH_CNF11_Msk;
	GPIOB -> ODR &= ~GPIO_ODR_ODR11;

    // Infinite loop
	while(1){
	//	delay(1000000U);
        delay_timer_1sec();
		GPIOC -> ODR ^= (1UL<<ledPin);
        GPIOB -> ODR ^= GPIO_ODR_ODR11;
	}
	return 0;
}

// Simple delay function
void delay(uint32_t value){
	while(value){
		value --;
    }
}

void delay_timer_1sec(void){
    // With 72MHz clock 1 second delay can be achieved by:
    // prescaler PSC = 0xFFF => 4096
    // auto-relode ARR = 72e6/4096 = 17578 = 0x44AA
    TIM1 -> PSC = 0x0FFFU;
    TIM1 -> ARR = 0x44AAU;
    TIM1 -> CR1 |= TIM_CR1_ARPE;
    TIM1 -> CR1 |= TIM_CR1_CEN;
    // wait until counting - check UIF in TIM1->SR, then switch off TIM, clean UIF and return
    while((TIM1 -> SR & TIM_SR_UIF_Msk) == 0){}
    TIM1 -> CR1 &= ~TIM_CR1_CEN_Msk;
    TIM1 -> SR &= ~TIM_SR_UIF_Msk;
}
