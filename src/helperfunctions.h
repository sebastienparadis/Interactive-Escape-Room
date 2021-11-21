#include "ece198.h"
#include <stdbool.h>

//FUNCTION DECLARATIONS

// REED SWITCH //
int ReadReed();

// JOYSTICK //
int ReadJoystick(ADC_HandleTypeDef *adc);

// 7-SEGMENT DISPLAY //
void PrintLocation(char location);

// PHOTO RESISTOR //
uint16_t ReadPhotoResistor(ADC_HandleTypeDef *adc); 
bool CheckPhotoResistor(uint16_t RoomBrightness, ADC_HandleTypeDef *adc);
