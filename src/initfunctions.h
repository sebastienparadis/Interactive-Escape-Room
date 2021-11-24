#include "stm32f4xx_hal.h"

void TIM2_Init(uint16_t period);

//all code below this point is part of the LED drivers taken from https://controllerstech.com/interface-ws2812-with-stm32/ 
void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_DMA_Init(void);
void MX_TIM1_Init(void);

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim);
