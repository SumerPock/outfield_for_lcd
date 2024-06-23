/**
  ******************************************************************************
  * File Name          : dma.c
  * Description        : This file provides code for the configuration
  *                      of all the requested memory to memory DMA transfers.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "bsp_dma.h"

/*
*********************************************************************************************************
*	�� �� ��: MX_DMA_Init
*	����˵��: 
*	��    ��: ��
*	�� �� ֵ: ��
* �� �� ��:   					
*********************************************************************************************************
*/
void MX_DMA_Init(void)
{
  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();
	__HAL_RCC_DMA1_CLK_ENABLE();
	
  HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 1, 0);	/*USART1RX DMA  */
  HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);
  HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 1, 0);	/*USART1TX DMA  */
  HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);
	
  HAL_NVIC_SetPriority(DMA1_Stream2_IRQn, 0, 0);	/*UART4RX DMA  */
  HAL_NVIC_EnableIRQ(DMA1_Stream2_IRQn);
  HAL_NVIC_SetPriority(DMA1_Stream4_IRQn, 0, 0);	/*UART4TX DMA  */
  HAL_NVIC_EnableIRQ(DMA1_Stream4_IRQn);	
	
	HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 2, 0);	/*UART2RX DMA  */
  HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);
  HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 2, 0);	/*UART2TX DMA  */
  HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);	
	
	HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 3, 0);	/*USART6RX DMA  */
  HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);
  HAL_NVIC_SetPriority(DMA2_Stream6_IRQn, 3, 0);	/*USART6TX DMA  */
  HAL_NVIC_EnableIRQ(DMA2_Stream6_IRQn);	
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
