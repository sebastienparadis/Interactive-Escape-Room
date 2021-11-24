#include "led.h"
#include "main.h"


//lights all the LEDS on a specific side with the specified colour 
//with 1 as left, 2 as top, 3 as right, 4 as bottom, and 5 as the entire boarder anything else resets all the LEDs
void SetLEDSide(int LEDside, int Red, int Green, int Blue ){
    Reset_LED();
    switch(LEDside){
        case 1:
            for(int i = 0; i < 35; ++i){
                Set_LED(i, Red, Green, Blue);
            }
            break;
        case 2:
            for(int i = 35; i < 89; ++i){
                Set_LED(i, Red, Green, Blue);
            }
            break;
        case 3:
            for(int i = 89; i < 125; ++i){
                Set_LED(i, Red, Green, Blue);
            }
            break;
        case 4:
            for(int i = 125; i < 180; ++i){
                Set_LED(i, Red, Green, Blue);
            }
            break;
        case 5:
            for(int i = 0; i < 180; ++i){
                Set_LED(i, Red, Green, Blue);
            }
            break;
    }
}

//sets the LEDs in the guitar hero map position specified to the specified colour
void SetGuitarHeroPosition(int position,  int Red, int Green, int Blue ){
    //62.5th is the center led on the top we will send LEDs out around and down from this position so one starts
    //at the 62nd (index 61) and goes backward and one starts at 63rd (index 62) and goes forward we will send them
    // as pairs with a leading lit led and a trailing unlit led so the backward led will start at index 60 and
    // the forward led will start at index 63 both lights will move by 2
    if(position < 45){   
        Set_LED(60 - 2*position > 0 ? 60 - 2*position : 60 - 2*position + 180, Red, Green, Blue);
        Set_LED(62 + 2*position, Red, Green, Blue);
    }
    if(position == 44){
        Set_LED(151, Red, Green, Blue);
    }
} 


//sets the LEDs in the morse map position specified to the specified colour
void SetMorsePosition(int position,  int Red, int Green, int Blue ){
    //62.5th is the center led on the top we will send LEDs out from there to show the user whether they are correctly
	// inputing the morse code
    Set_LED(60 - position, Red, Green, Blue);
    Set_LED(62 + position, Red, Green, Blue);
} 

//all code below this point is part of the LED drivers taken from https://controllerstech.com/interface-ws2812-with-stm32/ 

void Set_LED (int LEDnum, int Red, int Green, int Blue)
{
	LED_Data[LEDnum][0] = LEDnum;
	LED_Data[LEDnum][1] = Green;
	LED_Data[LEDnum][2] = Red;
	LED_Data[LEDnum][3] = Blue;
}


void Set_Brightness (int brightness)  // 0-45
{
#if USE_BRIGHTNESS

	if (brightness > 45) brightness = 45;
	for (int i=0; i<MAX_LED; i++)
	{
		LED_Mod[i][0] = LED_Data[i][0];
		for (int j=1; j<4; j++)
		{
			float angle = 90-brightness;  // in degrees
			angle = angle*PI / 180;  // in rad
			LED_Mod[i][j] = (LED_Data[i][j])/(tan(angle));
		}
	}

#endif

}



void WS2812_Send (void)
{
	uint32_t indx=0;
	uint32_t color;


	for (int i= 0; i<MAX_LED; i++)
	{
#if USE_BRIGHTNESS
		color = ((LED_Mod[i][1]<<16) | (LED_Mod[i][2]<<8) | (LED_Mod[i][3]));
#else
		color = ((LED_Data[i][1]<<16) | (LED_Data[i][2]<<8) | (LED_Data[i][3]));
#endif

		for (int i=23; i>=0; i--)
		{
			if (color&(1<<i))
			{
				pwmData[indx] = 60;  // 2/3 of 90
			}

			else pwmData[indx] = 30;  // 1/3 of 90

			indx++;
		}

	}

	for (int i=0; i<50; i++)
	{
		pwmData[indx] = 0;
		indx++;
	}

	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)pwmData, indx);
	//while (!datasentflag){};
	//datasentflag = 0;
}

void Reset_LED (void)
{
	for (int i=0; i<MAX_LED; i++)
	{
		LED_Data[i][0] = i;
		LED_Data[i][1] = 0;
		LED_Data[i][2] = 0;
		LED_Data[i][3] = 0;
	}
}