#include "ece198.h"
#include <stdbool.h>

//FUNCTION DECLARATIONS

// REED SWITCH //

int ReadReed();

// JOYSTICK //

int ReadJoystick();

// 7-SEGMENT DISPLAY //

void PrintLocation(char location);

// PHOTO RESISTOR //

uint16_t ReadPhotoResistor(); 
bool CheckPhotoResistor(uint16_t RoomBrightness);

// Timer 2 //

void TIM2_Start(void);
void TIM2_Stop(void);
void TIM2_IRQHandler(void);
