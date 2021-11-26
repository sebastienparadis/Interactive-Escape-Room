#include "reaction_time.h"
#include "helperfunctions.h"
#include <stdlib.h>
#include "main.h"

void ReactionTimeGame()
{
    int flash_time = 0;
    int input_time = 0;
    int success_count = 0;
    bool won = false;

    while (won == false)
    {   
     
        // Delay a random amount of time from 2 to 10 seconds
        HAL_Delay(400*((rand()%9)+2)); 
        // Checks if  user is holding down joystick before the flash     
        while(ReadJoystick())
        {/* Do nothing */} 
        
        // Set LED's to flash in white on all four sides
        SetLEDSide(5, 255, 0, 0); 
        WS2812_Send(); 
        // Record time at which the light flashes to  user
        flash_time = HAL_GetTick(); 
        HAL_Delay(100);
        Reset_LED();
        WS2812_Send();
        // Wait until the user interacts with the joystick to record user input time
        while (!ReadJoystick()) 
        {/* Do nothing */}

        // Record time at which the user reacts 
        input_time = HAL_GetTick(); 

        // Wait until the joystick goes back to a neutral position
        while(ReadJoystick())
        {/* Do nothing */}
        
        if ((input_time - flash_time) <= 150) // Calculate reaction time, and check if it is fast enough
        {
            success_count++; // Record the users success
        } else {
        }

        if (success_count == 3) // Once the user has reacted quick enough a total of 3 times, they have won
        {
            won = true;
        }
    }
}