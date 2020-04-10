#include "stm32f103xb.h"

int main(){
	SystemCoreClockUpdate();
    // TODO: setup serial for transmission
    // TODO: in while loop repeat over and over

    const char msg[] = "Hello World!\n";     
    
    // Enable clock to PortA (TX and RX pins of USART1)
    RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
    // TBC: may be necessary to enable clock to AFIO (TX1 must be set to AF configuration, but I do not need remapping)
    // Enable clock to USART1
    RCC -> APB2ENR |= RCC_APB2ENR_USART1EN;

    // Set pin PA9 (TX1) to AF Push-pull (see Reference manual page 166)
    // GPIOA -> CRH |= ; CNF1 CNF0 Mode1 Mode0 1011 at pin9  

    // Infinite loop
	while(1){
	}
	return 0;
}
