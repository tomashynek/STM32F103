#include<stdint.h>
#include "stm32f103xb.h"

void setup_tim1_1sec(void);

const uint8_t ledPin = 13;

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
	GPIOC -> CRH |= (3U << GPIO_CRH_MODE13_Pos);
	GPIOC -> CRH &=  ~GPIO_CRH_CNF13_Msk;
    
    // Setup TIM1 for 1sec 
    setup_tim1_1sec();
    // Enable Update interupt
    TIM1 -> DIER |= TIM_DIER_UIE;
    // Enable TIM1_UP interrupt in NVIC
    NVIC_EnableIRQ(TIM1_UP_IRQn);
    // Start TIM1
    TIM1 -> CR1 |= TIM_CR1_CEN;

    // Infinite loop
	while(1){
        //Do nothing, all is handled by interrupt service routine
	}
	return 0;
}

void setup_tim1_1sec(void){
    // With 72MHz clock 1 second delay can be achieved by:
    // prescaler PSC  => 7200
    // auto-relode ARR = 72e6/7200 = 10000
    TIM1 -> PSC = 7200;
    TIM1 -> ARR = 10000;
    TIM1 -> CR1 |= TIM_CR1_ARPE;
}

void TIM1_UP_IRQHandler(void){
    // TIM1 update event interrupt
	// Toggle LED
    GPIOC -> ODR ^= (1UL << ledPin);
    // Clear interrupt
    TIM1 -> SR &= ~TIM_SR_UIF;
}
