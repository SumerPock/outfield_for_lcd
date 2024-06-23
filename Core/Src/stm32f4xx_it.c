/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "bsp.h"
#include "stm32f4xx_it.h"

/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  while (1)
  {
  }
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  while (1)
  {
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  while (1)
  {
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  while (1)
  {
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  while (1)
  {
  }
}



/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
}

/*
*********************************************************************************************************
*	�� �� ��: USART1_IRQHandler
*	����˵��: 
*	��    ��: ��
*	�� �� ֵ: ��
* �� �� ��:   					
*********************************************************************************************************
*/
void USART6_IRQHandler(void)
{
  BSP_UART_IDLE_Handler(&husart6);
  HAL_UART_IRQHandler(&husart6);
}

/*
*********************************************************************************************************
*	�� �� ��: USART1_IRQHandler
*	����˵��: 
*	��    ��: ��
*	�� �� ֵ: ��
* �� �� ��:   					
*********************************************************************************************************
*/
void USART1_IRQHandler(void)
{
  BSP_UART_IDLE_Handler(&huart1);
  HAL_UART_IRQHandler(&huart1);
}


/*
*********************************************************************************************************
*	�� �� ��: USART1_IRQHandler
*	����˵��: 
*	��    ��: ��
*	�� �� ֵ: ��
* �� �� ��:   					
*********************************************************************************************************
*/
void USART2_IRQHandler(void)
{
  BSP_UART_IDLE_Handler(&husart2);
  HAL_UART_IRQHandler(&husart2);
}


/*
*********************************************************************************************************
*	�� �� ��: UART4_IRQHandler
*	����˵��: 
*	��    ��: ��
*	�� �� ֵ: ��
* �� �� ��:   					
*********************************************************************************************************
*/
void UART4_IRQHandler(void)
{
  BSP_UART_IDLE_Handler(&huart4);
  HAL_UART_IRQHandler(&huart4);
}


/*
*********************************************************************************************************
*	�� �� ��: DMA1_Stream2_IRQHandler
*	����˵��: 
*	��    ��: ��
*	�� �� ֵ: ��
* �� �� ��:   					
*********************************************************************************************************
*/
void DMA1_Stream2_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&hdma_uart4_rx);
}


/*
*********************************************************************************************************
*	�� �� ��: DMA2_Stream4_IRQHandler
*	����˵��: 
*	��    ��: ��
*	�� �� ֵ: ��
* �� �� ��:   					
*********************************************************************************************************
*/
void DMA2_Stream4_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&hdma_uart4_tx);
}


/*
*********************************************************************************************************
*	�� �� ��: DMA2_Stream2_IRQHandler
*	����˵��: 
*	��    ��: ��
*	�� �� ֵ: ��
* �� �� ��:   					
*********************************************************************************************************
*/
void DMA2_Stream2_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&hdma_usart1_rx);
}

/*
*********************************************************************************************************
*	�� �� ��: DMA2_Stream7_IRQHandler
*	����˵��: 
*	��    ��: ��
*	�� �� ֵ: ��
* �� �� ��:   					
*********************************************************************************************************
*/
void DMA2_Stream7_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&hdma_usart1_tx);
}

/*
*********************************************************************************************************
*	�� �� ��: DMA2_Stream6_IRQHandler
*	����˵��: 
*	��    ��: ��
*	�� �� ֵ: ��
* �� �� ��:   					
*********************************************************************************************************
*/
void DMA2_Stream6_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&hdma_usart6_tx);
}

/*
*********************************************************************************************************
*	�� �� ��: DMA2_Stream1_IRQHandler
*	����˵��: 
*	��    ��: ��
*	�� �� ֵ: ��
* �� �� ��:   					
*********************************************************************************************************
*/
void DMA2_Stream1_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&hdma_usart6_rx);
}


/*
*********************************************************************************************************
*	�� �� ��: DMA1_Stream5_IRQHandler
*	����˵��: 
*	��    ��: ��
*	�� �� ֵ: ��
* �� �� ��:   					
*********************************************************************************************************
*/
void DMA1_Stream5_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&hdma_usart2_rx);
}

/*
*********************************************************************************************************
*	�� �� ��: DMA1_Stream6_IRQHandler
*	����˵��: 
*	��    ��: ��
*	�� �� ֵ: ��
* �� �� ��:   					
*********************************************************************************************************
*/
void DMA1_Stream6_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&hdma_usart2_tx);
}

/*
*********************************************************************************************************
*	�� �� ��: DMA2_Stream7_IRQHandler
*	����˵��: 
*	��    ��: ��
*	�� �� ֵ: ��
* �� �� ��:  
stm32f4xx_it.c ����
*********************************************************************************************************
*/
void BSP_UART_IDLE_Handler(UART_HandleTypeDef *huart)
{
	unsigned int rxCnt = 0;
	if(__HAL_UART_GET_IT_SOURCE(huart, UART_IT_IDLE) != RESET)/* �����˿����ж�λ�Ž����ж� */
	{
		
		if(__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE) != RESET)/* �ǿ����ж� */
		{	
			__HAL_UART_CLEAR_IDLEFLAG(huart);	/* ������ڿ����ж� */
			unsigned char dmaBit = HAL_IS_BIT_SET(huart->Instance->CR3, USART_CR3_DMAR);
			if(dmaBit)
			{		
				rxCnt = __HAL_DMA_GET_COUNTER(huart->hdmarx);/* ��DMA�Ĵ����ж�ȡʣ��ռ�Ĵ���ֵ */
			}
			else
			{
				rxCnt = huart->RxXferCount;
			}		
			HAL_UART_AbortReceive(huart);/* �رմ��ڽ��� */
			
			/* ����1�ж� */
			if(huart->Instance == USART1)
			{
				g_tBspUart1.rxLen  = g_tBspUart1.rxSize - rxCnt;
				g_tBspUart1.rxFlag = 1;
				
				osEventFlagsSet(event_USART1_ID , 0x01U << 0);  /*�����¼���־�� event_Flags1��flag0��1*/				
				/* ���¿������ڽ��� ������ж����濪�����գ����ͺ�����Ҫ�����ж�,����ԭ���뿴�ĵ�UART������� __HAL_LCOK ˵�� */
				if(dmaBit)
				{
					HAL_UART_Receive_DMA(&huart1 , g_tBspUart1.pRxBuf , g_tBspUart1.rxSize);
				}
				else
				{
					HAL_UART_Receive_IT(&huart1 , g_tBspUart1.pRxBuf , g_tBspUart1.rxSize);
				}
			}
			
			else if(huart->Instance == USART2)
			{//
				g_tBspUsart2.rxLen  = g_tBspUsart2.rxSize - rxCnt;
				g_tBspUsart2.rxFlag = 1;
				
				osEventFlagsSet(event_USART2_ID , 0x01U << 0);  /*�����¼���־�� event_Flags1��flag0��1*/				
				/* ���¿������ڽ��� ������ж����濪�����գ����ͺ�����Ҫ�����ж�,����ԭ���뿴�ĵ�UART������� __HAL_LCOK ˵�� */
				if(dmaBit)
				{
					HAL_UART_Receive_DMA(&husart2 , g_tBspUsart2.pRxBuf , g_tBspUsart2.rxSize);
				}
				else
				{
					HAL_UART_Receive_IT(&husart2 , g_tBspUsart2.pRxBuf , g_tBspUsart2.rxSize);
				}
			}
			
			
			/* ����4�ж� */
			else if(huart->Instance == UART4)
			{
				g_tBspUart4.rxLen  = g_tBspUart4.rxSize - rxCnt;
				g_tBspUart4.rxFlag = 1;
				/* ���¿������ڽ��� ������ж����濪�����գ����ͺ�����Ҫ�����ж�,����ԭ���뿴�ĵ�UART������� __HAL_LCOK ˵�� */
				if(dmaBit)
				{
					HAL_UART_Receive_DMA(&huart4 , g_tBspUart4.pRxBuf , g_tBspUart4.rxSize);
				}
				else
				{
					HAL_UART_Receive_IT(&huart4 , g_tBspUart4.pRxBuf , g_tBspUart4.rxSize);
				}
			}
			
			/* ����6�ж� */
			else if(huart->Instance == USART6)
			{
				g_tBspUsart6.rxLen  = g_tBspUsart6.rxSize - rxCnt;
				g_tBspUsart6.rxFlag = 1;
				/* ���¿������ڽ��� ������ж����濪�����գ����ͺ�����Ҫ�����ж�,����ԭ���뿴�ĵ�UART������� __HAL_LCOK ˵�� */
				if(dmaBit)
				{
					HAL_UART_Receive_DMA(&husart6 , g_tBspUsart6.pRxBuf , g_tBspUsart6.rxSize);
				}
				else
				{
					HAL_UART_Receive_IT(&husart6 , g_tBspUsart6.pRxBuf , g_tBspUsart6.rxSize);
				}
			}	

			
		}
	}
}


