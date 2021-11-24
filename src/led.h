#include "stm32f4xx_hal.h"

#define MAX_LED 180
#define USE_BRIGHTNESS 0


void Set_LED (int LEDnum, int Red, int Green, int Blue);
void Set_Brightness (int brightness);
void WS2812_Send (void);
void Reset_LED (void);

uint8_t LED_Data[MAX_LED][4];
uint8_t LED_Mod[MAX_LED][4];  // for brightness
uint16_t pwmData[(24*MAX_LED)+50];

// below is not from drivers //

void SetLEDSide(int LEDside, int Red, int Green, int Blue );
void SetGuitarHeroPosition(int position,  int Red, int Green, int Blue );
void SetMorsePosition(int position,  int Red, int Green, int Blue );