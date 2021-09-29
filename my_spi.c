#include "my_defs.h"



//OK
void my_SPI1_WriteByte(uint8_t byte) {

while(SPI1CON2bits.BUSY)
    ;
    
    //Transmit only mode
    SPI1CON2bits.TXR=1;
    SPI1CON2bits.RXR=0;
    SPI1TCNTL=1; SPI1TCNTH=0; 
    
    SPI1TXB = byte;
    while(SPI1STATUSbits.TXBE==0);
   
}



void my_SPI1_WriteWord(uint8_t byteH, uint8_t byteL) {

while(SPI1CON2bits.BUSY)
    ;
    
    //Transmit only mode
    SPI1CON2bits.TXR=1;
    SPI1CON2bits.RXR=0;
    SPI1TCNTL=2; SPI1TCNTH=0; 
    
    SPI1TXB = byteH;
    SPI1TXB = byteL;
    
    while(SPI1STATUSbits.TXBE==0);

    
}

uint8_t my_SPI1_ReadByte(void) {
uint8_t ret;   

    while(SPI1CON2bits.BUSY)
        ;

 //   SPI1STATUSbits.CLRBF=1; // Reset the receive and transmit buffers, making both buffers empty
    
     // Se usar-se o module receive only (RXR=1, TXR=0), ele no segundo byte que receber começa a enviar os que já tinha recebido antes Pg.501 e 509. Não encontrei maneira de evitar isso (Obs. A mem+oria n parceia se chatera...))
    //A soluçãao foi de se meter em modo full-duplex e antes de se receber enviar-se sempre um zero.
    //Full-Duplex mode )TXR=RXR=1);

      
    SPI1CON2bits.TXR=1;
    SPI1CON2bits.RXR=1;
 
         
    // Counter=1
    SPI1TCNTL=1; SPI1TCNTH=0; 
    SPI1TXB=0;
      
    while(!PIR2bits.SPI1RXIF);
    ret=SPI1RXB;
    
    return ret;
    
}




void my_SPI1_Initialize(void)
{
    
 
    //EN - - - - LSBF MST  BMODE  ->  EN=0 DISABLED LSBF=0 MSb first (normal SPI mode); MST=1 bus master; BMODE=1 (SPI1TCNT = N bytes to transfer) ; 
    SPI1CON0 = 0b00000011;
    
  
//    Bit 7 SMP - Master mode:
//        1 = SDI input is sampled at the end of data output time
//        0 = SDI input is sampled in the middle of data output time
//    bit 6 CKE: Clock Edge Select bit
//        1 = Output data changes on transition from active to idle clock state
//        0 = Output data changes on transition from idle to active clock state
//    bit 5 CKP: Clock Polarity Select bit
//        1 = Idle state for SCK is high level
//        0 = Idle state for SCK is low level
    
    // SMP CKE CKP FST - SSP  SDIP SDOP  ->   SMP=0 SDI sasmpled Middle; CKE Active to idle; CKP Idle:Low, Active:High; FST disabled; SSP active low; SDIP active high; SDOP active high; 
    SPI1CON1 = 0b00000000;
    
    
    //BUSY  SSFLT - - - SSET TXR RXR  ->     //SSET disabled; TX=1xFIFO data is required for a transfer, RXR=0 Received data is not stored in the FIFO 
    SPI1CON2 = 0b000000010;
    
    //- - - - - TWIDTH2 TWIDTH1 TWIDTH0 
    SPI1TWIDTH=0b00000000; //FOR BMODE =1 8 bits to transfer
    
    //CLKSEL FOSC; 
    SPI1CLK= 0b00000101; //0101 TMR2_Postscaled;
    
    //BAUD equal to input frequency 800KHz; 
    SPI1BAUD = 0x00;
 
    //RB1 = SDI1
    TRISBbits.TRISB1=1;
    ANSELBbits.ANSELB1=0;
    SPI1SDIPPS = 0x09;   //RB1->SPI1:SDI1; 
    // RB2 = SCK1
    TRISBbits.TRISB2 = 0;
    ANSELBbits.ANSELB2=0;
    SPI1SCKPPS = 0x0A;   //RB2->SPI1:SCK1;  
    RB2PPS = 0x1E;       //RB2->SPI1:SCK1;  
    //RC3 = SDO1
//    TRISCbits.TRISC3 = 0;
//    ANSELCbits.ANSELC3=0;
//    RC3PPS = 0x1F;   //RC3->SPI1:SDO1;  
//    
    // Com SPI1CON0bits.BMODE:
    //   SPI1TCNTL = Bits 7-0 of the Transfer Counter, counting the total number of bytes to transfer
    //   SPI1TCNTH = Bits 10-8 of the Transfer Counter, counting the total number of bytes to transfer
    SPI1TCNTL=1; SPI1TCNTH=0; 
    
    // ENable do modulo SPI1
    SPI1CON0bits.EN = 1;       
    
        
}





