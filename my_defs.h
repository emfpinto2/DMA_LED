
// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H


#include <xc.h> // include processor files - each processor file is guarded. 
#include <stdbool.h> 
#include <stdint.h> 
#include "mcc_generated_files/mcc.h"

#define ON  1
#define OFF 0
#define TRUE 1
#define FALSE 0
#define RED 1
#define GREEN 0
#define BLUE 2


#define PLAYER_NUMBER 2     //Colocar aqui o numero do jogador
#define MATRIX_Z          //Descomentar para usar a matriz 16x16
#define LED_COUNT_X 16
#define LED_COUNT_Y 16
#define TOTAL_LEDS LED_COUNT_X*LED_COUNT_Y

#define BALL_INITIAL_DIR 0  // Direcção inicial da bola. 0 para baixo (0 a 7 predefinidas). Maior que 7, pseudo-aleatorio baseado no ocntador cents_since_start
#define BALL_INITIAL_POSX LED_COUNT_X/2
#define BALL_INITIAL_POSY LED_COUNT_Y/2


#define BALL_GAME_SPEED 10       // nem centesimas de s - Não meter menor que o MATRIX_REFRESH_RATE senão n se consegue ver a bola
#define KEY_SPEED BALL_GAME_SPEED/2
#define MATRIX_REFRESH_RATE 1     //In 10ms (5 = 50ms = 20Hz))
#define COLOR_PLAYER1_R 25
#define COLOR_PLAYER1_G 1
#define COLOR_PLAYER1_B 1
#define COLOR_PLAYER2_R 1
#define COLOR_PLAYER2_G 25
#define COLOR_PLAYER2_B 1
#define COLOR_PLAYER3_R 1
#define COLOR_PLAYER3_G 1
#define COLOR_PLAYER3_B 25
#define COLOR_PLAYER4_R 25
#define COLOR_PLAYER4_G 25
#define COLOR_PLAYER4_B 1
#define COLOR_BALL_R    20
#define COLOR_BALL_G    20
#define COLOR_BALL_B    20

#define BACKGROUND_RED   0
#define BACKGROUND_GREEN 0
#define BACKGROUND_BLUE  2

#define MAX_INTENSITY_RED   50
#define MAX_INTENSITY_GREEN 50
#define MAX_INTENSITY_BLUE  50


#define UART1_TX_BUFFER_SIZE 80
#define UART1_RX_BUFFER_SIZE 80
#define UART2_TX_BUFFER_SIZE 80
#define UART2_RX_BUFFER_SIZE 80

enum CAN_MSGs{
    START_GAME_CAN_MSG=1,
    STOP_GAME_CAN_MSG,
    GAME_UPDATE_PLAYER_CAN_MSG,
    GAME_UPDATE_BALL_CAN_MSG
    
};


typedef  struct {
    uint8_t sourceID;       // 5 bits - 28...24
    uint8_t targetID;       // 5 bits - 23...19
    uint8_t instruction;    // 3 bits - 18...16
    uint8_t index;          // 8 bits - 15...8
    uint8_t subindex;       // 8 bits - 7...0
    
} STRUCT_AF;




// File sound.c
void Teste_sound(void);
void Sound(uint8_t freq, uint8_t status);
void Beep(uint16_t duration);
void Beep_reset(void);
void Beep_loose(void);



// File utils.c
void Delay_us(uint16_t us);
void Delay_ms(uint16_t ms);

// File  WS2812.c
void MMA8652_init(void);
void ws2812_send(uint8_t red, uint8_t green, uint8_t blue);
void ws2812_send_SPI(uint8_t red, uint8_t green, uint8_t blue);
void read_ID_MMA8852(void);
void led_update(void);
void led_initialize(void);
void basic_test_ws2812_bits(void);
void basic_test_ws2812(void);
void fill_matrix_16x16(uint8_t red, uint8_t green, uint8_t blue);

// File my_spi.c
void my_SPI1_WriteByte(uint8_t byte);
void my_SPI1_WriteWord(uint8_t byteH, uint8_t byteL);
uint8_t my_SPI1_ReadByte(void);
void my_SPI1_Initialize(void);

// File my_dma1.c
void my_DMA1_Initialize(void);

// File my_dma2.c
void Matrix_fill_background(void);
void Matrix_fill_RGB(uint8_t red, uint8_t green, uint8_t blue);

//Em teste... Preenchimento de memória usando o DMA2 channel. Ver comentários em my_DMA2_Initialize
void Matrix_fill_DMA2(uint8_t red, uint8_t green, uint8_t blue);
void my_DMA2_Initialize(void);
void Show_buffers(void);

//File game.c
void Game_play(void);

//File parser_can.c
uint8_t CAN_receive_msg(void);
uint8_t CAN_send_start_msg(void);
uint8_t CAN_send_stop_msg(void);
uint8_t CAN_send_player_moved_msg(uint8_t player_posx, uint8_t player_posy);
uint8_t CAN_send_ball_moved_msg(void);


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

