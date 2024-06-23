/*
*********************************************************************************************************
*
*	ģ������ : BSPģ��(For STM32F407)
*	�ļ����� : bsp.c
*	��    �� : V1.0
*	˵    �� : ����Ӳ���ײ�������������ļ���ÿ��c�ļ����� #include "bsp.h" ���������е���������ģ�顣
*			   bsp = Borad surport packet �弶֧�ְ�
*	�޸ļ�¼ :
*		�汾��  ����         ����       ˵��
*		V1.0    2018-07-29  Eric2013   ��ʽ����
*
*	Copyright (C), 2018-2030, ���������� www.armfly.com
*
*********************************************************************************************************
*/
#include "bsp.h"



/*
*********************************************************************************************************
*	                                   ��������
*********************************************************************************************************
*/
//static void SystemClock_Config(void);
void Error_Handler(void);

/*
*********************************************************************************************************
*	�� �� ��: bsp_Init
*	����˵��: ��ʼ�����е�Ӳ���豸���ú�������CPU�Ĵ���������ļĴ�������ʼ��һЩȫ�ֱ�����ֻ��Ҫ����һ��
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_Init(void)
{
//	/* 
//       STM32H407 HAL ���ʼ������ʱϵͳ�õĻ���F407�Դ���16MHz��HSIʱ��:
//	   - ���ú���HAL_InitTick����ʼ���δ�ʱ���ж�1ms��
//	   - ����NVIV���ȼ�����Ϊ4��
//	 */
//	HAL_Init();

//	/* 
//       ����ϵͳʱ�ӵ�168MHz
//       - �л�ʹ��HSE��
//       - �˺��������ȫ�ֱ���SystemCoreClock������������HAL_InitTick��
//    */
//	SystemClock_Config();

//	/* 
//	   Event Recorder��
//	   - �����ڴ���ִ��ʱ�������MDK5.25�������ϰ汾��֧�֣�IAR��֧�֡�
//	   - Ĭ�ϲ����������Ҫʹ�ܴ�ѡ���ؿ�V5�������û��ֲ��8��
//	*/	
//#if Enable_EventRecorder == 1  
//	/* ��ʼ��EventRecorder������ */
//	EventRecorderInitialize(EventRecordAll, 1U);
//	EventRecorderStart();
//#endif
//	
//	bsp_InitKey();    	/* ������ʼ����Ҫ���ڵδ�ʱ��֮ǰ����Ϊ��ť�����ͨ���δ�ʱ��ɨ�� */
//	bsp_InitTimer();  	/* ��ʼ���δ�ʱ�� */
//	bsp_InitUart();		/* ��ʼ������ */
//	bsp_InitLed();    	/* ��ʼ��LED */	
//	BEEP_InitHard();    /* ��ʼ�������� */
//	
//	/* ��Բ�ͬ��Ӧ�ó��������Ҫ�ĵײ�����ģ���ʼ������ */

	
//	bsp_InitSFlash();	/* ��ʼ��SPI ����Flash */
}


/* ������Ź�
 * ���� IWDG �ĳ�ʱʱ��
 * Tout = prv/40 * rlv (s)
 *      prv������[4,8,16,32,64,128,256]
 * prv:Ԥ��Ƶ��ֵ��ȡֵ���£�
 *     @arg IWDG_Prescaler_4: IWDG prescaler set to 4
 *     @arg IWDG_Prescaler_8: IWDG prescaler set to 8
 *     @arg IWDG_Prescaler_16: IWDG prescaler set to 16
 *     @arg IWDG_Prescaler_32: IWDG prescaler set to 32
 *     @arg IWDG_Prescaler_64: IWDG prescaler set to 64
 *     @arg IWDG_Prescaler_128: IWDG prescaler set to 128
 *     @arg IWDG_Prescaler_256: IWDG prescaler set to 256
 *
 *        �������Ź�ʹ��LSI��Ϊʱ�ӡ�
 *        LSI ��Ƶ��һ���� 30~60KHZ ֮�䣬�����¶Ⱥ͹������ϻ���һ����Ư�ƣ���
 *        ��һ��ȡ 40KHZ�����Զ������Ź��Ķ�ʱʱ�䲢һ���ǳ���ȷ��ֻ�����ڶ�ʱ�侫��
 *        Ҫ��Ƚϵ͵ĳ��ϡ�
 *
 * rlv:��װ�ؼĴ�����ֵ��ȡֵ��ΧΪ��0-0XFFF
 * �������þ�����
 * IWDG_Config(IWDG_Prescaler_64 ,625);  // IWDG 1s ��ʱ��� 
 *                        ��625/40��*625 = 4s
 */
void MX_IWDG_Init(IWDG_HandleTypeDef *idwg)
{
	idwg->Instance = IWDG;
	idwg->Init.Prescaler = IWDG_PRESCALER_256;
	idwg->Init.Reload = 625;
	if(HAL_IWDG_Init(idwg)!= HAL_OK)
	{
		Error_Handler();
	}  
}



/*
*********************************************************************************************************
*	�� �� ��: bsp_RunPer10ms
*	����˵��: �ú���ÿ��10ms��Systick�жϵ���1�Ρ���� bsp_timer.c�Ķ�ʱ�жϷ������һЩ����ʱ��Ҫ���ϸ��
*			������Է��ڴ˺��������磺����ɨ�衢���������п��Ƶȡ�
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_RunPer10ms(void)
{
//	bsp_KeyScan10ms();
//	BEEP_Pro();
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_RunPer1ms
*	����˵��: �ú���ÿ��1ms��Systick�жϵ���1�Ρ���� bsp_timer.c�Ķ�ʱ�жϷ������һЩ��Ҫ�����Դ��������
*			 ���Է��ڴ˺��������磺��������ɨ�衣
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_RunPer1ms(void)
{
	
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_Idle
*	����˵��: ����ʱִ�еĺ�����һ����������for��whileѭ������������Ҫ���� CPU_IDLE() �������ñ�������
*			 ������ȱʡΪ�ղ������û��������ι��������CPU��������ģʽ�Ĺ��ܡ�
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_Idle(void)
{
	/* --- ι�� */

	/* --- ��CPU�������ߣ���Systick��ʱ�жϻ��ѻ��������жϻ��� */

	/* ���� emWin ͼ�ο⣬���Բ���ͼ�ο���Ҫ����ѯ���� */
	//GUI_Exec();

	/* ���� uIP Э�飬���Բ���uip��ѯ���� */
	//TOUCH_CapScan();
}

unsigned char bsp_sun_protocol(unsigned char *ucucStatus , unsigned char *ucucCount);

unsigned char DYTCommData(unsigned char* buff , unsigned char buffled)
{
	static int loop = 0;
	
	unsigned char ucreturn = 0;
	if(*buff == 0x55 && *(buff + 1) == 0xAA && *(buff + 2) == 0xDC)
	{
		printf("loop = %d \r\n" , loop);
		loop++;
	}
	return ucreturn;
}


unsigned char bsp_sun_protocol(unsigned char *ucucStatus , unsigned char *ucucCount)
{
	static unsigned char Buff[64] = {0};
	unsigned char ucreturn = 0;
	unsigned char read = 0;
	static int loop = 0;
	//static struct BUTTERY buttery;
	osStatus_t os_Status; 
	//if (comGetChar(COM1 , &read))
	{
		loop++;
		printf("loop = %d \r\n" , loop);
		*ucucStatus = 0;
		*ucucCount=0;			
//		switch (*ucucStatus)
//		{
//			/* ״̬0��֤���յ�0x55 */
//			case 0:
//				if(read == 0x55)
//				{
//					*ucucStatus = 1;        
//				}
//				break;

//			/* ״̬1��֤���յ�0xAA */
//			case 1:
//				if(read == 0xAA)
//				{
//					*ucucStatus = 2;//1Byte����
//				}
//				else
//				{
//					*ucucStatus = 0;
//				}
//				break;
//				
//			/* ״̬2��֤���յ�0xDC */	
//			case 2:
//				if(read == 0xDC)
//				{
//					*ucucStatus = 3;
//				}
//				else
//				{
//					*ucucStatus = 0;
//				}
//				break;				
//			
//			case 3:
//				Buff[(*ucucCount)] = read;
//				if((*ucucCount) == 21)			/* ���չ�1������ */
//				{
//					/*�����¼���־��*/
//					/* �¼���־��event_Flags1��flag0��1 */
//					osEventFlagsSet(event_DYTDataF_ID , 0x01U << 0);  
//					loop++;
//					printf("loop = %d \r\n" , loop);
////					unsigned char buff1[26] = {0x55 , 0xaa ,0xdc};
////					for(unsigned char i = 0 ; i <24 ; i++ )
////					{
////						buff1[i + 3] = Buff[i];
////					}
//					*ucucStatus = 0;
//					*ucucCount=0;
//					//comSendBuf(COM4 , buff1 , 25);
//					memset(Buff, 0, sizeof(Buff));
//				}
//				else
//				{
//					(*ucucCount)++;
//				}
//				break;
//							
//			default:
//				break;
//		}
	}
	return ucreturn;
}

unsigned char bsp_buttery_protocol(unsigned char *getbuff , unsigned char getbuffsize)
{
	unsigned char ucreturn = 0;
	static unsigned char Buff[32] = {0};
	static unsigned char ButteryData[16] = {0x55 , 0xAA};
	static unsigned char ButteryDataflag[6] = {0};	
	static struct BUTTERY buttery;
	osStatus_t os_Status; 
	for(unsigned char i = 0 ; i < getbuffsize ; i ++)
	{
		Buff[i] = *(getbuff + i);
	}
	if(Buff[0] == 0xff && Buff[1] == 0x02)
	{
		switch(Buff[2])
		{
			case 0x08://����¶�
				buttery.temperature = Buff[3];
				ButteryDataflag[0] = 1;
				memset(Buff, 0, sizeof(Buff));
				break;
	
			case 0x16://���״̬
				buttery.ButryStae = Buff[3];
				ButteryDataflag[1] = 1;
				memset(Buff, 0, sizeof(Buff));
				break;

			case 0x0D://�����԰ٷֱ�
				buttery.Butryremaining = Buff[3];
				ButteryDataflag[2] = 1;
				memset(Buff, 0, sizeof(Buff));
				break;
			
			default:
				ucreturn = 4;
				memset(Buff, 0, sizeof(Buff));
				break;
		}
	}
	else if(Buff[0] == 0xff && Buff[1] == 0x03)
	{	
		switch(Buff[2])
		{
			case 0x09://��ѹ
				buttery.Voltage = Buff[4] | (Buff[3]<<8);
				ButteryDataflag[3] = 1;
				memset(Buff, 0, sizeof(Buff));
				break;

			case 0x0F:
				buttery.Butrycapacity = Buff[4] | (Buff[3]<<8);
				ButteryDataflag[4] = 1;
				memset(Buff, 0, sizeof(Buff));
				break;
	
			case 0x0A://ʣ������
				buttery.Electric_current = Buff[4] | (Buff[3]<<8);
				ButteryDataflag[5] = 1;
				memset(Buff, 0, sizeof(Buff));
				break;
			
			default:
				ucreturn = 3;
				memset(Buff, 0, sizeof(Buff));
				break;
		}
	}	
	if(ButteryDataflag[0] + ButteryDataflag[1] + ButteryDataflag[2] + ButteryDataflag[3] + ButteryDataflag[4] 
		 + ButteryDataflag[5] == 6)
	{
		os_Status = osMessageQueuePut(msgQueue_ButteryData, /* ��Ϣ���е����� */
								&buttery, 									/* ������Ϣ���еı�������Ϣ�� */
								NULL,              											/* ������Ϣ�����ȼ� */
								NULL               											/* ��ʱʱ��Ϊ0�����osMessageQueuePut���жϻص���������ʱ���˲���������NULL */
								);
		osEventFlagsSet(event_Battery_ID , 0x01U << 0);  /*�����¼���־�� event_Flags1��flag0��1*/			
		memset(Buff, 0, sizeof(Buff));
		memset(ButteryDataflag, 0, sizeof(ButteryDataflag));
		memset(&buttery, 0, sizeof(buttery));
		
	}	
	return ucreturn;
}

//unsigned char bsp_buttery_protocol(unsigned char *ucucStatus , unsigned char *ucucCount)
//{
//	static unsigned char Buff[32] = {0};
//	static unsigned char ButteryData[16] = {0x55 , 0xAA};
//	static unsigned char ButteryDataflag[6] = {0};
//	unsigned char ucreturn = 0;
//	unsigned char read = 0;
//	static struct BUTTERY buttery;
//	osStatus_t os_Status; 
//	//if (comGetChar(COM2, &read))
//	{
//		//printf("%X\r\n", read);
//		switch (*ucucStatus)
//		{
//			/* ״̬0��֤���յ�0xff */
//			case 0:
//				if(read == 0xFF)
//				{
//					*ucucStatus = 1;        
//				}
//				break;

//			/* ״̬1��֤���յ�0x02��0x03 */
//			case 1:
//				if(read == 0x02)
//				{
//					*ucucStatus = 2;//1Byte����
//				}
//				else if(read == 0x03)
//				{
//					*ucucStatus = 3;//2Byte����
//				}
//				else
//				{
//					*ucucStatus = 0;
//				}
//				break;

//			case 2:
//				switch(read)
//				{
//					case 0x16://���״̬
//						*ucucStatus = 5;
//						break;
//					
//					case 0x08://�¶�
//						*ucucStatus = 6;
//						break;

//					case 0x0D://ʣ��ٷֱ�
//						*ucucStatus = 9;
//						break;
//						
//					default:
//						*ucucStatus = 0;
//						break;
//				}
//				break;

//				case 3:
//					switch(read)
//					{
//						case 0x09://��ѹ
//						*ucucStatus = 7;
//						break;

//						case 0x0A://����
//						*ucucStatus = 8;
//						break;

//						case 0x0F://ʣ��������
//						*ucucStatus = 10;
//						break;

//						default:
//						*ucucStatus = 0;
//						break;
//					}
//					break;
//				
//			/*״̬*/
//			case 5:
//				Buff[(*ucucCount)] = read;
//				if((*ucucCount) == 1)			/* ���չ�1������ */
//				{
//					unsigned char temp = 0;	
//					buttery.ButryStae = Buff[0];
//					buttery.add = Buff[1];
//					temp = 0xff + 0x02 + 0x16 + buttery.ButryStae;
//					if(buttery.add == temp)
//					{		
//						ButteryData[2] = 	0x16;	
//						ButteryData[3] = 	buttery.ButryStae;	
//						if(ButteryDataflag[0] == 0)
//						{
//							ButteryDataflag[0]++;
//						}					
//					}
//					*ucucStatus = 0;
//					*ucucCount=0;
//					memset(Buff, 0, sizeof(Buff));
//				}
//				else
//				{
//					(*ucucCount)++;
//				}
//				break;
//				
//			/*�¶�*/
//			case 6:
//				Buff[(*ucucCount)] = read;
//				if((*ucucCount) == 1)			/* ���չ�1������ */
//				{
//					unsigned char temp = 0;	
//					buttery.temperature = Buff[0];
//					buttery.add = Buff[1];
//					temp = 0xff + 0x02 + 0x08 + buttery.temperature;
//					if(buttery.add == temp)
//					{	
//						ButteryData[4] = 	0x08;	
//						ButteryData[5] = 	buttery.temperature;			
//						if(ButteryDataflag[1] == 0)
//						{
//							ButteryDataflag[1]++;
//						}				
//					}
//					*ucucStatus = 0;
//					*ucucCount=0;
//					memset(Buff, 0, sizeof(Buff));
//				}
//				else
//				{
//					(*ucucCount)++;
//				}						
//				break;

//			/*��ѹ*/
//			case 7:
//				Buff[(*ucucCount)] = read;
//				if((*ucucCount) == 2)			/* ���չ�2������ */
//				{
//					unsigned char temp = 0;	
//					buttery.Voltage = Buff[1] | (Buff[0]<<8);
//					buttery.add = Buff[2];
//					temp =  0xff + 0x03 + 0x09 + Buff[1] + Buff[0];
//					if(temp == buttery.add)
//					{
//						ButteryData[6] = 	0x09;	
//						ButteryData[7] = 	buttery.Voltage;
//						ButteryData[8] = 	buttery.Voltage>>8;
//						if(ButteryDataflag[2] == 0)
//						{
//							ButteryDataflag[2]++;
//						}	
//					}
//					*ucucStatus = 0;
//					*ucucCount=0;
//					memset(Buff, 0, sizeof(Buff));
//				}
//				else
//				{
//					(*ucucCount)++;
//				}						
//				break;	
//			
//			/*����*/
//			case 8:
//				Buff[(*ucucCount)] = read;
//				if((*ucucCount) == 2)			/* ���չ�2������ */
//				{
//					unsigned char temp = 0;	
//					buttery.Electric_current = Buff[1] | (Buff[0]<<8);//���Ϊ�������ŵ�Ϊ����
//					buttery.add = Buff[2];
//					temp =  0xff + 0x03 + 0x0A + Buff[1] + Buff[0];
//					if(temp == buttery.add)
//					{
//						ButteryData[6] = 	0x0A;	
//						ButteryData[7] = 	buttery.Electric_current;
//						ButteryData[8] = 	buttery.Electric_current>>8;
//						if(ButteryDataflag[3] == 0)
//						{
//							ButteryDataflag[3]++;
//						}	
//					}
//					*ucucStatus = 0;
//					*ucucCount=0;
//					memset(Buff, 0, sizeof(Buff));
//				}
//				else
//				{
//					(*ucucCount)++;
//				}						
//				break;	
//			
//			/*ʣ��ٷֱ�*/	
//			case 9:
//				Buff[(*ucucCount)] = read;
//				if((*ucucCount) == 1)	
//				{
//					unsigned char temp = 0;	
//					buttery.Butryremaining = Buff[0];
//					buttery.add = Buff[1];
//					temp = 0xff + 0x02 + 0x0D + buttery.Butryremaining;
//					if(buttery.add == temp)
//					{						
//						ButteryData[9] = 	0x0D;	
//						ButteryData[10] = buttery.Butryremaining;
//						if(ButteryDataflag[4] == 0)
//						{
//							ButteryDataflag[4]++;
//						}								
//					}
//					*ucucStatus = 0;
//					*ucucCount=0;
//					memset(Buff, 0, sizeof(Buff));
//				}
//				else
//				{
//					(*ucucCount)++;
//				}						
//				break;	
//			
//			/*ʣ������*/
//			case 10:
//				Buff[(*ucucCount)] = read;
//				if((*ucucCount) == 2)			
//				{
//					unsigned char temp = 0;	
//					buttery.Butrycapacity = Buff[1] | (Buff[0]<<8);
//					buttery.add = Buff[2];
//					temp = 0xFF + 0x03 + 0x0F + Buff[1] + Buff[0];
//					if(temp == buttery.add)
//					{
//						ButteryData[9] = 	0x0F;
//						ButteryData[10] = buttery.Butrycapacity;							
//						ButteryData[11] = buttery.Butrycapacity>>8;
//						if(ButteryDataflag[5] == 0)
//						{
//							ButteryDataflag[5]++;
//						}	
//					}
//					*ucucStatus = 0;
//					*ucucCount=0;
//					memset(Buff, 0, sizeof(Buff));
//				}
//				else
//				{
//					(*ucucCount)++;
//				}						
//				break;	
//				
//			default:
//				break;
//		}
//	}	
//	if(ButteryDataflag[0] + ButteryDataflag[1] + ButteryDataflag[2] + ButteryDataflag[3] + ButteryDataflag[4] 
//		 + ButteryDataflag[5] == 6)
//	{
//		os_Status = osMessageQueuePut(msgQueue_ButteryData, /* ��Ϣ���е����� */
//								&buttery, 									/* ������Ϣ���еı�������Ϣ�� */
//								NULL,              											/* ������Ϣ�����ȼ� */
//								NULL               											/* ��ʱʱ��Ϊ0�����osMessageQueuePut���жϻص���������ʱ���˲���������NULL */
//								);
//		memset(Buff, 0, sizeof(Buff));
//		memset(ButteryDataflag, 0, sizeof(ButteryDataflag));
//		memset(&buttery, 0, sizeof(buttery));
//		
//	}
//	return ucreturn;
//}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
void MX_GPIO_Init(void)
{
  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
}


#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/*
*********************************************************************************************************
*	�� �� ��: HAL_Delay
*	����˵��: �ض�������ӳٺ������滻HAL�еĺ�������ΪHAL�е�ȱʡ����������Systick�жϣ������USB��SD��
*             �ж������ӳٺ��������������Ҳ����ͨ������HAL_NVIC_SetPriority����Systick�ж�
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
/* ��ǰ����ʹ��stm32f4xx_hal.cĬ�Ϸ�ʽʵ�֣�δʹ�������ض���ĺ��� */
#if 0
void HAL_Delay(uint32_t Delay)
{
	bsp_DelayUS(Delay * 1000);
}
#endif

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/
