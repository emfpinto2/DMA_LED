/**
  PWM1 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    pwm1.c

  @Summary
    This is the generated driver implementation file for the PWM1 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides implementations for driver APIs for PWM1.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18F26K83
        Driver Version    :  2.01
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

/**
  Section: Included Files
*/

#include <xc.h>
#include "pwm1.h"

/**
  Section: Macro Declarations
*/

#define PWM1_INITIALIZE_DUTY_VALUE    99

/**
  Section: PWM Module APIs
*/

void PWM1_Initialize(void)
{
    // Set the PWM1 to the options selected in the User Interface
	
	// MODE PWM; EN enabled; FMT right_aligned; 
	CCP1CON = 0x8C;    
	
	// RH 0; 
	CCPR1H = 0x00;    
	
	// RL 99; 
	CCPR1L = 0x63;    

	// Selecting Timer 4
	CCPTMRS0bits.C1TSEL = 0x2;
    
}

void PWM1_LoadDutyValue(uint16_t dutyValue)
{
    dutyValue &= 0x03FF;
    
    // Load duty cycle value
    if(CCP1CONbits.FMT)
    {
        dutyValue <<= 6;
        CCPR1H = (uint8_t)(dutyValue >> 8);
        CCPR1L = (uint8_t)dutyValue;
    }
    else
    {
        CCPR1H = (uint8_t)(dutyValue >> 8);
        CCPR1L = (uint8_t)dutyValue;
    }
}

bool PWM1_OutputStatusGet(void)
{
    // Returns the output status
    return(CCP1CONbits.OUT);
}
/**
 End of File
*/

