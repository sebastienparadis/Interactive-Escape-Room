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
    int GuitarHeroGameInstancePoints[20];
    for(int i = 0; i < 20; ++i){
        TotalPosition -= ((rand() % 10) + 1);
        GuitarHeroGameInstancePoints[i] = TotalPosition;
    }
    int GameTime = -TotalPosition*GuitarHeroGameSpeed;
    TIM2_Init(GuitarHeroGameSpeed);

    while(!won){
        for(int i = 0; i < 20; ++i){
            GuitarHeroPoints[i] = GuitarHeroGameInstancePoints[i];
        }
        GuitarHeroStartTime = HAL_GetTick();
        TIM2_Start();

        while(GuitarHeroStartTime + GameTime > HAL_GetTick()){
            while(!ReadJoystick()){}
            int CurrentPosition = (HAL_GetTick()-GuitarHeroStartTime)/GuitarHeroGameSpeed;
            for(int i = 0; i < 20; ++i){
                if(GuitarHeroPoints[i] + CurrentPosition == 44){
                    GuitarHeroPoints[i] = 0;
                } else if(GuitarHeroPoints[i] + CurrentPosition < 44){
                    break;
                }
            }
            while(ReadJoystick()){}
        }
        int miss = 0;
        for (int i = 0; i < 20; ++i){
            if(GuitarHeroPoints[i]){
                ++miss;
            }
        }
        if (miss<5){
            won = true;
        }
    }
    
}

void MoveGuitarHeroPoints(){
    int CurrentPosition = (HAL_GetTick()-GuitarHeroStartTime)/GuitarHeroGameSpeed;
    Reset_LED();
    for(int i = 0; i < 20; ++i){
        int position = GuitarHeroPoints[i] + CurrentPosition;
        if(position < 0){
            break;
        } else if (position < 45) {
            SetGuitarHeroPosition(position, 255, 0 , 0);
        }
    }
}