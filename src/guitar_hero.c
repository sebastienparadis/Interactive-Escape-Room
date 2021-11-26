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
    bool hits[GuitarHeroGameLength];
    for(int i = 0; i < GuitarHeroGameLength; ++i){
        TotalPosition -= ((rand() % 10) + 1);
        GuitarHeroPoints[i] = TotalPosition;
        hits[i] = false;
    }
    int GameTime = -TotalPosition*(GuitarHeroGameSpeed+(GuitarHeroGameSpeed/5));
    TIM2_Init(GuitarHeroGameSpeed);

    while(!won){
        GuitarHeroStartTime = HAL_GetTick();
        TIM2_Start();
        int hit = 0;
        int press = 0;
        while(GuitarHeroStartTime + GameTime > HAL_GetTick()){
            while(!ReadJoystick()){}
            ++press;
            if(press > 25){
                break;
            }
            int CurrentPosition = (HAL_GetTick()-GuitarHeroStartTime)/GuitarHeroGameSpeed;
            for(int i = 0; i < GuitarHeroGameLength; ++i){
                if(GuitarHeroPoints[i] + CurrentPosition + 1 == 44 || GuitarHeroPoints[i] + CurrentPosition == 44 || GuitarHeroPoints[i] + CurrentPosition - 1 == 44){
                    hits[i] = true;
                    SetGuitarHeroPosition(44,0,255,0);
                } else if(GuitarHeroPoints[i] + CurrentPosition < 44){
                    break;
                }
            }  
            while(ReadJoystick()){}
        }

        for (int i = 0; i < GuitarHeroGameLength; ++i){
            if(hits[i]){
                ++hit;
            }
        }
        if (hit>GuitarHeroGameLength/2){
            won = true;
        }
        TIM2_Stop();
        Reset_LED();
        for(int i = 0; i < hit; ++i){
            Set_LED(i, 0, 0, 255);
        }
        WS2812_Send();
        HAL_Delay(2000);
    }
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