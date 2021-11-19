/*#include "morse.h"
#include "ece198.h"

//function exits once player has correctly entered the morse code pattern using the flashlight
void Morse(){
    //0 is a dot, 1 is a dash
    int E7[6] = {0,1,1,0,0,0};
    //read the inital britness to allow the check for the flashlight being on
    uint16_t RoomBrightness = ReadPhotoResistor(); 

    for(int i = 0; i < 6; ++i){
        uint32_t Diff = 0;

        //record when they turn the flashlight on
        while (!CheckPhotoResistor(RoomBrightness)){}
        Diff = HAL_GetTick();

        //record when they turn the flashlight off and calculate whether it was a dot or dash 
        while(CheckPhotoResistor(RoomBrightness)){}
        Diff = HAL_GetTick() - Diff;
        uint8_t code = Diff > 200 ? 1 : 0;

        // if they gave the wrong symbol start again 
        if (!(code == E7[i])){
            i = -1;
        } 
    }
}
*/