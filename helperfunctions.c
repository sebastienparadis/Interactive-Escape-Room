#include <stdbool.h>
#include "helperfunctions.h"
// SIDES OF BOARD
// Defining the LED ranges and their board sides







// Read Reed Switches

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
    
    if (!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4))
    {
        output += 0b1000;
    }

    if (!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5))
    {
        output += 0b100;
    }
    
    if (!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3))
    {
        output += 0b10;
    }    

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

void PrintLocation(char n)
{
   
    if (n = 'O')
    {
        //print 0
    }
    if (n = 'R')
    {
        //print R
    }
    if (n = 'S')
    {
        //print 5
    }
    if (n = 'E')
    {
        //print E
    }
}