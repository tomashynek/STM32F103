#include "stm32f103xb.h"

int main(){
	SystemCoreClockUpdate();

    // Enable clock to PortA (TX and RX pins of USART1)
    RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
    // Enable clock to USART1
    //RCC -> APB2ENR |= RCC_APB2ENR_USART1EN;
    // Enable clock to ADC1
    RCC -> APB2ENR |= RCC_APB2ENR_ADC1EN;

    // Set pin PA9 (TX1) to AF Push-pull (see Reference manual page 166)
    // CNF1 CNF0 Mode1 Mode0  = 1011 = 0xB at pin9
    // Read -> Clear CNF and MODE for Pin9 -> Set 0xB -> Write
    //GPIOA -> CRH = ((GPIOA -> CRH & ~(GPIO_CRH_CNF9_Msk | GPIO_CRH_MODE9_Msk)) | (0xB << GPIO_CRH_MODE9_Pos));
    
    // Initialise USART1 for transmission
    // Enable USART1
    //USART1 -> CR1 |= USART_CR1_UE; 
    // Set M to 0 - 1 start 8 data n stop bits
    //USART1 -> CR1 & ~USART_CR1_M;
    // Set Stop to 00 - 1 stop bit
    //USART1 -> CR2 & ~USART_CR2_STOP;
    // Set Baud rate to 9600 - 72e6 / (16*468.75) -> Mantissa 468, Fraction 0.75 -> 0xC
    //USART1 -> BRR = ((468 << USART_BRR_DIV_Mantissa_Pos) | 0xC);
    // Set TE to 1
    //USART1 -> CR1 |= USART_CR1_TE;

    // Initialise ADC1 for conversion of internal channels (reference voltage or temperature sensor)
    ADC1 -> CR2 |= ADC_CR2_ADON; // Turn ADC1 ON
    ADC1 -> CR2 |= ADC_CR2_TSVREFE; // Enable internal channels
    ADC1 -> CR2 &= ~ADC_CR2_ALIGN; // Right alignment of the results
    ADC1 -> CR2 &= ~ADC_CR2_CONT; // Single mode
    ADC1 -> SQR3 = (ADC1 -> SQR3 & ~ADC_SQR3_SQ1_Msk) | (17U << ADC_SQR3_SQ1_Pos); // Channel 17 (V_REF) as 1st input in sequence
    ADC1 -> SQR1 = (ADC1 -> SQR1 & ~ADC_SQR1_L_Msk) | (0U << ADC_SQR1_L_Pos); // Set number of channels in sequence to 1 (=0000)
    ADC1 -> SMPR1 = (ADC1 -> SMPR1 & ~ADC_SMPR1_SMP17_Msk) | (7U << ADC_SMPR1_SMP17_Pos); // Set sampling time of channel 17 to 239.5 cycle (~ 21us @ 12MHz)
    // Calibration
    ADC1 -> CR2 |= ADC_CR2_CAL; // Start calibration
    while((ADC1 -> CR2 & ADC_CR2_CAL_Msk) != 0){} // Wait until CAL is cleared by HW


    // Infinite loop
    int result = 0;
	while(1){
        // Trigger measurement and wait for the results
        ADC1 -> CR2 |= ADC_CR2_ADON; // Trigger measurement
        while((ADC1 -> SR & ADC_SR_EOS_Msk) == 0){} // Wait till the end of conversion
        result = ADC1 -> DR; // Store result from DR

        // Send result over USART1
        // loop over message
//        for(int i = 0; i < length; i++){
            // wait until finished
//            while((USART1 -> SR & USART_SR_TC_Msk) == 0) {}
            // send character
//            USART1 -> DR = msg[i];
//        }
	}
	return 0;
}
