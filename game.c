#include"my_defs.h"


extern uint8_t Game_array[LED_COUNT_Y][LED_COUNT_X][3];
extern uint8_t Video_array[LED_COUNT_Y][LED_COUNT_X][3];
extern void (*putch_uartfunction_ptr)(uint8_t);
uint8_t player_number=PLAYER_NUMBER;
extern uint32_t cents_since_start;
extern uCAN_MSG  can_message;
extern STRUCT_AF can_arbitrationID;

/* POSICOES DOS PLAYERS NA MATRIZ*/        
/*
         P L A Y E R 3
P                           P  
L                           L
A                           A
Y                           Y
E                           E
R                           R
4                           2
        P L A Y E R 1
  
       2
       |
  3<-     ->1 
       |
       0
 
 */      
        
        
uint8_t coords_inc[4][2]= {
    {1,0},
    {0,1},
    {1,0},
    {0,1}        
};

uint8_t player1_posx,player1_posy;
uint8_t player2_posx,player2_posy;
uint8_t player3_posx,player3_posy;
uint8_t player4_posx,player4_posy;
uint8_t ball_posx,ball_posy;
uint8_t ball_dir=3;
uint8_t player1_ncatches,player2_ncatches,player3_ncatches,player4_ncatches;


void Init_player_ball_positions(void) {
    player1_posx=LED_COUNT_X/2; player1_posy=0;
    player2_posx=LED_COUNT_X-1; player2_posy=LED_COUNT_Y/2;
    player3_posx=LED_COUNT_X/2; player3_posy=LED_COUNT_Y-1;
    player4_posx=0; player4_posy=LED_COUNT_Y/2;

#if BALL_INITIAL_DIR>=0 && BALL_INITIAL_DIR<=7
    ball_dir=BALL_INITIAL_DIR;  
#else
    ball_dir=(uint8_t)(cents_since_start&0x07); //Usa o contador de centesimos desde que o MCU fez reset para dar um numero pseudo-aleatório
#endif    
    
    ball_posx=BALL_INITIAL_POSX; ball_posy=BALL_INITIAL_POSY;
    
}



// COpiar o array Game_array para o "video buffer"
//Se a matriz estiver organizada em "Z" é preciso inverter as linhas impares
void Copy_game_array_to_video_buffer(void) {    
    

    for(uint8_t y=0; y<LED_COUNT_Y;y++) {

#ifdef MATRIX_Z
        if (y&0x01)
            for(uint8_t x=0;x<LED_COUNT_X;x++) {
                Video_array[y][x][RED]   = Game_array[y][LED_COUNT_X-1-x][RED];
                Video_array[y][x][GREEN] = Game_array[y][LED_COUNT_X-1-x][GREEN];
                Video_array[y][x][BLUE]  = Game_array[y][LED_COUNT_X-1-x][BLUE];
            }
        else
            for(uint8_t x=0;x<LED_COUNT_X;x++) {
                Video_array[y][x][RED]   = Game_array[y][x][RED];
                Video_array[y][x][GREEN] = Game_array[y][x][GREEN];
                Video_array[y][x][BLUE]  = Game_array[y][x][BLUE];
            }
            
#else
        for(uint8_t x=0;x<LED_COUNT_X;x++) {
            Video_array[y][x][RED]   = Game_array[y][x][RED];
            Video_array[y][x][GREEN] = Game_array[y][x][GREEN];
            Video_array[y][x][BLUE]  = Game_array[y][x][BLUE];
        }    
#endif
    }

}


void Fade_in(void) {
uint8_t i,x,y,max_colour;

    max_colour=0;
    for (y=0; y<LED_COUNT_Y; y++) {
        for (x=0; x<LED_COUNT_X; x++) {
            if (Game_array[y][x][RED] > max_colour)
                max_colour=Game_array[y][x][RED];
            if (Game_array[y][x][GREEN] > max_colour)
                max_colour=Game_array[y][x][GREEN];
            if (Game_array[y][x][BLUE] > max_colour)
                max_colour=Game_array[y][x][BLUE];
            Video_array[y][x][RED]=0;
            Video_array[y][x][GREEN]=0;
            Video_array[y][x][BLUE]=0;
        }
    }
    Delay_ms(500);
    
    for(i=0;i<max_colour;i++) {
        for (y=0; y<LED_COUNT_Y; y++) {
            
#ifdef MATRIX_Z
            if (y&0x01){
                for (x=0; x<LED_COUNT_X; x++) {
                    if (Video_array[y][LED_COUNT_X-1-x][RED]<Game_array[y][x][RED])
                        Video_array[y][LED_COUNT_X-1-x][RED]++;
                    if (Video_array[y][LED_COUNT_X-1-x][GREEN]<Game_array[y][x][GREEN])
                        Video_array[y][LED_COUNT_X-1-x][GREEN]++;
                    if (Video_array[y][LED_COUNT_X-1-x][BLUE]<Game_array[y][x][BLUE])
                        Video_array[y][LED_COUNT_X-1-x][BLUE]++;
                }
            }
            else {
                for (x=0; x<LED_COUNT_X; x++) {
                    if (Video_array[y][x][RED]<Game_array[y][x][RED])
                        Video_array[y][x][RED]++;
                    if (Video_array[y][x][GREEN]<Game_array[y][x][GREEN])
                        Video_array[y][x][GREEN]++;
                    if (Video_array[y][x][BLUE]<Game_array[y][x][BLUE])
                        Video_array[y][x][BLUE]++;
                }
            }    
#else  
            for (x=0; x<LED_COUNT_X; x++) {
                if (Video_array[y][x][RED]<Game_array[y][x][RED])
                    Video_array[y][x][RED]++;
                if (Video_array[y][x][GREEN]<Game_array[y][x][GREEN])
                    Video_array[y][x][GREEN]++;
                if (Video_array[y][x][BLUE]<Game_array[y][x][BLUE])
                    Video_array[y][x][BLUE]++;
            }
#endif    
        }
        Delay_ms(100);
    }
}

void Fade_out(void) {
uint8_t i,x,y,max_colour;

    max_colour=0;
    for (y=0; y<LED_COUNT_Y; y++) {
        for (x=0; x<LED_COUNT_X; x++) {
            if (Video_array[y][x][RED] > max_colour)
                max_colour=Video_array[y][x][RED];
            if (Video_array[y][x][GREEN] > max_colour)
                max_colour=Video_array[y][x][GREEN];
            if (Video_array[y][x][BLUE] > max_colour)
                max_colour=Video_array[y][x][BLUE];
        }    
    }
   // printf("max_colour=%d\r\n",max_colour);
    for(i=0;i<max_colour;i++) {
        for (y=0; y<LED_COUNT_Y; y++) {
            for (x=0; x<LED_COUNT_X; x++) {
                if (Video_array[y][x][RED])
                    Video_array[y][x][RED]--;
                if (Video_array[y][x][GREEN])
                    Video_array[y][x][GREEN]--;
                if (Video_array[y][x][BLUE])
                    Video_array[y][x][BLUE]--;
            }    
        }
        Delay_ms(50);
    }
}



void Update_game_board(void) {
    
    Game_array[ball_posy][ball_posx][RED]=COLOR_BALL_R;
    Game_array[ball_posy][ball_posx][GREEN]=COLOR_BALL_G;
    Game_array[ball_posy][ball_posx][BLUE]=COLOR_BALL_B;

    Game_array[player1_posy][player1_posx-1][RED]=COLOR_PLAYER1_R;
    Game_array[player1_posy][player1_posx-1][GREEN]=COLOR_PLAYER1_G;
    Game_array[player1_posy][player1_posx-1][BLUE]=COLOR_PLAYER1_B;

    Game_array[player1_posy][player1_posx][RED]=COLOR_PLAYER1_R;
    Game_array[player1_posy][player1_posx][GREEN]=COLOR_PLAYER1_G;
    Game_array[player1_posy][player1_posx][BLUE]=COLOR_PLAYER1_B;

    Game_array[player1_posy][player1_posx+1][RED]=COLOR_PLAYER1_R;
    Game_array[player1_posy][player1_posx+1][GREEN]=COLOR_PLAYER1_G;
    Game_array[player1_posy][player1_posx+1][BLUE]=COLOR_PLAYER1_B;

                
    Game_array[player2_posy-1][player2_posx][RED]=COLOR_PLAYER2_R;
    Game_array[player2_posy-1][player2_posx][GREEN]=COLOR_PLAYER2_G;
    Game_array[player2_posy-1][player2_posx][BLUE]=COLOR_PLAYER2_B;

    Game_array[player2_posy][player2_posx][RED]=COLOR_PLAYER2_R;
    Game_array[player2_posy][player2_posx][GREEN]=COLOR_PLAYER2_G;
    Game_array[player2_posy][player2_posx][BLUE]=COLOR_PLAYER2_B;

    Game_array[player2_posy+1][player2_posx][RED]=COLOR_PLAYER2_R;
    Game_array[player2_posy+1][player2_posx][GREEN]=COLOR_PLAYER2_G;
    Game_array[player2_posy+1][player2_posx][BLUE]=COLOR_PLAYER2_B;

                
    Game_array[player3_posy][player3_posx-1][RED]=COLOR_PLAYER3_R;
    Game_array[player3_posy][player3_posx-1][GREEN]=COLOR_PLAYER3_G;
    Game_array[player3_posy][player3_posx-1][BLUE]=COLOR_PLAYER3_B;

    Game_array[player3_posy][player3_posx][RED]=COLOR_PLAYER3_R;
    Game_array[player3_posy][player3_posx][GREEN]=COLOR_PLAYER3_G;
    Game_array[player3_posy][player3_posx][BLUE]=COLOR_PLAYER3_B;

    Game_array[player3_posy][player3_posx+1][RED]=COLOR_PLAYER3_R;
    Game_array[player3_posy][player3_posx+1][GREEN]=COLOR_PLAYER3_G;
    Game_array[player3_posy][player3_posx+1][BLUE]=COLOR_PLAYER3_B;


    Game_array[player4_posy-1][player4_posx][RED]=COLOR_PLAYER4_R;
    Game_array[player4_posy-1][player4_posx][GREEN]=COLOR_PLAYER4_G;
    Game_array[player4_posy-1][player4_posx][BLUE]=COLOR_PLAYER4_B;

    Game_array[player4_posy][player4_posx][RED]=COLOR_PLAYER4_R;
    Game_array[player4_posy][player4_posx][GREEN]=COLOR_PLAYER4_G;
    Game_array[player4_posy][player4_posx][BLUE]=COLOR_PLAYER4_B;

    Game_array[player4_posy+1][player4_posx][RED]=COLOR_PLAYER4_R;
    Game_array[player4_posy+1][player4_posx][GREEN]=COLOR_PLAYER4_G;
    Game_array[player4_posy+1][player4_posx][BLUE]=COLOR_PLAYER4_B;

   
}


 
void Reset_game_display(void) {
uint8_t x,y;


    for (y=0; y<LED_COUNT_Y; y++) {
        for (x=0; x<LED_COUNT_X; x++) {
        
            Game_array[y][x][RED]=BACKGROUND_RED;//(uint8_t)(0x1+i*3);
            Game_array[y][x][GREEN]=BACKGROUND_GREEN;//(uint8_t)(0x2+i*3);
            Game_array[y][x][BLUE]=BACKGROUND_BLUE;//(uint8_t)(0x3+i*3);
        }    
    }
      
    Update_game_board();
    Fade_in();

    
}


void Init_game(void) {
    
    Init_player_ball_positions();
    Reset_game_display();
    
    player1_ncatches=player2_ncatches=player3_ncatches=player4_ncatches=0;
    
       
}
   
//Actualiza a posição da bola, nas variaveis ball_posx, ball_posy, ball_dir
//Devolve o numero do jogador que n apanhou a bola (1 a 4), zero se movimento normal
uint8_t Move_ball(void) {

     Game_array[ball_posy][ball_posx][RED]=BACKGROUND_RED;
    Game_array[ball_posy][ball_posx][GREEN]=BACKGROUND_GREEN;
    Game_array[ball_posy][ball_posx][BLUE]=BACKGROUND_BLUE;

    printf("X=%d Y=%d DIR=%d [%d]\r\n",ball_posx,ball_posy,ball_dir, Game_array[ball_posy][ball_posx][RED]);
    printf("PLAYER1=%d,%d  PLAYER2=%d,%d  PLAYER3=%d,%d  PLAYER4=%d,%d\r\n",player1_posx,player1_posy, player2_posx,player2_posy, player3_posx,player3_posy, player4_posx,player4_posy);                    
    switch(ball_dir) {
        case 0: if (ball_posy==1) {
                     
                    if  (Game_array[ball_posy-1][ball_posx][RED]==BACKGROUND_RED) {
                        ball_posy--;
                        return 1;
                    }
                    else {
                        ball_dir=4;
                        if (ball_posx==player1_posx-1)
                            ball_dir=5;
                        else
                            if (ball_posx==player1_posx+1)
                                ball_dir=3;
                    }
                }
                else
                  ball_posy--;
                break;
                
                
        case 1: if (ball_posx==LED_COUNT_X-2 || ball_posy==1) {
                    if  (Game_array[ball_posy-1][ball_posx+1][RED]==BACKGROUND_RED) {
                        ball_posx++; ball_posy--;
                        if (ball_posx==LED_COUNT_X-2) {
                            return 1;
                        }
                        //else ball_posy==1
                        return 2;    
                    }
                    else {
                        if (ball_posx==LED_COUNT_X-2) {
                            ball_dir=6;
                            if (ball_posy==player2_posy)
                                ball_dir=7;
                            else
                                if (ball_posy==player2_posy-2)
                                    ball_dir=3;
                        }
                        else {  //else ball_posy==1
                            ball_dir=4;
                            if (ball_posx==player1_posx)
                                    ball_dir=3;
                                else
                                    if (ball_posx==player1_posx-2)
                                        ball_dir=5;
                        }
                    }
                }
                else {
                    ball_posx++; 
                    ball_posy--;
                }    
                break;
                
        case 2:if (ball_posx==LED_COUNT_X-2) {
                    if  (Game_array[ball_posy][ball_posx+1][RED]==BACKGROUND_RED) {
                        ball_posx++;
                        return 2;
                    }
                    else {
                        ball_dir=6;
                        if (ball_posy==player2_posy-1)
                            ball_dir=7;
                        else
                            if (ball_posy==player2_posy+1)
                                ball_dir=5;
                    }
                }
                else
                    ball_posx++;
                break;
                

        case 3: if (ball_posx==LED_COUNT_X-2 || ball_posy==LED_COUNT_Y-2) {
                    if  (Game_array[ball_posy+1][ball_posx+1][RED]==BACKGROUND_RED) {
                        ball_posx++; ball_posy++;
                        if (ball_posx==LED_COUNT_X-2) {
                            return 2;
                        }
                        //else ball_posy==LED_COUNT_Y-2
                        return 1;    
                    }
                    else {
                        if (ball_posx==LED_COUNT_X-2) {
                            ball_dir=6;
                            if (ball_posy==player2_posy-2)
                                ball_dir=7;
                            else
                                if (ball_posy==player2_posy)
                                    ball_dir=5;
                        }
                        else {//else ball_posy==LED_COUNT_Y-1
                            ball_dir=0;
                            if (ball_posx==player3_posx-2)
                                    ball_dir=7;
                                else
                                    if (ball_posx==player3_posx)
                                        ball_dir=1;
                        }                        
                    }
                }
                else {
                 ball_posx++; ball_posy++;
               
                }    
                break;


        case 4: if (ball_posy==LED_COUNT_Y-2) {
                    if  (Game_array[ball_posy+1][ball_posx][RED]==BACKGROUND_RED) {
                         ball_posy++;
                        return 1;
                    }
                    else {
                        ball_dir=0;
                        if (ball_posx==player3_posx-1)
                            ball_dir=7;
                        else
                            if (ball_posx==player3_posx+1)
                                ball_dir=1;
                    }
                }
                else
                  ball_posy++;
                break;        
                
                
               
        case 5: if (ball_posx==1 || ball_posy==LED_COUNT_Y-2 ) {
                    if  (Game_array[ball_posy+1][ball_posx-1][RED]==BACKGROUND_RED) {
                        ball_posx--; ball_posy++;
                        if (ball_posx==1) {
                            return 4;
                        }
                        //else ball_posy==LED_COUNT_Y-1
                        return 3;    
                    }
                    else {
                        if (ball_posx==1) {
                            ball_dir=2;
                            if (ball_posy==player4_posy-2)
                                ball_dir=1;
                            else
                                if (ball_posy==player4_posy)
                                    ball_dir=3;
                        }
                        else {//else ball_posy==LED_COUNT_Y-1
                            ball_dir=0;
                            if (ball_posx==player3_posx+2)
                                    ball_dir=1;
                                else
                                    if (ball_posx==player3_posx)
                                        ball_dir=7;
                        }
                    }
                }
                else {
                    ball_posx--; 
                    ball_posy++;
                }    
                break; 
                

        case 6:if (ball_posx==1) {
                    if  (Game_array[ball_posy][ball_posx-1][RED]==BACKGROUND_RED) {
                        ball_posx--;
                        return 4;
                    }
                    else {
                        ball_dir=2;
                        if (ball_posy==player4_posy-1)
                            ball_dir=1;
                        else
                            if (ball_posy==player4_posy+1)
                                ball_dir=3;
                    }
                }
                else
                    ball_posx--;
                break;
                

               
        case 7: if (ball_posx==1 || ball_posy==1) {
                    
                    if  (Game_array[ball_posy-1][ball_posx-1][RED]==BACKGROUND_RED) {
                        ball_posx--; ball_posy--;
                        if (ball_posx==1) {
                            return 4;
                        }
                        //else ball_posy==1
                        return 1;    
                    }
                    else {
                        if (ball_posx==1) {
                            ball_dir=2;
                            if (ball_posy==player4_posy+2)
                                ball_dir=3;
                            else
                                if (ball_posy==player4_posy)
                                    ball_dir=1;
                        }
                        else { //else ball_posy==1
                            ball_dir=4;
                            if (ball_posx==player1_posx+2)
                                    ball_dir=3;
                                else
                                    if (ball_posx==player1_posx)
                                        ball_dir=5;
                        }
                    }
                }
                else {
                    ball_posx--; 
                    ball_posy--;
                }    
                break; 
                
             
    }
    printf("X=%d Y=%d DIR=%d [%d]\r\n\r\n",ball_posx,ball_posy,ball_dir, Game_array[ball_posy][ball_posx][RED]);
    
    return 0;
}

void Check_keys(void) {
uint8_t player_moved=FALSE;

#if PLAYER_NUMBER==1
      if (KEY_RIGHT_GetValue() && player1_posx!=LED_COUNT_X-1-1) {
        Game_array[player1_posy][player1_posx-1][RED]=BACKGROUND_RED;
        Game_array[player1_posy][player1_posx-1][GREEN]=BACKGROUND_GREEN;
        Game_array[player1_posy][player1_posx-1][BLUE]=BACKGROUND_BLUE;
        player1_posx++;
        player_moved=TRUE;
    }    
    
    if (KEY_LEFT_GetValue() && player1_posx!=0+1) {
        Game_array[player1_posy][player1_posx+1][RED]=BACKGROUND_RED;
        Game_array[player1_posy][player1_posx+1][GREEN]=BACKGROUND_GREEN;
        Game_array[player1_posy][player1_posx+1][BLUE]=BACKGROUND_BLUE;
        player1_posx--;
        player_moved=TRUE;
    }
        
    if (player_moved) 
        CAN_send_player_moved_msg(player1_posx,player1_posy);
        
     

#endif
      
#if PLAYER_NUMBER==2
      if (KEY_RIGHT_GetValue() && player2_posy!=LED_COUNT_Y-1-1) {
        Game_array[player2_posy-1][player2_posx][RED]=BACKGROUND_RED;
        Game_array[player2_posy-1][player2_posx][GREEN]=BACKGROUND_GREEN;
        Game_array[player2_posy-1][player2_posx][BLUE]=BACKGROUND_BLUE;
        player2_posy++;
        player_moved=TRUE;
    }    
    
    if (KEY_LEFT_GetValue() && player2_posy!=0+1) {
        Game_array[player2_posy+1][player2_posx][RED]=BACKGROUND_RED;
        Game_array[player2_posy+1][player2_posx][GREEN]=BACKGROUND_GREEN;
        Game_array[player2_posy+1][player2_posx][BLUE]=BACKGROUND_BLUE;
        player2_posy--;
        player_moved=TRUE;
    }
    if (player_moved) 
        CAN_send_player_moved_msg(player2_posx,player2_posy);
 
#endif
      
#if PLAYER_NUMBER==3
      if (KEY_RIGHT_GetValue() && player3_posx!=LED_COUNT_X-1-1) {
        Game_array[player3_posy][player3_posx-1][RED]=BACKGROUND_RED;
        Game_array[player3_posy][player3_posx-1][GREEN]=BACKGROUND_GREEN;
        Game_array[player3_posy][player3_posx-1][BLUE]=BACKGROUND_BLUE;
        player3_posx++;
        player_moved=TRUE;
    }    
    
    if (KEY_LEFT_GetValue() && player3_posx!=0+1) {
        Game_array[player3_posy][player3_posx+1][RED]=BACKGROUND_RED;
        Game_array[player3_posy][player3_posx+1][GREEN]=BACKGROUND_GREEN;
        Game_array[player3_posy][player3_posx+1][BLUE]=BACKGROUND_BLUE;
        player3_posx--;
        player_moved=TRUE;
    }   
    if (player_moved) 
        CAN_send_player_moved_msg(player3_posx,player3_posy);
 
#endif

      
#if PLAYER_NUMBER==4
      if (KEY_RIGHT_GetValue() && player4_posy!=LED_COUNT_Y-1-1) {
        Game_array[player4_posy-1][player4_posx][RED]=BACKGROUND_RED;
        Game_array[player4_posy-1][player4_posx][GREEN]=BACKGROUND_GREEN;
        Game_array[player4_posy-1][player4_posx][BLUE]=BACKGROUND_BLUE;
        player4_posy++;
        player_moved=TRUE;
    }    
    
    if (KEY_LEFT_GetValue() && player4_posy!=0+1) {
        Game_array[player4_posy+1][player4_posx][RED]=BACKGROUND_RED;
        Game_array[player4_posy+1][player4_posx][GREEN]=BACKGROUND_GREEN;
        Game_array[player4_posy+1][player4_posx][BLUE]=BACKGROUND_BLUE;
        player4_posy--;
        player_moved=TRUE;
    }
    if (player_moved) 
        CAN_send_player_moved_msg(player4_posx,player4_posy);
 
#endif
      
      
      
}



        
void Game_play(void) {
uint8_t game_end=FALSE;
uint32_t last_time_move_ball;
uint32_t last_time_key_checked;
uint8_t  ret_can;
    
    putch_uartfunction_ptr=UART1_Write; // Redirecionar o printf para o UART1 (Porta SUB debug da fusion) - Para o módulo BLE usar UART2_Write
    Init_game();
    
    while(TRUE) {
        game_end=FALSE;
        
        printf("Press START KEY\r\n");
        while(!KEY_START_GetValue() && CAN_receive_msg()!=START_GAME_CAN_MSG);
        if (KEY_START_GetValue()) {
            CAN_send_start_msg();
            while(KEY_START_GetValue());
        }
    
        last_time_key_checked=last_time_move_ball=cents_since_start;
        
        printf("GAME STARTED!\r\n");    
    
        while (!game_end && !KEY_START_GetValue()){
            
            if (cents_since_start - last_time_key_checked >= KEY_SPEED) {
                last_time_key_checked=cents_since_start;
                Check_keys();       
            }
            if (player_number==1) { //Only the player 1 sends the update ball can msg
                if (cents_since_start - last_time_move_ball >= BALL_GAME_SPEED)  {
                    last_time_move_ball=cents_since_start;
                    game_end=Move_ball();
                    CAN_send_ball_moved_msg();
               }         
            }
            
            switch(ret_can=CAN_receive_msg()) {
                case 0: break;
                
                case STOP_GAME_CAN_MSG: game_end=TRUE;
                                        break;
                case GAME_UPDATE_PLAYER_CAN_MSG: switch(can_arbitrationID.sourceID) {
                                                    case 1: player1_posx=can_message.frame.data0;
                                                            player1_posy=can_message.frame.data1;
                                                            break;
                                                    case 2: player2_posx=can_message.frame.data0;
                                                            player2_posy=can_message.frame.data1;
                                                            break;
                                                    case 3: player3_posx=can_message.frame.data0;
                                                            player3_posy=can_message.frame.data1;
                                                            break;
                                                    case 4: player4_posx=can_message.frame.data0;
                                                            player4_posy=can_message.frame.data1;
                                                            break;
                                                    default: printf("CAN ERROR player id - sourceID=%d\r\n",can_arbitrationID.sourceID);

                                                }
                                                break;
                    
                GAME_UPDATE_BALL_CAN_MSG: ball_posx=can_message.frame.data0;
                                          ball_posy=can_message.frame.data1;
                                          break;
                                                    
                default: printf("CAN ERROR msg type - ret_can=%d\r\n",ret_can);
              
            }
            
            Update_game_board();
            Copy_game_array_to_video_buffer();

            switch(game_end) {
                case 1: printf("PLAYER1 LOOSES: %d\r\n",++player1_ncatches);
                        Beep_loose();
                        Delay_ms(500);
                        break;
                case 2: printf("PLAYER2 LOOSES: %d\r\n",++player2_ncatches);
                        Beep_loose();
                        Delay_ms(500);
                        break;
                case 3: printf("PLAYER3 LOOSES: %d\r\n",++player3_ncatches);
                        Beep_loose();
                        Delay_ms(500);
                        break;
                case 4: printf("PLAYER4 LOOSES: %d\r\n",++player4_ncatches);
                        Beep_loose();
                        Delay_ms(500);
                        break;
                default: ;        
            }
        
        }
        if (KEY_START_GetValue()) 
            CAN_send_stop_msg();
            
        Fade_out();
        Delay_ms(500);
        Init_player_ball_positions();
        
        Reset_game_display();
       
    }    
    
}


