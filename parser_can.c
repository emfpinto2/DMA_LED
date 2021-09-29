/*
 * File:   parser_can.c
 * Author: emfpi
 *
 * Created on April 10, 2020, 4:17 PM
 */

// ATENÇÃO: Velocidade é só 250Kbps
#include <xc.h>
#include "my_defs.h"

extern uint8_t ball_posx,ball_posy;
extern uint8_t player_number;

uCAN_MSG  can_message;
STRUCT_AF can_arbitrationID;

#define BUILD_CAN_arbitration_id(sourceID,targetID,instruction,index,subindex) (((uint32_t)sourceID<<24) | ((uint32_t)targetID<<19) | ((uint32_t)instruction<<16) | ((uint32_t)index<<8) | ((uint32_t)subindex) )
 
extern uint32_t cents_since_start;

uint8_t CAN_receive_msg(void){
uint8_t ret;
       
    ret = CAN_messagesInBuffer();
    if (ret) {
        printf("Number of CAN messages in buffer=%d\r\n",ret);
        ret=CAN_receive(&can_message);
        can_arbitrationID.sourceID=can_message.frame.id>>24;
        can_arbitrationID.targetID=(can_message.frame.id>>19)&0x0000001F;
        can_arbitrationID.instruction=(can_message.frame.id>>16)&0x00000007;
        can_arbitrationID.index=(can_message.frame.id>>8)&0x000000FF;
        can_arbitrationID.subindex=can_message.frame.id&0x000000FF;

        printf("Value returned buy CAN_receive: %d\r\n",ret);
        printf("idType=%02X\r\n", can_message.frame.idType);
        printf("id(32bits) %08lx\r\n",can_message.frame.id);
        printf("  sourceID=%02X\r\n", can_arbitrationID.sourceID); 
        printf("  targetID=%02X\r\n", can_arbitrationID.targetID); 
        printf("  instruction=%02X\r\n", can_arbitrationID.instruction); 
        printf("  index=%02X\r\n", can_arbitrationID.index); 
        printf("  subindex=%02X\r\n", can_arbitrationID.subindex); 
        printf("dlc=%02X\r\n", can_message.frame.dlc); 
        printf("Data: %02X %02X %02X %02X %02X %02X %02X %02X\r\n\r\n", can_message.frame.data0, can_message.frame.data1, can_message.frame.data2, can_message.frame.data3, can_message.frame.data4, can_message.frame.data5, can_message.frame.data6, can_message.frame.data7);
        return can_arbitrationID.subindex;
            
    }
    return FALSE;

}


uint8_t CAN_send_player_moved_msg(uint8_t player_posx, uint8_t player_posy) {
uint8_t ret;   
    can_message.frame.idType=dEXTENDED_CAN_MSG_ID_2_0B;

    //Usando para o Arbitration field um long
    can_message.frame.id=BUILD_CAN_arbitration_id(player_number, 0x00, 0x00, 0x00, GAME_UPDATE_PLAYER_CAN_MSG); // (sourceID<<24) | (targetID<<19) | (instruction<<16) | (index<<8) | (subindex)
    //printf("Arbitration id=%x\r\n",can_message.frame.id);

    can_message.frame.dlc=2;
    can_message.frame.data0=player_posx;
    can_message.frame.data1=player_posy;
    
    ret=CAN_transmit(&can_message);
    printf("CAN transmitted status=%d\r\n\r\n",ret);
    
    return ret;
}


uint8_t CAN_send_ball_moved_msg(void) {
uint8_t ret;   
    can_message.frame.idType=dEXTENDED_CAN_MSG_ID_2_0B;

    //Usando para o Arbitration field um long
    can_message.frame.id=BUILD_CAN_arbitration_id(0x00, 0x00, 0x00, 0x00, GAME_UPDATE_BALL_CAN_MSG); // (sourceID<<24) | (targetID<<19) | (instruction<<16) | (index<<8) | (subindex)
    //printf("Arbitration id=%x\r\n",can_message.frame.id);

    can_message.frame.dlc=2;
    can_message.frame.data0=ball_posx;
    can_message.frame.data1=ball_posy;
    
    ret=CAN_transmit(&can_message);
    printf("CAN transmitted status=%d\r\n\r\n",ret);
    
    return ret;
}


uint8_t CAN_send_start_msg(void) {
uint8_t ret;

    can_message.frame.idType=dEXTENDED_CAN_MSG_ID_2_0B;

    //Usando para o Arbitration field um long
    can_message.frame.id=BUILD_CAN_arbitration_id(0x00, 0x00, 0x00, 0x00, START_GAME_CAN_MSG); // (sourceID<<24) | (targetID<<19) | (instruction<<16) | (index<<8) | (subindex)
    //printf("Arbitration id=%x\r\n",can_message.frame.id);

//    can_message.frame.dlc=1;
//    can_message.frame.data0=START_GAME_CAN_MSG;
    
    ret=CAN_transmit(&can_message);
    printf("CAN transmitted status=%d\r\n\r\n",ret);
    
    return ret;
}


uint8_t CAN_send_stop_msg(void) {
uint8_t ret;

    can_message.frame.idType=dEXTENDED_CAN_MSG_ID_2_0B;

    //Usando para o Arbitration field um long
    can_message.frame.id=BUILD_CAN_arbitration_id(0x00, 0x00, 0x00, 0x00, STOP_GAME_CAN_MSG); // (sourceID<<24) | (targetID<<19) | (instruction<<16) | (index<<8) | (subindex)
    //printf("Arbitration id=%x\r\n",can_message.frame.id);

//    can_message.frame.dlc=1;
//    can_message.frame.data0=STOP_GAME_CAN_MSG;
    
    ret=CAN_transmit(&can_message);
    printf("CAN transmitted status=%d\r\n\r\n",ret);
    
    return ret;
}


// ATENÇÃO: Velocidade é só 250Kbps
void teste_can(void) {
uint8_t i,ret;


    for(;;)
    for(i=0;i<10;i++) {
        can_message.frame.idType=dEXTENDED_CAN_MSG_ID_2_0B;
        
        //Usando para o Arbitration field um long
        can_message.frame.id=BUILD_CAN_arbitration_id(0x04, 0x00, 0x00, 0x00, 0x00); // (sourceID<<24) | (targetID<<19) | (instruction<<16) | (index<<8) | (subindex)
        //printf("Arbitration id=%x\r\n",can_message.frame.id);

        can_message.frame.dlc=8;
        can_message.frame.data0=0;
        can_message.frame.data1=1;
        can_message.frame.data2=2;
        can_message.frame.data3=3;
        can_message.frame.data4=4;
        can_message.frame.data5=5;
        can_message.frame.data6=6;
        can_message.frame.data7=7;
        ret=CAN_transmit(&can_message);
        printf("CAN transmitted status=%d\r\n\r\n",ret);
        
        
        ret= CAN_messagesInBuffer();
        if (ret) printf("Number of CAN messages in buffer=%d\r\n",ret);
        if (ret) {
            ret=CAN_receive(&can_message);
            can_arbitrationID.sourceID=can_message.frame.id>>24;
            can_arbitrationID.targetID=(can_message.frame.id>>19)&0x0000001F;
            can_arbitrationID.instruction=(can_message.frame.id>>16)&0x00000007;
            can_arbitrationID.index=(can_message.frame.id>>8)&0x000000FF;
            can_arbitrationID.subindex=can_message.frame.id&0x000000FF;
                                
            printf("Value returned buy CAN_receive: %d\r\n",ret);
            printf("idType=%02X\r\n", can_message.frame.idType);
            printf("id(32bits) %08lx\r\n",can_message.frame.id);
            printf("  sourceID=%02X\r\n", can_arbitrationID.sourceID); 
            printf("  targetID=%02X\r\n", can_arbitrationID.targetID); 
            printf("  instruction=%02X\r\n", can_arbitrationID.instruction); 
            printf("  index=%02X\r\n", can_arbitrationID.index); 
            printf("  subindex=%02X\r\n", can_arbitrationID.subindex); 
            printf("dlc=%02X\r\n", can_message.frame.dlc); 
            printf("Data: %02X %02X %02X %02X %02X %02X %02X %02X\r\n\r\n", can_message.frame.data0, can_message.frame.data1, can_message.frame.data2, can_message.frame.data3, can_message.frame.data4, can_message.frame.data5, can_message.frame.data6, can_message.frame.data7);
            
        }
        
        Delay_ms(1000);
        printf("\r\n\r\n");
        
        
    }
    
    
      
        
}
