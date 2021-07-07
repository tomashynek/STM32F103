#include "stm32f103xb.h"

int main(){
	SystemCoreClockUpdate();
	// Enable clock to PortA - USART1 pins, TIM2 pins
	RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;	

    // Enable clock to TIM2
    RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN;

    // Setup TIM2 - into PWM mode, period 20ms, TODO: extreme servo values shall be 1-2ms thus duty cycle 5-10%  
    // TIM2 will be free running no need to care about interrupts or overflows, just CCR shall be updated
    // With 72MHz clock 1 second delay can be achieved by:
    // prescaler PSC = 0xFFF => 4096
    // auto-reload ARR = 72e6/4096 = 17578 = 0x44AA
    // TIM2 -> PSC = 0x0FFFU;
    // TIM2 -> ARR = 0x44AAU;
    // TIM2 -> CR1 |= TIM_CR1_ARPE;
    // TIM2 -> CR1 |= TIM_CR1_CEN;
    

    // TODO:
    // Set period and mid position on PWM - check all works by oscilloscope
    // Test with servo
    // Receive L/R chars over USART to modify PWM and thus servo position 

    // Infinite loop
	while(1){
    }
	return 0;
}
