#include "morse.h"
#include "ece198.h"
#include "led.h"
#include "helperfunctions.h"

//function exits once player has correctly entered the morse code pattern using the flashlight
void Morse(){
    //0 is a dot, 1 is a dash
    int E7[6] = {0,1,1,0,0,0};
    //read the inital britness to allow the check for the flashlight being on
    uint16_t RoomBrightness = ReadPhotoResistor(); 

    Reset_LED();
    Set_LED(61, 255, 255, 255);
    WS2812_Send();

    int i = 0;
    while(i < 6){
        uint32_t Diff = 0;

        //record when they turn the flashlight on
        while (!CheckPhotoResistor(RoomBrightness)){}
        Diff = HAL_GetTick();      

        //record when they turn the flashlight off and calculate whether it was a dot or dash 
        while(CheckPhotoResistor(RoomBrightness)){}
        Diff = HAL_GetTick() - Diff;
        uint8_t code = (Diff > 400);
        

        // if they gave the wrong symbol start again 
        if (!(code == E7[i])){
            SetLEDSide(5,255,0,0);
            WS2812_Send();
            HAL_Delay(100);
            Reset_LED();
            Set_LED(61, 255, 255, 255);
            WS2812_Send();
            i = 0;
        } else if (i != 5) {
            Reset_LED();
            for(int j=0; j <= i ; ++j ){
                SetMorsePosition(j,0,255,0);
            }
            Set_LED(61, 255, 255, 255);
            for(int j=0; j < Diff/50; ++j ){
                Set_LED(j,0,0,255);
            }
            WS2812_Send();
            ++i;
        } else {
            ++i;
        }
    }
}
