#include "morse.h"
#include "ece198.h"
#include <stdio.h>

//function exits once player has correctly entered the morse code pattern using the flashlight
void Morse(){
    __HAL_RCC_ADC1_CLK_ENABLE();        // enable ADC 1
    ADC_HandleTypeDef adcInstance; // this variable stores an instance of the ADC
    InitializeADC(&adcInstance, ADC1);  // initialize the ADC instance
    InitializePin(GPIOA, GPIO_PIN_0 | GPIO_PIN_4 , GPIO_MODE_ANALOG, GPIO_NOPULL, 0);

    //0 is a dot, 1 is a dash
    int E7[6] = {0,1,1,0,0,0};
    //read the inital britness to allow the check for the flashlight being on
    uint16_t RoomBrightness = ReadPhotoResistor(&adcInstance); 

    for(int i = 0; i < 6; ++i){
        uint32_t Diff = 0;

        //record when they turn the flashlight on
        while (!CheckPhotoResistor(RoomBrightness, &adcInstance)){}
        Diff = HAL_GetTick();

        //record when they turn the flashlight off and calculate whether it was a dot or dash 
        while(CheckPhotoResistor(RoomBrightness/* , &adcInstance */)){}
        Diff = HAL_GetTick() - Diff;
        uint8_t code = Diff > 200 ? 1 : 0;

        
        // if they gave the wrong symbol start again 
        if (!(code == E7[i])){
            i = -1;
        } 
    }
}
