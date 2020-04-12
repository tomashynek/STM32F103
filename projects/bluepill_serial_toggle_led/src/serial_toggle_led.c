#include "stm32f103xb.h"

int main(){
	SystemCoreClockUpdate();

    // Enable clock to PortA (TX and RX pins of USART1)
    RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
    // Enable clock to PortC (LED)
    RCC -> APB2ENR |= RCC_APB2ENR_IOPCEN;
    // Enable clock to USART1
    RCC -> APB2ENR |= RCC_APB2ENR_USART1EN;

    // Set pin PA10 (RX1) to Input floating (see Reference manual page 166)
    // CNF1 CNF0 Mode1 Mode0  = 0100 = 0x4 at pin10
    // Read -> Clear CNF and MODE for Pin10 -> Set 0x -> Write
    GPIOA -> CRH = ((GPIOA -> CRH & ~(GPIO_CRH_CNF10_Msk | GPIO_CRH_MODE10_Msk)) | (0x4 << GPIO_CRH_MODE10_Pos));

    // Set pin PC13 (LED) to 
    // CNF1 CNF0 Mode1 Mode0 = 0011 = 0x3 at pin13
    const int ledPin = 13;
    GPIOC -> CRH = ((GPIOC -> CRH & ~(GPIO_CRH_CNF13_Msk | GPIO_CRH_MODE13_Msk)) | (0x3 << GPIO_CRH_MODE13_Pos));
    GPIOC -> ODR ^= (1UL<<ledPin);
 
    // Initialise USART1 for transmission
    // Enable USART1
    USART1 -> CR1 |= USART_CR1_UE; 
    // Set M to 0 - 1 start 8 data n stop bits
    USART1 -> CR1 & ~USART_CR1_M;
    // Set Stop to 00 - 1 stop bit
    USART1 -> CR2 & ~USART_CR2_STOP;
    // Set Baud rate to 9600 - 72e6 / (16*468.75) -> Mantissa 468, Fraction 0.75 -> 0xC
    USART1 -> BRR = ((468 << USART_BRR_DIV_Mantissa_Pos) | 0xC);
    // Set RE to 1
    USART1 -> CR1 |= USART_CR1_RE;

    // Infinite loop
	while(1){
            // Wait until something is received RXNE set to 1
            while((USART1 -> SR & USART_SR_RXNE_Msk) == 0) {}
            // Check if it is 't' 
            if(USART1 -> DR == 't'){
                // Toggle LED
                GPIOC -> ODR ^= (1UL<<ledPin);
            }
	}
	return 0;
}
