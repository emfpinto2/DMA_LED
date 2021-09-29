/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18F26K83
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
        MPLAB 	          :  MPLAB X 5.45	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set KEY_RIGHT aliases
#define KEY_RIGHT_TRIS                 TRISAbits.TRISA0
#define KEY_RIGHT_LAT                  LATAbits.LATA0
#define KEY_RIGHT_PORT                 PORTAbits.RA0
#define KEY_RIGHT_WPU                  WPUAbits.WPUA0
#define KEY_RIGHT_OD                   ODCONAbits.ODCA0
#define KEY_RIGHT_ANS                  ANSELAbits.ANSELA0
#define KEY_RIGHT_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define KEY_RIGHT_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define KEY_RIGHT_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define KEY_RIGHT_GetValue()           PORTAbits.RA0
#define KEY_RIGHT_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define KEY_RIGHT_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define KEY_RIGHT_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define KEY_RIGHT_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define KEY_RIGHT_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define KEY_RIGHT_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define KEY_RIGHT_SetAnalogMode()      do { ANSELAbits.ANSELA0 = 1; } while(0)
#define KEY_RIGHT_SetDigitalMode()     do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set KEY_LEFT aliases
#define KEY_LEFT_TRIS                 TRISAbits.TRISA2
#define KEY_LEFT_LAT                  LATAbits.LATA2
#define KEY_LEFT_PORT                 PORTAbits.RA2
#define KEY_LEFT_WPU                  WPUAbits.WPUA2
#define KEY_LEFT_OD                   ODCONAbits.ODCA2
#define KEY_LEFT_ANS                  ANSELAbits.ANSELA2
#define KEY_LEFT_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define KEY_LEFT_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define KEY_LEFT_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define KEY_LEFT_GetValue()           PORTAbits.RA2
#define KEY_LEFT_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define KEY_LEFT_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define KEY_LEFT_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define KEY_LEFT_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define KEY_LEFT_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define KEY_LEFT_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define KEY_LEFT_SetAnalogMode()      do { ANSELAbits.ANSELA2 = 1; } while(0)
#define KEY_LEFT_SetDigitalMode()     do { ANSELAbits.ANSELA2 = 0; } while(0)

// get/set KEY_START aliases
#define KEY_START_TRIS                 TRISAbits.TRISA7
#define KEY_START_LAT                  LATAbits.LATA7
#define KEY_START_PORT                 PORTAbits.RA7
#define KEY_START_WPU                  WPUAbits.WPUA7
#define KEY_START_OD                   ODCONAbits.ODCA7
#define KEY_START_ANS                  ANSELAbits.ANSELA7
#define KEY_START_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define KEY_START_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define KEY_START_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define KEY_START_GetValue()           PORTAbits.RA7
#define KEY_START_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define KEY_START_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)
#define KEY_START_SetPullup()          do { WPUAbits.WPUA7 = 1; } while(0)
#define KEY_START_ResetPullup()        do { WPUAbits.WPUA7 = 0; } while(0)
#define KEY_START_SetPushPull()        do { ODCONAbits.ODCA7 = 0; } while(0)
#define KEY_START_SetOpenDrain()       do { ODCONAbits.ODCA7 = 1; } while(0)
#define KEY_START_SetAnalogMode()      do { ANSELAbits.ANSELA7 = 1; } while(0)
#define KEY_START_SetDigitalMode()     do { ANSELAbits.ANSELA7 = 0; } while(0)

// get/set RB1 procedures
#define RB1_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define RB1_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define RB1_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define RB1_GetValue()              PORTBbits.RB1
#define RB1_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define RB1_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define RB1_SetPullup()             do { WPUBbits.WPUB1 = 1; } while(0)
#define RB1_ResetPullup()           do { WPUBbits.WPUB1 = 0; } while(0)
#define RB1_SetAnalogMode()         do { ANSELBbits.ANSELB1 = 1; } while(0)
#define RB1_SetDigitalMode()        do { ANSELBbits.ANSELB1 = 0; } while(0)

// get/set RB2 procedures
#define RB2_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define RB2_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define RB2_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define RB2_GetValue()              PORTBbits.RB2
#define RB2_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define RB2_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define RB2_SetPullup()             do { WPUBbits.WPUB2 = 1; } while(0)
#define RB2_ResetPullup()           do { WPUBbits.WPUB2 = 0; } while(0)
#define RB2_SetAnalogMode()         do { ANSELBbits.ANSELB2 = 1; } while(0)
#define RB2_SetDigitalMode()        do { ANSELBbits.ANSELB2 = 0; } while(0)

// get/set RB3 procedures
#define RB3_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define RB3_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define RB3_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define RB3_GetValue()              PORTBbits.RB3
#define RB3_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define RB3_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define RB3_SetPullup()             do { WPUBbits.WPUB3 = 1; } while(0)
#define RB3_ResetPullup()           do { WPUBbits.WPUB3 = 0; } while(0)
#define RB3_SetAnalogMode()         do { ANSELBbits.ANSELB3 = 1; } while(0)
#define RB3_SetDigitalMode()        do { ANSELBbits.ANSELB3 = 0; } while(0)

// get/set RB4 procedures
#define RB4_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define RB4_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define RB4_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define RB4_GetValue()              PORTBbits.RB4
#define RB4_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define RB4_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define RB4_SetPullup()             do { WPUBbits.WPUB4 = 1; } while(0)
#define RB4_ResetPullup()           do { WPUBbits.WPUB4 = 0; } while(0)
#define RB4_SetAnalogMode()         do { ANSELBbits.ANSELB4 = 1; } while(0)
#define RB4_SetDigitalMode()        do { ANSELBbits.ANSELB4 = 0; } while(0)

// get/set RB5 procedures
#define RB5_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define RB5_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define RB5_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define RB5_GetValue()              PORTBbits.RB5
#define RB5_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define RB5_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define RB5_SetPullup()             do { WPUBbits.WPUB5 = 1; } while(0)
#define RB5_ResetPullup()           do { WPUBbits.WPUB5 = 0; } while(0)
#define RB5_SetAnalogMode()         do { ANSELBbits.ANSELB5 = 1; } while(0)
#define RB5_SetDigitalMode()        do { ANSELBbits.ANSELB5 = 0; } while(0)

// get/set A_LED aliases
#define A_LED_TRIS                 TRISBbits.TRISB7
#define A_LED_LAT                  LATBbits.LATB7
#define A_LED_PORT                 PORTBbits.RB7
#define A_LED_WPU                  WPUBbits.WPUB7
#define A_LED_OD                   ODCONBbits.ODCB7
#define A_LED_ANS                  ANSELBbits.ANSELB7
#define A_LED_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define A_LED_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define A_LED_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define A_LED_GetValue()           PORTBbits.RB7
#define A_LED_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define A_LED_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define A_LED_SetPullup()          do { WPUBbits.WPUB7 = 1; } while(0)
#define A_LED_ResetPullup()        do { WPUBbits.WPUB7 = 0; } while(0)
#define A_LED_SetPushPull()        do { ODCONBbits.ODCB7 = 0; } while(0)
#define A_LED_SetOpenDrain()       do { ODCONBbits.ODCB7 = 1; } while(0)
#define A_LED_SetAnalogMode()      do { ANSELBbits.ANSELB7 = 1; } while(0)
#define A_LED_SetDigitalMode()     do { ANSELBbits.ANSELB7 = 0; } while(0)

// get/set RC2 procedures
#define RC2_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define RC2_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define RC2_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define RC2_GetValue()              PORTCbits.RC2
#define RC2_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define RC2_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define RC2_SetPullup()             do { WPUCbits.WPUC2 = 1; } while(0)
#define RC2_ResetPullup()           do { WPUCbits.WPUC2 = 0; } while(0)
#define RC2_SetAnalogMode()         do { ANSELCbits.ANSELC2 = 1; } while(0)
#define RC2_SetDigitalMode()        do { ANSELCbits.ANSELC2 = 0; } while(0)

// get/set RC3 procedures
#define RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RC3_GetValue()              PORTCbits.RC3
#define RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define RC3_SetPullup()             do { WPUCbits.WPUC3 = 1; } while(0)
#define RC3_ResetPullup()           do { WPUCbits.WPUC3 = 0; } while(0)
#define RC3_SetAnalogMode()         do { ANSELCbits.ANSELC3 = 1; } while(0)
#define RC3_SetDigitalMode()        do { ANSELCbits.ANSELC3 = 0; } while(0)

// get/set RC5 procedures
#define RC5_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define RC5_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define RC5_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define RC5_GetValue()              PORTCbits.RC5
#define RC5_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define RC5_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define RC5_SetPullup()             do { WPUCbits.WPUC5 = 1; } while(0)
#define RC5_ResetPullup()           do { WPUCbits.WPUC5 = 0; } while(0)
#define RC5_SetAnalogMode()         do { ANSELCbits.ANSELC5 = 1; } while(0)
#define RC5_SetDigitalMode()        do { ANSELCbits.ANSELC5 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()              PORTCbits.RC6
#define RC6_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define RC6_SetPullup()             do { WPUCbits.WPUC6 = 1; } while(0)
#define RC6_ResetPullup()           do { WPUCbits.WPUC6 = 0; } while(0)
#define RC6_SetAnalogMode()         do { ANSELCbits.ANSELC6 = 1; } while(0)
#define RC6_SetDigitalMode()        do { ANSELCbits.ANSELC6 = 0; } while(0)

// get/set RC7 procedures
#define RC7_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define RC7_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define RC7_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define RC7_GetValue()              PORTCbits.RC7
#define RC7_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define RC7_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define RC7_SetPullup()             do { WPUCbits.WPUC7 = 1; } while(0)
#define RC7_ResetPullup()           do { WPUCbits.WPUC7 = 0; } while(0)
#define RC7_SetAnalogMode()         do { ANSELCbits.ANSELC7 = 1; } while(0)
#define RC7_SetDigitalMode()        do { ANSELCbits.ANSELC7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/