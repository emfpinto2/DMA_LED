
#include <xc.h>
#include "my_defs.h"


void Teste_sound(void) {
    for(;;)
        for(uint8_t i=20;i<255;i++) {
            Sound(i, ON);
            Delay_ms(100);
        }
}

void Beep(uint16_t duration) {

    Sound(100, ON);
    Delay_ms(duration);
    Sound(100,OFF);
}


void Beep_loose(void) {
uint8_t i;    
    TMR0_StopTimer();
    for(i=40;i>10;i--) {
        Sound(i,ON);
        Delay_ms(5);
        
    }    
    Sound(40,OFF);
    TMR0_StartTimer();
}


void Sound(uint8_t freq, uint8_t status) {
    PR4=freq;
    //50 more or less 5KHZ
    if (status==ON) 
        PWM1_LoadDutyValue(0x0063); //50%
    else 
        PWM1_LoadDutyValue(0x0000); //0%

 }

void Beep_reset(void) {
    Beep(100);
    Delay_ms(50);
    Beep(100);
}

