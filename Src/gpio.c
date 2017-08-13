/**
  ******************************************************************************
  * File Name          : gpio.c
  * Description        : This file provides code for the configuration
  *                      of all used GPIO pins.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"
/* USER CODE BEGIN 0 */

#define CMD_DEBUG 1

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/*
Defination                 Pin
------------|-----------|------
delay_stop    --------     PA1
stop          --------     PA2
warn_led      --------     PA3
start         --------     PA4
power_off     --------     PA5
front_led     --------     PA7
back_led      --------     PB5
go_head       --------     PB7
go_back       --------     PB8
horn          --------     PB9
system_on     --------     PB12
transmission_state  --     PB13
emergency_stop   -----     PB14
---------------------------------
*/
/* USER CODE END 1 */

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, delay_stop_Pin|stop_Pin|warn_led_Pin|start_Pin 
                          |power_off_Pin|front_led_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, system_on_Pin|transmission_state_Pin|emergency_stop_Pin|back_led_Pin 
                          |go_head_Pin|go_back_Pin|horn_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PAPin PAPin PAPin PAPin 
                           PAPin PAPin */
  GPIO_InitStruct.Pin = delay_stop_Pin|stop_Pin|warn_led_Pin|start_Pin 
                          |power_off_Pin|front_led_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin PBPin PBPin 
                           PBPin PBPin PBPin */
  GPIO_InitStruct.Pin = system_on_Pin|transmission_state_Pin|emergency_stop_Pin|back_led_Pin 
                          |go_head_Pin|go_back_Pin|horn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */

void delay_stop(bool state)
{
	if(state) 
		HAL_GPIO_WritePin(GPIOA, delay_stop_Pin, GPIO_PIN_SET);
	else 
		HAL_GPIO_WritePin(GPIOA, delay_stop_Pin, GPIO_PIN_RESET);
#if CMD_DEBUG
	printf("delay_stop(%d)\n", (int)state);
#endif
}

void stop(bool state)
{
	if(state) 
		HAL_GPIO_WritePin(GPIOA, stop_Pin, GPIO_PIN_SET);
	else 
		HAL_GPIO_WritePin(GPIOA, stop_Pin, GPIO_PIN_RESET);
#if CMD_DEBUG
	printf("stop(%d)\n", (int)state);
#endif
}

void warn_led(bool state)
{
	if(state) 
		HAL_GPIO_WritePin(GPIOA, warn_led_Pin, GPIO_PIN_SET);
	else 
		HAL_GPIO_WritePin(GPIOA, warn_led_Pin, GPIO_PIN_RESET);
#if CMD_DEBUG
	printf("warn_led(%d)\n", (int)state);
#endif
}

void start(bool state)
{
	if(state) 
		HAL_GPIO_WritePin(GPIOA, start_Pin, GPIO_PIN_SET);
	else 
		HAL_GPIO_WritePin(GPIOA, start_Pin, GPIO_PIN_RESET);
#if CMD_DEBUG
	printf("start(%d)\n", (int)state);
#endif
}

void power_off(bool state)
{
	if(state) 
		HAL_GPIO_WritePin(GPIOA, power_off_Pin, GPIO_PIN_SET);
	else 
		HAL_GPIO_WritePin(GPIOA, power_off_Pin, GPIO_PIN_RESET);
#if CMD_DEBUG
	printf("power_off(%d)\n", (int)state);
#endif
}

void front_led(bool state)
{
	if(state) 
		HAL_GPIO_WritePin(GPIOA, front_led_Pin, GPIO_PIN_SET);
	else 
		HAL_GPIO_WritePin(GPIOA, front_led_Pin, GPIO_PIN_RESET);
#if CMD_DEBUG
	printf("front_led(%d)\n", (int)state);
#endif
}

void back_led(bool state)
{
	if(state)
		HAL_GPIO_WritePin(GPIOB, back_led_Pin, GPIO_PIN_SET);
	else 
		HAL_GPIO_WritePin(GPIOB, back_led_Pin, GPIO_PIN_RESET);
#if CMD_DEBUG
	printf("back_led(%d)\n", (int)state);
#endif
}

void go_head(bool state)
{
	if(state)
		HAL_GPIO_WritePin(GPIOB, go_head_Pin, GPIO_PIN_SET);
	else 
		HAL_GPIO_WritePin(GPIOB, go_head_Pin, GPIO_PIN_RESET);
#if CMD_DEBUG
	printf("go_head(%d)\n", (int)state);
#endif
}

void go_back(bool state)
{
	if(state)
		HAL_GPIO_WritePin(GPIOB, go_back_Pin, GPIO_PIN_SET);
	else 
		HAL_GPIO_WritePin(GPIOB, go_back_Pin, GPIO_PIN_RESET);
#if CMD_DEBUG
	printf("go_back(%d)\n", (int)state);
#endif
}

void horn(bool state)
{
	if(state)
		HAL_GPIO_WritePin(GPIOB, horn_Pin, GPIO_PIN_SET);
	else 
		HAL_GPIO_WritePin(GPIOB, horn_Pin, GPIO_PIN_RESET);
#if CMD_DEBUG
	printf("horn(%d)\n", (int)state);
#endif
}

void system_on(bool state)
{
	if(state)
		HAL_GPIO_WritePin(GPIOB, system_on_Pin, GPIO_PIN_SET);
	else 
		HAL_GPIO_WritePin(GPIOB, system_on_Pin, GPIO_PIN_RESET);
#if CMD_DEBUG
	printf("system_on(%d)\n", (int)state);
#endif
}

void transmission_state(bool state)
{
	if(state)
		HAL_GPIO_WritePin(GPIOB, transmission_state_Pin, GPIO_PIN_SET);
	else 
		HAL_GPIO_WritePin(GPIOB, transmission_state_Pin, GPIO_PIN_RESET);
#if CMD_DEBUG
	printf("transmission_state(%d)\n", (int)state);
#endif
}

void emergency_stop(bool state)
{
	if(state)
		HAL_GPIO_WritePin(GPIOB, emergency_stop_Pin, GPIO_PIN_SET);
	else 
		HAL_GPIO_WritePin(GPIOB, emergency_stop_Pin, GPIO_PIN_RESET);
#if CMD_DEBUG
	printf("emergency_stop(%d)\n", (int)state);
#endif
}

/* USER CODE END 2 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
