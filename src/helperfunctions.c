#include <stdbool.h>
#include "helperfunctions.h"

// FUNCTION DEFINITIONS

// READ REED SWITCH
/* 
Return an int where each bit corresponds to a reed switch being on, ob10000 being the first
note: this is used to verify that the user has the proper pins activated after each mini-game

LOCATION LAYOUT
First Location,  "M"  -->    GPIO PIN B 10
Second Location, "O"  -->    GPIO PIN B 4
Third Location,  "R"  -->    GPIO PIN B 5
Fourth Location, "S"  -->    GPIO PIN B 3
Fifth Location,  "E"  -->    GPIO PIN A 10 
*/
int ReadReed()
{
    int output;
    output = 0;
    if (!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10)) //Check if the first reed switch is activated
    {
        output += 0b10000; 
    }
    if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)) //Check if the second reed switch is activated
    {
        output += 0b1000;
    }
    if (!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)) //Check if the third reed switch is activated
    {
        output += 0b100;
    }
    if (!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3)) //Check if the fourth reed switch is activated
    {
        output += 0b10;
    }    
    if (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10)) //Check if the fifth reed switch is activated
    {
        output += 0b1;
    }    

    return output;
}

// READ JOYSTICK
/* 
Detect whether the direction of an input from the joystick, either left, up, right, or down.
Return a distinct integer value for each of the four possible directions.
note: this is used to determine the attemptive pattern input by the user to compare to the actual pattern. 
*/

int ReadJoystick(ADC_HandleTypeDef *adc)
{
    uint16_t user_y0 = ReadADC(adc, ADC_CHANNEL_0); //up & down
    uint16_t user_x1 = ReadADC(adc, ADC_CHANNEL_1); //left & right
    
    // Check for left
    if (user_x1 > 3800) 
    {
        return 1;
    }
    // Check for right
    else if (user_x1 < 1500) //
    {
        return 3;
    }
    // Check for down
    else if (user_y0 > 3800)
    {
        return 4;
    }
    // Check for up
    else if (user_y0 < 1500) //
    {
        return 2;
    }
    return 0;
}



// PRINT FIRST CHARACTER OF NEXT LOCATION ON 7-SEGMENT DISPLAY
/* GPIO Pin layout
Segment A (TOP) --> B8 --> GPIOB, GPIO_PIN_8;
Segment B (UPPER RIGHT) --> B9 --> GPIOB, GPIO_PIN_9;
Segment C (LOWER RIGHT) --> A5 --> GPIOA, GPIO_PIN_5;
Segment D (BOTTOM) --> A6 --> GPIOA, GPIO_PIN_6;
Segment E (LOWER LEFT) --> A7 --> GPIOA, GPIO_PIN_7;
Segment F (UPPER LEFT) --> B6 --> GPIOB, GPIO_PIN_6;
Segment G (MIDDLE) --> C7 --> GPIOC, GPIO_PIN_7;
*/
void PrintLocation(char location)
{
    // Turn off the previously displayed location letter each time PrintLocation() is called
    // If PrintLocation() is called with an argument that is not one of the valid location character ('O', 'R', 'S', 'E'), display turns off.
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, false); //Top
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, false); //Upper Right
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, false); //Lower Right
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, false); //Bottom
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, false); //Lower Left
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, false); //Upper Left
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, false); //Middle

    if (location == 'O')
    {

        //print O
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, true); //Top
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, true); //Upper Right
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, true); //Lower Right
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, true); //Bottom
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, true); //Lower Left
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, true); //Upper Left
    }

    if (location == 'R')
    {
        //print r
        HAL_GPIO_WritePin( GPIOA, GPIO_PIN_7, true); //Lower Left
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, true); //Middle
    }

    if (location == 'S')
    {
        //print 5
        
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, true); //Top
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, true); //Lower Right
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, true); //Bottom
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, true); //Upper Left
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, true); //Middle   
    }
    
    if (location == 'E')
    {
        //print E
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, true); //Top
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, true); //Bottom
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, true); //Lower Left
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, true); //Upper Left
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, true); //Middle
    }
}

// READ PHOTO RESISTOR
// Read the photoresistor voltage value
uint16_t ReadPhotoResistor(ADC_HandleTypeDef *adc)
{
    return ReadADC(adc, ADC_CHANNEL_4); 
}

// CHECK AND COMPARE PHOTO RESISTOR VALUES
// Compare the recorded room brightness with the current brightness.
// Checks if there is a significant voltage increase, indicating a flashed light
bool CheckPhotoResistor(uint16_t RoomBrightness, ADC_HandleTypeDef *adc)
{
    if ((ReadPhotoResistor(adc) - RoomBrightness) >= 300)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

