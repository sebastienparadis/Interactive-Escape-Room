#include "guitar_hero.h"
#include "led.h"
#include "main.h"
#include <stdbool.h>
#include "initfunctions.h"
#include "helperfunctions.h"
#include <stdlib.h>

void GuitarHeroGame(void){
    bool won = false;
    int TotalPosition = 0;
    int GuitarHeroGameInstancePoints[GuitarHeroGameLength];
    for(int i = 0; i < GuitarHeroGameLength; ++i){
        TotalPosition -= ((rand() % 10) + 1);
        GuitarHeroGameInstancePoints[i] = TotalPosition;
    }
    int GameTime = -TotalPosition*GuitarHeroGameSpeed;
    TIM2_Init(GuitarHeroGameSpeed);

    while(!won){
        for(int i = 0; i < GuitarHeroGameLength; ++i){
            GuitarHeroPoints[i] = GuitarHeroGameInstancePoints[i];
        }
        GuitarHeroStartTime = HAL_GetTick();
        TIM2_Start();
        int hit = 0;
        while(GuitarHeroStartTime + GameTime > HAL_GetTick()){
            while(!ReadJoystick()){}
            int CurrentPosition = (HAL_GetTick()-GuitarHeroStartTime)/GuitarHeroGameSpeed;
            for(int i = 0; i < GuitarHeroGameLength; ++i){
                if(GuitarHeroPoints[i] + CurrentPosition == 44){
                    GuitarHeroPoints[i] = 0;
                    SetGuitarHeroPosition(44,0,255,0);
                } else if(GuitarHeroPoints[i] + CurrentPosition < 44){
                    break;
                }
            }  
            while(ReadJoystick()){}
        }
        for (int i = 0; i < GuitarHeroGameLength; ++i){
        if(!GuitarHeroPoints[i]){
            ++hit;
            }
        }
        if (hit>10){
            won = true;
        }
    }
    TIM2_Stop();
}

void MoveGuitarHeroPoints(){
    int CurrentPosition = (HAL_GetTick()-GuitarHeroStartTime)/GuitarHeroGameSpeed;
    Reset_LED();
    for(int i = 0; i < GuitarHeroGameLength; ++i){
        int position = GuitarHeroPoints[i] + CurrentPosition;
        if(position < 0){
            break;
        } else if (position < 45) {
            SetGuitarHeroPosition(position, 255, 0 , 0);
        }
    }
}