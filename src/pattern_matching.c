#include "pattern_matching.h"
#include "ece198.h"
#include <stdbool.h>



void PatternGame(int length, int delay)
{
    int pattern_game[length];
    // Initialize the respective sequence with the LED ranges for the left, up, right, and down sides of the board
    for (int i=0; i < length; i++)
        {
            pattern_game[i] = ((rand()%4) + 1); // "rand()%4 + 1" selects a random integer between 1, 2, 3, and 4.
        }    

    bool won = false;
    while (!won) {
        //output the pattern
        for (int i = 0; i < length; ++i)
        {
            // Output the light sequence, flashing in the sequence order on the appropriate sides of the board
            SetLEDSide(pattern_game[i], 0, 0, 255);
            WS2812_Send();
            HAL_DELAY(delay);
        }
        
        int user_trial[length];
        for (int i = 0; i<length; ++i)
            {
                while (!ReadJoystick()){}
                user_trial[i] = ReadJoystick();
                SetLEDSide(user_trial[i], 0, 0, 255);
                WS2812_Send();
                while(ReadJoystick()){}

            }

        //check for the pattern
        //If its the right pattern, end. If it is not, output again and check again.
        won = true;
        for (int i = 0; i < length; ++i)
        {
            if (user_trial[i] != pattern_game[i])
            {
                won = false;
                break;
            }
            
        }
        if (!won){
            SetLEDSide(5, 255, 0, 0); // 
            WS2812_Send();
            HAL_Delay(500);
            SetLEDSide(5, 0,0,0);
            WS2812_Send();
            HAL_Delay(500);
        }
    }
}

