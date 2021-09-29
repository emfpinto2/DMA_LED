/**
  Acesso por DMA a uma matriz de leds com as dimensões LED_COUNT_X e LED_COUNT_y  
 * 
 *TMR0 - 10ms - Callback da função LED_update 
 *    - Incrementa a variave cents_since_start
 *    - Faz refresh da matriz de leds iniciando um processo DMA de acordo com a constante
 *      PixelArray[TOTAL_LEDS][3] -> SPI(&PWM5) -> CLC2 -> Pin RC3
 * .
*/

#include "mcc_generated_files/mcc.h"
#include "my_defs.h"
#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "mcc_generated_files/spi1.h"

extern volatile uint8_t new_message_in_rx1_buffer;
extern volatile uint8_t new_message_in_rx2_buffer;
extern volatile uint8_t uart1RxBuffer[UART1_RX_BUFFER_SIZE];
extern volatile uint8_t uart2RxBuffer[UART2_RX_BUFFER_SIZE];

uint8_t PixelBase[3]={0,0,0};
uint8_t Game_array[LED_COUNT_Y][LED_COUNT_X][3];
uint8_t Video_array[LED_COUNT_Y][LED_COUNT_X][3];



uint32_t cents_since_start=0L;
uint32_t last_time_refresh_matrix=0L;


void (*putch_uartfunction_ptr)(uint8_t)=UART1_Write; //Apontador para função UARTx_Write pretendida. 
//Tem que se colocar a função(endereço) pretendido antes de se chamar o printf)



void putch(char txData)
{
    putch_uartfunction_ptr(txData);
    
}


inline void Matrix_refresh(void ) {
    
    DMA1CON0bits.DMA1SIRQEN = 1;  //Trigger the DMA Transfer
    //while(DMA1CON0bits.DGO);
}        



void Matrix_fill_RGB(uint8_t red, uint8_t green, uint8_t blue) {
uint8_t x,y;
    
    TMR0_StopTimer();
    for (y=0; y<LED_COUNT_Y; y++) {
        for (x=0; x<LED_COUNT_X; x++) {
            Game_array[y][x][RED]=red;//(uint8_t)(0x1+i*3);
            Game_array[y][x][GREEN]=green;//(uint8_t)(0x2+i*3);
            Game_array[y][x][BLUE]=blue;//(uint8_t)(0x3+i*3);
        }    
    }
    TMR0_StartTimer();
}







    
#define DELAY_TFD    20

void Teste_fill_using_DMA1(void) {
uint8_t i;
    /* Trigger the SPI to start DMA */
//    SPI1INTFbits.SPI1TXUIF = 1;
//    __delay_ms(100);

    for(;;) {
        for(i=0;i<MAX_INTENSITY_RED;i++) {
            Matrix_fill_RGB(i,0x00,0x00);
            Delay_ms(DELAY_TFD);
        }    
        for(i=MAX_INTENSITY_RED;i;i--) {
            Matrix_fill_RGB(i,0x00,0x00);
            Delay_ms(DELAY_TFD);
        }    
        
        
        for(i=0;i<MAX_INTENSITY_GREEN;i++) {
            Matrix_fill_RGB(0,i,0x00);
            Delay_ms(DELAY_TFD);
        }    
        for(i=MAX_INTENSITY_GREEN;i;i--) {
            Matrix_fill_RGB(0,i,0x00);
            Delay_ms(DELAY_TFD);
        }    
        
        for(i=0;i<MAX_INTENSITY_BLUE;i++) {
            Matrix_fill_RGB(0,0,i);
            Delay_ms(DELAY_TFD);
        }    
        for(i=MAX_INTENSITY_BLUE;i;i--) {
            Matrix_fill_RGB(0,0,i);
            Delay_ms(DELAY_TFD);
        }    
        
    }
}





void main(void) {
  uint16_t i=0;
  
    // Initialize the device
    SYSTEM_Initialize();
    my_SPI1_Initialize(); // Parece que o MCC no Easy Setup n funciona bem! Fiz as minhas rotinas no ficheiro my_spi.c
    my_DMA1_Initialize();
    my_DMA2_Initialize();

    Beep_reset();
    
    led_initialize();
    
    TMR0_SetInterruptHandler(led_update);

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts
    // Use the following macros to:

    // Enable high priority global interrupts
    INTERRUPT_GlobalInterruptHighEnable();

    // Enable low priority global interrupts.
    INTERRUPT_GlobalInterruptLowEnable();

    // Disable high priority global interrupts
    //INTERRUPT_GlobalInterruptHighDisable();

    // Disable low priority global interrupts.
    //INTERRUPT_GlobalInterruptLowDisable();
    


    //Teste_fill_using_DMA1(); //Teste Fade in e fade out RGB
    Game_play();
    
    for(;;) {
        putch_uartfunction_ptr=UART1_Write;
        printf("%05d -Siemens UART1 (USB-Serial)\r\n",i);
        //check_for_new_msg_UART1(); //- Não funciona porque o buffer de hardware são só dois bytes. É preciso usar interrupções
        
        putch_uartfunction_ptr=UART2_Write;
        printf("%05d -Siemens UART2 (Bluetooth)\r\n",i++);     
        //check_for_new_msg_UART2();  //- Não funciona porque o buffer de hardware são só dois bytes. É preciso usar interrupções
        
        for(uint16_t i=0;i<1000;i++) {
            if  (new_message_in_rx1_buffer) {
                new_message_in_rx1_buffer=0;
                putch_uartfunction_ptr=UART1_Write;
                printf("NEW MESSAGE RECEIVED: %s",&uart1RxBuffer[1]);
            }   
            if  (new_message_in_rx2_buffer) {
                new_message_in_rx2_buffer=0;
                 putch_uartfunction_ptr=UART2_Write;
                printf("NEW MESSAGE RECEIVED: %s",&uart2RxBuffer[1]);
            }   
            __delay_ms(1);
        }
    }
} 
  
/**
 End of File
*/