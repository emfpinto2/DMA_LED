
/**
  DMA Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    dma2.c

  @Summary
    This is the generated header file for the DMA driver using MPLAB(c) Code Configurator

  @Description
    This source file provides APIs for DMA.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.15.3
        Device            :  PIC18F25K42
        Driver Version    :  1.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40
 */

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
 */

/**
  Section: Included Files
 */
#include "my_defs.h"
#include <xc.h>


//------------------------------------------------------------------------------
#define m_ARBITER_LOCK()    \
      do{ \
           asm("BANKSEL PRLOCK");\
           asm("MOVLW   0x55");\
           asm("MOVWF   (PRLOCK & 0xFF)");\
           asm("MOVLW   0xAA");\
           asm("MOVWF   (PRLOCK & 0xFF)");\
           asm("BSF     (PRLOCK & 0xFF),0");\
        }while(0)
//------------------------------------------------------------------------------
#define m_ARBITER_UNLOCK()  \
      do{ \
           asm("BANKSEL PRLOCK");\
           asm("MOVLW   0x55");\
           asm("MOVWF   (PRLOCK & 0xFF)");\
           asm("MOVLW   0xAA");\
           asm("MOVWF   (PRLOCK & 0xFF)");\
           asm("BCF     (PRLOCK & 0xFF),0");\
        }while(0)

/**
  Section: Global Variables Definitions
 */

/**
  Section: DMA APIs
 */
extern uint8_t  Game_array[LED_COUNT_Y][LED_COUNT_X][3];
extern uint8_t  PixelBase[3];


/****************************************************************/
/* DBUG  FUNCTONS*/
/****************************************************************/

void Show_buffers(void) {
    printf("PixelBase[]\r\n");
    printf("  %02x %02x %02x\r\n",PixelBase[RED],PixelBase[GREEN],PixelBase[BLUE]);
    
    printf("PixelArray[][]\r\n");
    for (uint16_t i=0; i< 10; i++) {
        printf("  #%03d %02x %02x %02x\r\n",i,Game_array[i][RED], Game_array[i][GREEN], Game_array[i][BLUE]);
        
    }
    printf("DMA2SSA=%02x%02x%02x   DMA2DSA=%02x%02x\r\n",DMA2SSAU,DMA2SSAH,DMA2SSAL,  DMA2DSAH,DMA2DSAL);
    printf("DMA2SPTR=%02x%02x%02x   DMA2DPTR=%02x%02x\r\n\r\n",DMA2SPTRU,DMA2SPTRH,DMA2SPTRL,  DMA2DPTRH,DMA2DPTRL);
 
    printf("\r\n");
    
}


//Tentativa para preecnher a memoria usando o DMA2 channel- Ver comentarios na função my_DMA2_initialize
void Matrix_fill_DMA2(uint8_t red, uint8_t green, uint8_t blue) {
    
    PixelBase[RED]=red;
    PixelBase[GREEN]=green;
    PixelBase[BLUE]=blue;
    
    DMA2CON0bits.DMA2SIRQEN=1;
    PIR6bits.DMA2SCNTIF=0;
    DMA2CON0bits.DGO=1;
    Delay_ms(50);
    printf("DGO=%d  IF=%d EN=%d\r\n", DMA2CON0bits.DGO,PIR6bits.DMA2SCNTIF,DMA2CON0bits.DMA2SIRQEN);
   
}


/*********************************************************************************************************************/


/*
 - Quando activo as flags de interripção ele encrava. Porque n se tem os ISR definidos?
  -  Ele só faz a tarnsferência de 3, com o DGO. Se fizer varias vezes ele faz bem! Parece que para sempre que a source se esgota!
 - Independentemente  do SSTP ou do DSTP ele transfere sempre só menor. Se pedir para ser 3, como está ele transfere 3, se pedir 6 ele transfere 6

*/
void my_DMA2_Initialize(void) {   
    
    /* stop and clear DMA 2  */
    DMA2CON0 = 0;

    /* configure DMA 2 */

    /* 1. Program the appropriate Source and Destination addresses for the
     * transaction into the DMAxSSA and DMAxDSA registers
     */
    DMA2SSA = (volatile __uint24)&PixelBase; /* source address */
    DMA2DSA = (volatile unsigned int)&Game_array; /* destination address */

    //00 = DMAxSSA<21:0> points to SFR/GPR Data Space
    DMA2CON1bits.SMR=0b00;  
    
        /* 5. If the user desires to disable data transfers once the message has
     * completed, then the SSTP and DSTP bits in DMAxCON0 register need to be set
     */
    DMA2CON1bits.SSTP = 0; /* SIRQEN bit clear when source counter reloads */
    DMA2CON1bits.DSTP = 1; /* SIRQEN bit clear when Destination Counter reloads */
    
    /* 3. Program the SMODE and DMODE bits to select the addressing mode.
     */
    DMA2CON1bits.SMODE = 0b01; /* source is incremented after each transfer completion */
    DMA2CON1bits.DMODE = 0b01; /* destination is incremented after each transfer completion */

    /* 4. Program the Source size DMAxSSZ and Destination size DMAxDSZ
     * registers with the number of bytes to be transferred. It is recommended
     * for proper operation that the size registers be a multiple of each other.
     */
    DMA2SSZ = 3; /* source transfer size is size of array */
    DMA2DSZ = 7*3;//TOTAL_LEDS*3; /*  destination size 1 */

   
    PIR6bits.DMA2DCNTIF = 0; //clear Destination Count Interrupt Flag bit
    PIR6bits.DMA2SCNTIF = 0; //clear Source Count Interrupt Flag bit
    PIR6bits.DMA2AIF = 0; //clear abort Interrupt Flag bit
    PIR6bits.DMA2ORIF = 0; //clear overrun Interrupt Flag bit
    
    PIE6bits.DMA2DCNTIE = 0; //enable Destination Count 0 Interrupt
    PIE6bits.DMA2SCNTIE = 0; //disable Source Count Interrupt
    PIE6bits.DMA2AIE = 0; //disable abort Interrupt
    PIE6bits.DMA2ORIE = 0; //disable overrun Interrupt

    /* 6. If using hardware triggers for data transfer, setup the hardware
     * trigger interrupt sources for the starting and aborting DMA transfers
     * (DMAxSIRQ and DMAxAIRQ), and set the corresponding interrupt request
     * enable bits (SIRQEN and AIRQEN).
     */
    DMA2SIRQ = DMA2SCNT;     /* Hardware trigger*/
    DMA2AIRQ = 0;                           /* Abort trigger  */

    /* disable temporallily hardware source trigger  */
    DMA2CON0bits.DMA2SIRQEN = 0;

    /* 7. Select the priority level for the DMA
     * (see Section 3.1 ?System Arbitration?) and lock the priorities
     * (see Section 3.1.1 ?Priority Lock?)
     * 0 being the highest priority and 4 being the lowest priority.
     */
    m_ARBITER_UNLOCK(); /* unlock Arbiter settings */
    MAINPR = 3;
    ISRPR = 2;
    DMA1PR = 0;
    DMA2PR = 1;
    SCANPR = 4;
    m_ARBITER_LOCK(); /* lock Arbiter settings */

    /* 8. Enable the DMA (DMAxCON0bits. EN = 1)
     */
    DMA2CON0bits.EN = 1;

    /* 9. If using software control for data transfer, set the DGO bit,
     * else this bit will be set by the hardware trigger.
     */
    //DMA2CON0bits.DGO = 1;
    
    /*
     * DMA Transfer is started with 
     *    MA1CON0bits.DMA1SIRQEN = 1;
     */


}


//void my_DMA2_Initialize(void) {   
//    
//    /* stop and clear DMA 2  */
//    DMA2CON0 = 0;
//
//    /* configure DMA 2 */
//
//    /* 1. Program the appropriate Source and Destination addresses for the
//     * transaction into the DMAxSSA and DMAxDSA registers
//     */
//    DMA2SSA = (volatile __uint24)&PixelBase; /* source address */
//    DMA2DSA = (volatile __uint24)&PixelArray; /* destination address */
//
//    /* 2. Select the source memory region that is being addressed by DMAxSSA
//     * register, using the SMR<1:0> bits.
//     */
//    DMA2CON1bits.SMR = 0b00; /* source pointer points to GPR space */
//
//    /* 3. Program the SMODE and DMODE bits to select the addressing mode.
//     */
//    DMA2CON1bits.SMODE = 0b01; /* source is incremented after each transfer completion */
//    DMA2CON1bits.DMODE = 0b01; /* destination is incremented after each transfer completion */
//
//    /* 4. Program the Source size DMAxSSZ and Destination size DMAxDSZ
//     * registers with the number of bytes to be transferred. It is recommended
//     * for proper operation that the size registers be a multiple of each other.
//     */
//    DMA2SSZ = 3; /* source transfer size is size of array */
//    DMA2DSZ = 3*10;//TOTAL_LEDS*3; /*  destination size 1 */
//
//
//    /* 5. If the user desires to disable data transfers once the message has
//     * completed, then the SSTP and DSTP bits in DMAxCON0 register need to be set
//     */
//    DMA2CON1bits.SSTP = 0; /* SIRQEN bit is cleared when source counter reloads */
//    DMA2CON1bits.DSTP = 1; /* SIRQEN bit is not cleared when Destination Counter reloads */
//
//    /* 6. If using hardware triggers for data transfer, setup the hardware
//     * trigger interrupt sources for the starting and aborting DMA transfers
//     * (DMAxSIRQ and DMAxAIRQ), and set the corresponding interrupt request
//     * enable bits (SIRQEN and AIRQEN).
//     */
//    DMA2SIRQ = 0; /* No hardware trigger slected. Trasfer initiate by software suing the DGO bit*/
//    DMA2AIRQ = 0; /* No abort trigger  */
//
//    /* disable temporallily hardware source trigger  */
//    DMA2CON0bits.DMA2SIRQEN = 0;
//
//
//    /* 7. Select the priority level for the DMA
//     * (see Section 3.1 ?System Arbitration?) and lock the priorities
//     * (see Section 3.1.1 ?Priority Lock?)
//     * 0 being the highest priority and 4 being the lowest priority.
//     */
//    m_ARBITER_UNLOCK(); /* unlock Arbiter settings */
//    MAINPR = 3;
//    ISRPR = 2;
//    DMA1PR = 0;
//    DMA2PR = 1;
//    SCANPR = 4;
//    m_ARBITER_LOCK(); /* lock Arbiter settings */
//
//    /* 8. Enable the DMA (DMAxCON0bits. EN = 1)
//     */
//    DMA2CON0bits.EN = 1;
//
//    /* 9. If using software control for data transfer, set the DGO bit,
//     * else this bit will be set by the hardware trigger.
//     */
//    DMA2CON0bits.DGO = 1;
//    
//    /*
//     * DMA Transfer is started with 
//     *        DMA2CON0bits.DGO = 1;
//     */
//
//}



/**
  End of File
 */