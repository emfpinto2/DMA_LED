#include "mcc_generated_files/mcc.h"
#include "my_defs.h"


//XC8 inline __delay_ms function only allows for maximum delay of about 4s at 64MHz ...
void Delay_ms(uint16_t ms) {
 uint16_t i;
 
    for(i=0;i<ms;i++)
        __delay_ms(1);
}

void Delay_us(uint16_t us) {
 uint16_t i;
 
    for(i=0;i<us;i++)
        __delay_us(1);
}

