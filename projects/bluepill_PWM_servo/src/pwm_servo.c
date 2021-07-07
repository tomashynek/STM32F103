#include "stm32f103xb.h"

int main(){
	SystemCoreClockUpdate();
	// Enable clock to PortA - USART1 pins, TIM2 pins
	RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;	

    // Enable clock to TIM2
    RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN;

    // Setup TIM2 - into PWM mode, period 20ms, TODO: extreme servo values shall be 1-2ms thus duty cycle 5-10%  
    // TIM2 will be free running no need to care about interrupts or overflows, just CCR shall be updated
    // With 36MHz clock:
    // Servo angle range is approx 180deg, max - min pwm range is about 1ms, thus would be nice to have 180 ticks per 1 ms
    // This thus gives 180kHz counter input frequency
    // Prescaler set to 199 makes 36MHz/(199+1) = 180kHz
    // Auto reload set to 3600 ticks means 20 ms
    // Min position ~ 1ms = 180 ticks
    // Max position ~ 2ms = 360 ticks
    TIM2 -> PSC = 199;
    TIM2 -> ARR = 3599;
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
