
#include "mcc_generated_files/mcc.h"
#include <stdint.h>
#include "my_defs.h"


extern uint32_t cents_since_start;
extern uint32_t last_time_refresh_matrix;

#define DEFAULT_LED_TEMPO1 1  // em centesimos de s (TMR0 period = 10ms)
#define DEFAULT_LED_TEMPO0 100   // em centesimos de s (TMR0 period = 10ms)

uint8_t     ws2812_bits[24];
uint8_t     led_rgb_on[3]={0,255,0};
uint8_t     led_rgb_off[3]={0,0,0};
uint16_t    led_tempo1=DEFAULT_LED_TEMPO1;        // em centesimos de s (TMR0 period = 10ms)
uint16_t    led_tempo0=DEFAULT_LED_TEMPO0;        // em centesimos de s (TMR0 period = 10ms)
uint8_t     led_status=ON;


void led_update(void) {
    
    if (cents_since_start - last_time_refresh_matrix >= MATRIX_REFRESH_RATE)  {
        last_time_refresh_matrix=cents_since_start;
        DMA1CON0bits.DMA1SIRQEN = 1;  //Trigger the DMA Transfer
    
    }
    
    //Update do on_board led (bigbang - sõ existe dois canais DMA que estão  a ser usado para a led_matrix)
    if (led_status) {
        ws2812_send(led_rgb_on[0],led_rgb_on[1],led_rgb_on[2]);
        led_tempo1--;
        if (!led_tempo1) {
            led_status = ! led_status;
            led_tempo1=DEFAULT_LED_TEMPO1;
        }
    }     
    else
        ws2812_send(led_rgb_off[0],led_rgb_off[1],led_rgb_off[2]);
        led_tempo0--;
        if (!led_tempo0) {
            led_status = ! led_status;
            led_tempo0=DEFAULT_LED_TEMPO0;
        }
        
    cents_since_start++;
        
}


void led_initialize(void) {

    ws2812_send(0,0,0);
     
}


uint32_t bitflip(uint8_t b) {
   b = (uint8_t)( (b & 0xF0) >> 4 | (b & 0x0F) << 4 );
   b = (uint8_t)( (b & 0xCC) >> 2 | (b & 0x33) << 2 );
   b = (uint8_t)( (b & 0xAA) >> 1 | (b & 0x55) << 1 );
   return (uint32_t)b;
}

                               
                               
                               
// use of do{...} while (0) allow the macro to be inserted in a multi statement if correctly.https://www.microchip.com/forums/m909941.aspx
#define SET_DIN_WS2812B(bit)  do { LATBbits.LATB7 = bit; } while(0) 

void ws2812_send(uint8_t red, uint8_t green, uint8_t blue) {
int8_t i,j;


    // Build in ws2812_bits the bit sequence to send to ws2812 (THe order is GGGGGGGG RRRRRRRR BBBBBBBB with MSB first)
    //The use of an array allow to reduce the execution time sending the bits
    for (i=0,j=7;j>=0;j--,i++)
      ws2812_bits[i]= ((green & (1 << j)) !=0) ;
    
    for (j=7;j>=0;j--,i++)
      ws2812_bits[i]= ((red & (1 << j)) !=0) ;

    for (j=7;j>=0;j--,i++)
      ws2812_bits[i]= ((blue & (1 << j)) !=0) ;


    //_XTAL_FREQ =64000000  1/64000000 = 15.625 ns  4*15.625 = 62.5ns minimum instruction cycle time
    // 0.35us=350ns / 62.5 ns = 5.6 => 7 nops (com 6 falhava...))
    // Os valores menores são: (Estesvalores foram testados na pratica, mas nos datasheets eles indicam tempo maiores!!!)
    // BIT 1     1                   0
    //         7 nops (437.5ns)    2 nops (125ns)    Tbit=562.5ns 
    //              
    // BIT 0     1         0
    //         2 nops    1 nops
    // Agora estão simétricos e iguais a 750ns (12 nops)+ 250 ns (4 nops)
    // O tempo de separação entre bits, tempo a zero, n é critico mas não pode ser  (tenmpo a zero da onda) não pode ser superior a 40us (testei 40us OK,  50us deu mal))
    // Só programa por causa dos saltos (if else mete ai um overhad de 1us! Só funciona porque os leds não ligam muito ao tempo a zero!             
    INTERRUPT_GlobalInterruptHighDisable();
    INTERRUPT_GlobalInterruptLowDisable();
    for(i=0;i<24;i++) {
        if  (ws2812_bits[i]==1) {
            A_LED_SetHigh();
            NOP();
            NOP();
            NOP();
            NOP();
            NOP();
            NOP();
            NOP();
            NOP();
            NOP();
            NOP();
            NOP();
//            NOP();            //Para acertar para os 750ns - ver disassembly
            A_LED_SetLow();
            NOP();
            NOP();
            NOP();
            NOP();
            
        }
        else {
            A_LED_SetHigh();
            NOP();
            NOP();
            NOP();
//            NOP();            //Para acertar para os 250ns - ver disassembly
            A_LED_SetLow();
            NOP();
            NOP();
            NOP();
            NOP();
            NOP();
            NOP();
            NOP();
            NOP();
            NOP();
            NOP();
            NOP();
            NOP();
                       
        }
        
    }
    
    INTERRUPT_GlobalInterruptHighEnable();
    INTERRUPT_GlobalInterruptLowEnable();

 
}



//Versão SPI
void ws2812_send_SPI(uint8_t red, uint8_t green, uint8_t blue) {

   
    INTERRUPT_GlobalInterruptHighDisable();
    INTERRUPT_GlobalInterruptLowDisable();
    
    SPI1TXB = green;
  //  while(SPI1STATUSbits.TXBE==0); //N é preciso porque o FIFO é de dois bytes...
    SPI1TXB = red;
    while(SPI1STATUSbits.TXBE==0);
    SPI1TXB = blue;
    while(SPI1STATUSbits.TXBE==0);
    
    INTERRUPT_GlobalInterruptHighEnable();
    INTERRUPT_GlobalInterruptLowEnable();

 
}


void basic_test_ws2812_bits(void) {
    for(;;) {
       // for(uint8_t j=0; j<100;j++)
          ws2812_send_SPI(0xFF, 0x00, 00) ;
        __delay_ms(1);

    }

}


void fill_matrix_16x16(uint8_t red, uint8_t green, uint8_t blue) {
 int8_t i;
 int16_t j;
 
    // Build in ws2812_bits the bit sequence to send to ws2812 (THe order is GGGGGGGG RRRRRRRR BBBBBBBB with MSB first)
    //The use of an array allow to reduce the execution time sending the bits
    for (i=0,j=7;j>=0;j--,i++)
        if ( ( green & (1 << j)) !=0 )
           ws2812_bits[i]= 0b11101110; 
    
        else
            ws2812_bits[i]= 0b10001000;
    
    for (j=7;j>=0;j--,i++)
        if ( ( red & (1 << j)) !=0 )
           ws2812_bits[i]= 0b11101110;
        else
            ws2812_bits[i]= 0b10001000;
    
    for (j=7;j>=0;j--,i++)
        if ( ( blue & (1 << j)) !=0 )
           ws2812_bits[i]= 0b11101110;
        else
            ws2812_bits[i]= 0b10001000;
    
    INTERRUPT_GlobalInterruptHighDisable();
    INTERRUPT_GlobalInterruptLowDisable();
    for(j=0;j<16*16;j++) {
        for(i=0;i<24;i++) {
            //Com SPI=8Mhz, o tempo de transmissao de 1 bit, é mais rápido que o que o programa demora aqui pelo que se pode colocar simplesmente no SFR
            SPI1TXB = ws2812_bits[i];
            // SPI1_WriteByte(ws2812_bits[i]);
        }     
        }
    ;
    INTERRUPT_GlobalInterruptHighEnable();
    INTERRUPT_GlobalInterruptLowEnable();
    __delay_ms(20);
}





void basic_test_ws2812(void) {
    for (;;) {
    printf("RED\r\n");
        ws2812_send(255, 0, 0) ;
        Delay_ms(1000);
        
        printf("GREEN\r\n");
        ws2812_send(0, 255, 0) ;
        Delay_ms(1000);
                
        printf("BLUE\r\n");
        ws2812_send(0, 0, 255) ;
        Delay_ms(1000);
      
        printf("WHITE\r\n");
        ws2812_send(255, 255, 255) ;
        Delay_ms(1000);
      
        printf("BLACK\r\n");
        ws2812_send(0, 0, 0) ;
        Delay_ms(2000);
    } 
}

