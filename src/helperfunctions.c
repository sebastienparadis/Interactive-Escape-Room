#include <stdbool.h>
#include "helperfunctions.h"

// Read Reed Switches
// Assigning and returning a corresponding integer value to each reed switch
// When checking if the proper location has been placed, checking to see if the sum of all activated reed switches is appropriate


// First Location, "M" --> GPIO PIN B 10
// Second Location, "O" --> GPIO PIN B 4
// Third Location, "R" --> GPIO PIN B 5
// Fourth Location, "S" --> GPIO PIN B 3
// Fifth Location, "E" --> GPIO PIN A 10

int ReadReed()
{
    int output;
    output = 0;
    //Check if the first reed switch is activated

    if (!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10))
    {
        output += 0b10000;
    }
    
    //Check if the second reed switch is activated

    if (!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4))
    {
        output += 0b1000;
    }

    //Check if the third reed switch is activated


    if (!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5))
    {
        output += 0b100;
    }
    
    //Check if the fourth reed switch is activated

    if (!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3))
    {
        output += 0b10;
    }    

    //Check if the fifth reed switch is activated

    if (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10))
    {
        output += 0b1;
    }    

    return output;
}


// Read Joystick

// Detecting whether the user inputs a left, up, right, or down motion on the joysitck

// if (joystick range > range for motion to left)
//      return 1;

// if (joystick range > range for motion to up)
//      return 2;

// if (joystick range > range for motion to right)
//      return 3;

// if (joystick range > range for motion to down)
//      return 4;

// if (joystick range > or < than range for x and for y)
//      return 5; 
//^^ Ths indicates that it has been pushed in a corner

//Range in the x ---->     LEFT   <--->     RIGHT


int ReadJoystick(ADC_HandleTypeDef *adc)
{
    uint16_t user_x0 = ReadADC(adc, ADC_CHANNEL_0);
    uint16_t user_y1 = ReadADC(adc, ADC_CHANNEL_1);

    //if ( user_x0 > );

    return 0;
}



// Printing the Next Location on the 7-Segment Display

//GPIO Pin layout: 
/*
Segment A (TOP) --> B8 --> GPIOB, GPIO_PIN_8;
Segment B (UPPER RIGHT) --> B9 --> GPIOB, GPIO_PIN_9;
Segment C (LOWER RIGHT) --> A5 --> GPIOA, GPIO_PIN_5;
Segment D (BOTTOM) --> A6 --> GPIOA, GPIO_PIN_6;
Segment E (LOWER LEFT) --> A7 --> GPIOA, GPIO_PIN_7;
Segment F (UPPER LEFT) --> B6 --> GPIOB, GPIO_PIN_6;
Segment G (MIDDLE) --> C7 --> GPIOC, GPIO_PIN_7;


*/

void PrintLocation(char n)
{
   
    if (n = 'O')
    {
        //print O
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, true); //Top
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, true); //Upper Right
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, true); //Lower Right
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, true); //Bottom
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, true); //Lower Left
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, true); //Upper Left

        
    }
    if (n = 'R')
    {
        //print R
        // Print a 0 without the bottom segment
        // all segments except D

        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, true); //Top
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, true); //Upper Right
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, true); //Lower Right
        HAL_GPIO_WritePin( GPIOA, GPIO_PIN_7, true); //Lower Left
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, true); //Upper Left
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, true); //Middle
    }
    if (n = 'S')
    {
        //print 5
        
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, true); //Top
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, true); //Lower Right
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, true); //Bottom
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, true); //Upper Left
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, true); //Middle
        
    }
    if (n = 'E')
    {
        //print E

        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, true); //Top
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, true); //Bottom
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, true); //Lower Left
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, true); //Upper Left
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, true); //Middle

    }
}

