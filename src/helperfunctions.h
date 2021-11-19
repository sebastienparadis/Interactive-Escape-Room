#include "ece198.h"
#include <stdbool.h>

//Function Declarations
int ReadReed();
int ReadJoystick(ADC_HandleTypeDef *adc);
uint16_t ReadPhotoResistor(); //uint16_t CheckPhotoResistor(uint16_t RoomBrightness);
void PrintLocation(char location);