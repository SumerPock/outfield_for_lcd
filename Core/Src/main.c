/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
	* 调试过程中发现的问题1：之前使用uartfifo调试速度慢的串口，比如200ms以上的速度接收发送时，未发现丢数据
	  但当我将速度提升至10ms这个级别，以115200bps 传输25Byte的数据时出错，首先115200
		的波特率传输速度极限在每秒11.25kByte/s , 而我只达到了2.5KByte/s就出现了很严重的
		丢包，事实证明FIFO只能缓解数据丢包现象，当我改成DMA传输是就没发现有丢包现象了
		
		问题2：我将串口数据发送DMA方式 放入定时器中发送，发现数据无法解析，接入逻辑分析仪后发现有时候
		串口数据会与发送的不一致
  ******************************************************************************
  */


#include "main.h"
#include "bsp.h"
#include "pic.h"

void SystemClock_Config(void);

CRC_HandleTypeDef hcrc;
IWDG_HandleTypeDef hiwdg = {0};


/*****************************任务*************************************/
void AppTaskStart(void *argument);		/*	启动任务	*/
osThreadId_t ThreadIdStart = NULL;			/* 启动任务线程ID */
/*启动任务*/
const osThreadAttr_t ThreadStart_Attr = 
{
	.name = "osRtxStartThread",			/* 线程名字  */
	.attr_bits = osThreadDetached,  /* 线程类型  */
	.priority = osPriorityHigh7,		/* 线程优先级 */
	.stack_size = 2048,							/* 堆栈的大小 */
};


void AppTaskLcdShow(void *argument);	/*	液晶屏幕显示任务	*/
osThreadId_t ThreadIdLcdShow = NULL;		/* 液晶屏幕显示任务线程ID */
/*液晶屏幕显示任务*/
const osThreadAttr_t ThreadLcdShow_Attr = 
{
	.name = "osRtxLcdShowThread",		/* 线程名字   */
	.attr_bits = osThreadDetached,  /* 线程类型   */
	.priority = osPriorityHigh6,		/* 线程优先级 */
	.stack_size = 2048,							/* 堆栈的大小 */
};


void AppTaskUart_1(void *argument);		/*	UART1任务	*/
osThreadId_t ThreadIdUart_1 = NULL;			/*UART1任务线程ID*/
/*UART1任务*/
const osThreadAttr_t ThreadUart_1_Attr = 
{
	.name = "osRtxUart1Thread",		  /* 线程名字   */
	.attr_bits = osThreadDetached,  /* 线程类型   */
	.priority = osPriorityHigh5,		/* 线程优先级 */
	.stack_size = 2048,							/* 堆栈的大小 */
};

void AppTaskUart_2(void *argument);		/*	UART2任务	*/
osThreadId_t ThreadIdUart_2 = NULL;			/*UART2任务线程ID*/
/*UART2任务*/
const osThreadAttr_t ThreadUart_2_Attr = 
{
	.name = "osRtxUart2Thread",		  /* 线程名字   */
	.attr_bits = osThreadDetached,  /* 线程类型   */
	.priority = osPriorityHigh4,		/* 线程优先级 */
	.stack_size = 2048,							/* 堆栈的大小 */
};


void AppTaskUart_4(void *argument);		/*	UART4任务	*/
osThreadId_t ThreadIdUart_4 = NULL;			/*UART4任务线程ID*/
/*UART4任务*/
const osThreadAttr_t ThreadUart_4_Attr = 
{
	.name = "osRtxUart4Thread",			/* 线程名字   */
	.attr_bits = osThreadDetached,  /* 线程类型   */
	.priority = osPriorityHigh3,		/* 线程优先级 */
	.stack_size = 2048,							/* 堆栈的大小 */
};

void AppTaskUart_6(void *argument);		/*	UART6任务	*/
osThreadId_t ThreadIdUart_6 = NULL;			/*UART6任务线程ID*/
/*UART6任务*/
const osThreadAttr_t ThreadUart_6_Attr = 
{
	.name = "osRtxUart6Thread",		  /* 线程名字   */
	.attr_bits = osThreadDetached,  /* 线程类型   */
	.priority = osPriorityHigh2,		/* 线程优先级 */
	.stack_size = 2048,							/* 堆栈的大小 */
};


void AppTaskRot_enc(void *argument);	/*	旋转编码器任务 Rotary encoder	*/
osThreadId_t ThreadIdRot_enc = NULL;		/*旋转编码器任务线程ID*/
/*旋转编码器任务*/
const osThreadAttr_t ThreadRot_enc_Attr = 
{
	.name = "osRtxRot_encThread",		/* 线程名字   */
	.attr_bits = osThreadDetached,  /* 线程类型   */
	.priority = osPriorityHigh6,		/* 线程优先级 */
//	.stack_size = 2048,							/* 堆栈的大小 */
	.stack_size = 512,							/* 堆栈的大小 */
};

void AppTaskGETKEYDATA(void *argument);		/*	按键任务	*/
osThreadId_t ThreadIdGetKey = NULL;				/* 按键任务线程ID */
const osThreadAttr_t ThreadGetKey = 			/*获取按键任务*/
{
	.name = "osRtxGetKeyThread",		/* 线程名字   */
	.attr_bits = osThreadDetached,  /* 线程类型   */
	.priority = osPriorityHigh6,		/* 线程优先级 */
	.stack_size = 1024,							/* 堆栈的大小 */
};


void AppTaskA_menu(void *argument);		/*	一级菜单选择任务	*/
osThreadId_t ThreadIdA_menu = NULL;		/* 一级菜单任务线程ID */
const osThreadAttr_t ThreadA_menu = 	/*一级菜单任务*/
{
	.name = "osRtxA_menuThread",		/* 线程名字   */
	.attr_bits = osThreadDetached,  /* 线程类型   */
	.priority = osPriorityHigh5,		/* 线程优先级 */
	.stack_size = 1024,							/* 堆栈的大小 */
};


/*****************************软件定时器*************************************/
/* 软件定时器 */
void timer_Periodic_App(void *argument);  
/* 保存定时器ID */
osTimerId_t  timerID_Periodic = NULL;   
/* 软件定时器1 属性  1ms*/
const osTimerAttr_t timer_Periodic_Attr = 
{
	.name = "periodic timer",        /* 定时器名字 */
};

/*****************************消息队列*************************************/
/*消息队列ID 传输电池信息*/
osMessageQueueId_t msgQueue_ButteryData;
/*建立消息队列 传递电池信息*/
const osMessageQueueAttr_t msgQueue_ButteryData_Attr =
{
	.name = "Message_Queue_ButteryData",
};

/*消息队列ID 传输LM75B温度信息*/
osMessageQueueId_t msgQueue_LM75BData;
/*建立消息队列 传递LM75B温度信息*/
const osMessageQueueAttr_t msgQueue_LM75BData_Attr =
{
	.name = "Message_Queue_LM75BData",
};


/*消息队列ID 传输旋转编码器的信息*/
osMessageQueueId_t msgQueue_Rotary_encoderData;

const osMessageQueueAttr_t msgQueue_Rotary_encoder_Attr =
{
	.name = "Message_Queue_Rotary_encoderData",
};


/*消息队列ID 传输按键键值*/
osMessageQueueId_t msgQueue_KeyData;

const osMessageQueueAttr_t msgQueue_KeyData_Attr =
{
	.name = "Message_Queue_KeyData",
};




/*****************************事件标志组*************************************/
/* 事件标志组属性 */
const osEventFlagsAttr_t event_DYTDataF_Attr = 
{
	.name = "event_DYTDataF",   	/* 事件标志组的名字 */
																/* 其他默认 */
};
/* 标志组ID */
osEventFlagsId_t event_DYTDataF_ID = NULL; 


/*串口1 事件标志组属性 */
const osEventFlagsAttr_t event_USART1_Attr = 
{
	.name = "event_USART1",   	/* 事件标志组的名字 */
															/* 其他默认 */
};
/* 标志组ID */
osEventFlagsId_t event_USART1_ID = NULL; 


/*串口2 事件标志组属性 */
const osEventFlagsAttr_t event_USART2_Attr = 
{
	.name = "event_USART2",   	/* 事件标志组的名字 */
															/* 其他默认 */
};
/* 标志组ID */
osEventFlagsId_t event_USART2_ID = NULL; 


/*串口4 事件标志组属性 */
const osEventFlagsAttr_t event_UART4_Attr = 
{
	.name = "event_UART4",   	/* 事件标志组的名字 */
														/* 其他默认 */
};
/* 标志组ID */
osEventFlagsId_t event_UART4_ID = NULL; 


/*LM75B 事件标志组属性 */
const osEventFlagsAttr_t event_LM75B_Attr = 
{
	.name = "event_LM75B",   	/* 事件标志组的名字 */
														/* 其他默认 */
};
/* 标志组ID */
osEventFlagsId_t event_LM75B_ID = NULL; 


/*电池信息 事件标志组属性 */
const osEventFlagsAttr_t event_Battery_Attr = 
{
	.name = "event_Battery",   	/* 事件标志组的名字 */
															/* 其他默认 */
};
/* 标志组ID */
osEventFlagsId_t event_Battery_ID = NULL; 


/*旋转编码器 事件标志组属性 */
const osEventFlagsAttr_t event_Rotary_encoder_Attr = 
{
	.name = "event_Rotary_encoder",   	/* 事件标志组的名字 */
																			/* 其他默认 */
};
/* 标志组ID */
osEventFlagsId_t event_Rotary_encoder_ID = NULL; 



/*UI进入选择 事件标志组属性 choose*/
const osEventFlagsAttr_t event_UIChoose_Attr = 
{
	.name = "event_UIChoose",   	/* 事件标志组的名字 */
																			/* 其他默认 */
};
/* 标志组ID */
osEventFlagsId_t event_UIChoose_ID = NULL; 


///*屏幕UI进入选择 事件标志组属性 choose*/
//const osEventFlagsAttr_t event_UIScreenChoose_Attr = 
//{
//	.name = "event_UIScreenChoose",   	/* 事件标志组的名字 */
//																			/* 其他默认 */
//};
///* 标志组ID */
//osEventFlagsId_t event_UIScreenChoose_ID = NULL; 


/*
*********************************************************************************************************
*	函 数 名: 
*	功能说明: 
*	形    参: 无
*	返 回 值: 无
* 优 先 级:   
*********************************************************************************************************
*/
int main(void)
{
  /* MCU Configuration--------------------------------------------------------*/
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  /* Configure the system clock */
  SystemClock_Config();
  /* Initialize all configured peripherals */
  MX_GPIO_Init();
	EventRecorderInitialize(EventRecordAll, 1U);
	EventRecorderStart();	
  /* Infinite loop */
	HAL_SuspendTick();			/* 内核开启前关闭HAL的时间基准 */
	osKernelInitialize();  	/* 初始化RTX5内核 */ 	
	/* 创建启动任务 */
	ThreadIdStart = osThreadNew(AppTaskStart, NULL, &ThreadStart_Attr); 
	osKernelStart();	 			/* 启动RTX5内核 */
}



/*
*********************************************************************************************************
*	函 数 名: AppTaskStart
*	功能说明: 启动任务，这里用作BSP驱动包处理。
*	形    参: 无
*	返 回 值: 无
*   优 先 级: osPriorityHigh4  
*********************************************************************************************************
*/
void AppTaskStart(void *argument)
{
	unsigned char crctest[6] = {0x00 , 0x01 , 0x02 , 0x03 , 0x04 , 0x05};	
	const uint16_t usFrequency = 5000;	/* 延迟周期 */
	uint32_t tick;
	HAL_ResumeTick(); 					/* 重新开启HAL库心跳 */
	tick = osKernelGetTickCount(); 		/* 获取当前时间 */
	
	/*UART4 - 0
	  UART1 - 1*/
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
	
	bsp_InitSPIBus();			/* 配置SPI总线 */	
	LCD_Init();						/* SPI LCD初始化*/
	//MX_IWDG_Init(&hiwdg);	/* 独立看门狗 */
	ConfigLed();
	ConfigSP330(U1 , RS422); 	/* U1 422模式(UART1) */
	ConfigSP330(U26 , RS422); /* U26 422模式(UART4) */
	ConfigSP330(U8 , RS232);	/* U8 232模式(UART6) */
	MX_I2C1_Init();						/* I2C */
	ConfigOUT();
	
	//bsp_InitUart();		/* 初始化fifo串口 , 由于fifo模式发现丢数据严重，改用DMA模式*/
	bsp_InitKey();
	
	MX_DMA_Init();
	
	MX_USART1_UART_Init();
	MX_UART4_UART_Init();
	MX_USART2_UART_Init();
	MX_USART6_UART_Init();
	
	/**UART DMA config**/
	HAL_UART_Transmit(&huart1, (uint8_t *)"this is uart1 send data\r\n", 24, 1000);	
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);	/* 开启串口空闲中断 */
	#define UART_RX_MODE_DMA	/* 开启串口接收 大小缓冲区最大长度rxSize */	
	#ifdef UART_RX_MODE_DMA
	HAL_UART_Receive_DMA(&huart1, g_tBspUart1.pRxBuf, g_tBspUart1.rxSize);
	#else
	HAL_UART_Receive_IT(&huart1, g_tBspUart1.pRxBuf, g_tBspUart1.rxSize);
	#endif
	
	HAL_UART_Transmit(&huart4, (uint8_t *)"this is uart4 send data!\r\n", 24, 1000);
	__HAL_UART_ENABLE_IT(&huart4, UART_IT_IDLE);	/* 开启串口空闲中断 */
	#define UART_RX_MODE_DMA											/* 开启串口接收 大小缓冲区最大长度rxSize */
	#ifdef UART_RX_MODE_DMA
	HAL_UART_Receive_DMA(&huart4, g_tBspUart4.pRxBuf, g_tBspUart4.rxSize);
	#else
	HAL_UART_Receive_IT(&huart4, g_tBspUart4.pRxBuf, g_tBspUart4.rxSize);
	#endif
	
	
	HAL_UART_Transmit(&husart2, (uint8_t *)"this is uart2 send data!\r\n", 24, 1000);
	__HAL_UART_ENABLE_IT(&husart2, UART_IT_IDLE);	/* 开启串口空闲中断 */
	#define UART_RX_MODE_DMA											/* 开启串口接收 大小缓冲区最大长度rxSize */
	#ifdef UART_RX_MODE_DMA
	HAL_UART_Receive_DMA(&husart2, g_tBspUsart2.pRxBuf, g_tBspUsart2.rxSize);
	#else
	HAL_UART_Receive_IT(&husart2, g_tBspUsart2.pRxBuf, g_tBspUsart2.rxSize);
	#endif


	HAL_UART_Transmit(&husart6, (uint8_t *)"this is usart6 send data!\r\n", 24, 1000);
	__HAL_UART_ENABLE_IT(&husart6, UART_IT_IDLE);	/* 开启串口空闲中断 */
	#define UART_RX_MODE_DMA											/* 开启串口接收 大小缓冲区最大长度rxSize */
	#ifdef UART_RX_MODE_DMA
	HAL_UART_Receive_DMA(&husart6, g_tBspUsart6.pRxBuf, g_tBspUsart6.rxSize);
	#else
	HAL_UART_Receive_IT(&husart6, g_tBspUsart6.pRxBuf, g_tBspUsart6.rxSize);
	#endif


	//ThreadIdLcdShow = osThreadNew(AppTaskLcdShow, NULL, &ThreadLcdShow_Attr);
	/*链接孙工小源板*/
	//ThreadIdUart_1 = osThreadNew(AppTaskUart_1, NULL, &ThreadUart_1_Attr);	
	/*链接上位机*/
	//ThreadIdUart_4 = osThreadNew(AppTaskUart_4, NULL, &ThreadUart_4_Attr);	
	/*链接库仑计*/
	//ThreadIdUart_2  = osThreadNew(AppTaskUart_2, NULL, &ThreadUart_2_Attr);	
	


	/*多级菜单显示*/
	ThreadIdA_menu = osThreadNew(AppTaskA_menu, NULL, &ThreadA_menu);
	
	/*旋转编码器*/
	ThreadIdRot_enc = osThreadNew(AppTaskRot_enc, NULL, &ThreadRot_enc_Attr);
	
	ThreadIdGetKey = osThreadNew(AppTaskGETKEYDATA, NULL, &ThreadGetKey);

//	/* 创建定时器 */
//	timerID_Periodic = osTimerNew(timer_Periodic_App,   /* 定时器回调函数 */
//																osTimerPeriodic,      /* 连续运行 */
//																NULL,              	/* 不传递参数 */
//																&timer_Periodic_Attr  /* 定时器属性 */
//															 );
//	osTimerStart(timerID_Periodic , 20U);/* 用于给蜂鸣器提供节拍 */
	
	msgQueue_ButteryData =	osMessageQueueNew(MQ_SIZE , sizeof(struct BUTTERY) ,&msgQueue_ButteryData_Attr);
	msgQueue_LM75BData   =	osMessageQueueNew(MQ_SIZE , sizeof(struct LM75BTEMP) ,&msgQueue_LM75BData_Attr);	
	msgQueue_Rotary_encoderData   =	osMessageQueueNew(MQ_SIZE , sizeof(struct Rotary_encoder) ,&msgQueue_Rotary_encoder_Attr);		
	msgQueue_KeyData   =	osMessageQueueNew(MQ_SIZE , sizeof(struct KEYDATA) ,&msgQueue_KeyData_Attr);

	event_DYTDataF_ID = osEventFlagsNew(&event_DYTDataF_Attr);	
	event_USART1_ID   = osEventFlagsNew(&event_USART1_Attr);
	event_USART2_ID   = osEventFlagsNew(&event_USART2_Attr);	
	event_UART4_ID    = osEventFlagsNew(&event_UART4_Attr);
	event_LM75B_ID    = osEventFlagsNew(&event_LM75B_Attr);
	event_Battery_ID    = osEventFlagsNew(&event_Battery_Attr);		
	//旋转编码器
	event_Rotary_encoder_ID    = osEventFlagsNew(&event_Rotary_encoder_Attr);	
	/*多级UI选择*/
	event_UIChoose_ID    = osEventFlagsNew(&event_UIChoose_Attr);		


	LCD_Clear(DARKBLUE);	
	DISPlay_Title();
	DISPlay_Function_1(0);
	DISPlay_Function_2(0);
	DISPlay_Function_3(0);
	DISPlay_Function_4(0);
	
	DISPlay_image_park(initialize , center);
	DISPlay_self_test();
	while(1)
	{	
		printf("The RTX5 OS is Run\r\n");			
		/* 相对延迟 */
		tick += usFrequency;                          
		osDelayUntil(tick);
		printf("Start App going to exit.\r\n");		
		/* Start线程退出 */
		osThreadExit();  /* Start线程属于osThreadDetached,退出后无法通过osThreadJoin加入调度 */
	}
}



/*
*********************************************************************************************************
*	函 数 名: AppTaskA_menu
*	功能说明: 多级菜单UI显示
*	形    参: 无
*	返 回 值: 无
* 优 先 级:  
* 其    他: 这个函数中的功能比较复杂，一开始我只是简单的使用if else ,但发现使用简单的if else实现多级菜单切换异常
						困难，所以只能引入状态机函数这个终极杀手解决此问题
*********************************************************************************************************
*/
void AppTaskA_menu(void *argument)
{
	const uint16_t usFrequency = 5; /* 相对延时 */	
	uint32_t tick;
	osStatus_t os_Status; 
	tick = osKernelGetTickCount();  /* 获取当前时间 */
	
	unsigned int Flag_Rotary_encoder = 0; 							// 旋转编码器
	static unsigned char msg_Rotary_encoder_Number = 0;
	struct Rotary_encoder getrot_enc;
	static unsigned char getfun = 0;		


	getfun = UI_CilckFun(1);//上电默认给一个1
	struct KEYDATA Getkeydata;
	
	static unsigned char msg_GetKeyDATA_Number = 0;	    //按键	
	static unsigned char keyenter = 0;//entern 按键

	unsigned int Flag_UIChoose = 0; 
	unsigned char cmos[9] = {0x81 , 0x01 , 0x04 , 0x47 , 0x00 , 0x00 , 0x00 , 0x00 , 0xff};
	unsigned short zoom_level[30] = 
				{0 , 0x16A1 , 0x2063 , 0x2628 , 0x2A1D , 0x2D13 , 0x2F6D , 0x3161 , 0x330D , 0x3486 , 
		0x35D7 , 0x3709 , 0x3820 , 0x3920 , 0x3A0A , 0x3ADD , 0x3B9C , 0x3C46 , 0x3CDC , 0x3D60 , 
		0x3DD4 , 0x3E39 , 0x3E90 , 0x3EDC , 0x3F1E , 0x3F57 , 0x3F8A , 0x3FB6 , 0x3FDC , 0x4000 };
	//DISPlay_DrawCircle_Break();	
	while(1)
	{
		
		Flag_Rotary_encoder = osEventFlagsGet(event_Rotary_encoder_ID);
		//旋转编码器值队列
		msg_Rotary_encoder_Number = osMessageQueueGetCount(msgQueue_Rotary_encoderData);

		//按键键值队列
		msg_GetKeyDATA_Number = osMessageQueueGetCount(msgQueue_KeyData);
	
		Flag_UIChoose = osEventFlagsGet(event_UIChoose_ID);
		

		
		//旋转编码器触发
		if(Flag_Rotary_encoder && msg_Rotary_encoder_Number > 0)
		{
			if(osEventFlagsClear(event_Rotary_encoder_ID , 0x01U) == (osFlagsErrorUnknown|osFlagsErrorParameter|osFlagsErrorResource))
			{			
				printf("EventFlagClrer is flad \r\n");
			}	

			os_Status = osMessageQueueGet(msgQueue_Rotary_encoderData, /* 消息队列的名字 */
																		&getrot_enc,   							/* 存放消息的内存 */
																		NULL,              					/* 取出消息的优先级 */
																		osWaitForever      					/* 超时时间，在中断函数里调用osMessageQueueGet时，此参数必须是NULL */);			
			//这里必须做一个限制
			if(Flag_UIChoose == 0)
			{
				getfun = UI_CilckFun(getrot_enc.Rotary_encoder);
			}
		}
		else
		{
		}
		//按键触发
		if(msg_GetKeyDATA_Number > 0)
		{
			os_Status = osMessageQueueGet(msgQueue_KeyData, /* 消息队列的名字 */
															&Getkeydata,   							/* 存放消息的内存 */
															NULL,              					/* 取出消息的优先级 */
															osWaitForever      					/* 超时时间，在中断函数里调用osMessageQueueGet时，此参数必须是NULL */);
		
			if(Getkeydata.Key_Data == 0x07 && getfun == 1)
			{
				DISPlay_FUN1_Break();
				DISPlay_FUN1();				//二级子菜单1 dyt激光
				Getkeydata.Key_Data = 0;
				
				DISPlay_image_park(not_caught , north_by_west);
				
				osEventFlagsSet(event_UIChoose_ID , 0x01U << 0);  
			}
			else if(Getkeydata.Key_Data == 0x05 && getfun == 1)
			{
				DISPlay_FUN1_Break();
				DISPlay_DrawCircle_Break();
				
				UI_CilckFun(1);//退出二级子菜单1
				Getkeydata.Key_Data = 0;	
				if(osEventFlagsClear(event_UIChoose_ID , 0x01U) == (osFlagsErrorUnknown|osFlagsErrorParameter|osFlagsErrorResource))
				{			
					printf("EventFlagClrer is flad \r\n");
				}					
			}
			
			else if(Getkeydata.Key_Data == 0x07 && getfun == 2)
			{
				DISPlay_FUN1_Break();//二级子菜单2 相机控制
				DISPlay_FUN2(); 			
				DISPlay_image_park(not_caught , north_by_east);				
				osEventFlagsSet(event_UIChoose_ID , 0x01U << 1); 
			}
			else if(Getkeydata.Key_Data == 0x05 && getfun == 2)
			{
				DISPlay_FUN1_Break();//退出二级子菜单2		
				DISPlay_DrawCircle_Break();				
				UI_CilckFun(2);
				Getkeydata.Key_Data = 0;	
				if(osEventFlagsClear(event_UIChoose_ID , 0x02U) == (osFlagsErrorUnknown|osFlagsErrorParameter|osFlagsErrorResource))
				{			
					printf("EventFlagClrer is flad \r\n");
				}	
			}
			
			else if(Getkeydata.Key_Data == 0x07 && getfun == 3)
			{
				DISPlay_FUN1_Break();//二级子菜单3 循环散热
				DISPlay_FUN3(); 							
				DISPlay_image_park(not_caught , south_by_west);				
				osEventFlagsSet(event_UIChoose_ID , 0x01U << 2); 
			}
			else if(Getkeydata.Key_Data == 0x05 && getfun == 3)
			{
				DISPlay_FUN1_Break();//退出二级子菜单3	
				DISPlay_DrawCircle_Break();				
				UI_CilckFun(3);
				Getkeydata.Key_Data = 0;	
				if(osEventFlagsClear(event_UIChoose_ID , 0x04U) == (osFlagsErrorUnknown|osFlagsErrorParameter|osFlagsErrorResource))
				{			
					printf("EventFlagClrer is flad \r\n");
				}	
			}
			
			else if(Getkeydata.Key_Data == 0x07 && getfun == 4)
			{
				DISPlay_FUN1_Break();//二级子菜单4 程控模式
				DISPlay_FUN4(); 
				
				DISPlay_image_park(not_caught , south_by_east);
				
				osEventFlagsSet(event_UIChoose_ID , 0x01U << 3); 
			}
			else if(Getkeydata.Key_Data == 0x05 && getfun == 4)
			{
				DISPlay_FUN1_Break();//退出二级子菜单4
				DISPlay_DrawCircle_Break();				
				UI_CilckFun(4);
				Getkeydata.Key_Data = 0;	
				if(osEventFlagsClear(event_UIChoose_ID , 0x08U) == (osFlagsErrorUnknown|osFlagsErrorParameter|osFlagsErrorResource))
				{			
					printf("EventFlagClrer is flad \r\n");
				}	
			}	
			
			//相机控制
			if(Flag_UIChoose == 0x02)
			{
				//ThreadIdUart_6 = osThreadNew(AppTaskUart_6, NULL, &ThreadUart_6_Attr);
				//if(Getkeydata.Key_Data == 0x01 || Getkeydata.Key_Data == 0x02)
				static unsigned char loopCMOSKEY = 0;
				unsigned char Zoomdata[4] = {0};
				if(Getkeydata.Key_Data == 0x02)
				{			
					if(loopCMOSKEY < 29)
					{
						loopCMOSKEY++;
					}
					Zoomdata[0] = zoom_level[loopCMOSKEY] >> 12;
					Zoomdata[1] = (zoom_level[loopCMOSKEY] >> 8) & 0x0F;
					Zoomdata[2] = (zoom_level[loopCMOSKEY] & 0XF0) >> 4;
					Zoomdata[3] = zoom_level[loopCMOSKEY] & 0X0F;
					
					cmos[4] = Zoomdata[0];
					cmos[5] = Zoomdata[1];
					cmos[6] = Zoomdata[2];
					cmos[7] = Zoomdata[3];
				
					BSP_UART_Transmit_DMA(&husart6, &cmos[0], 9);
				}else if(Getkeydata.Key_Data == 0x04)
				{
					if(loopCMOSKEY > 0)
					{
						loopCMOSKEY--;
					}
					Zoomdata[0] = zoom_level[loopCMOSKEY] >> 12;
					Zoomdata[1] = (zoom_level[loopCMOSKEY] >> 8) & 0x0F;
					Zoomdata[2] = (zoom_level[loopCMOSKEY] & 0XF0) >> 4;
					Zoomdata[3] = zoom_level[loopCMOSKEY] & 0X0F;
					
					cmos[4] = Zoomdata[0];
					cmos[5] = Zoomdata[1];
					cmos[6] = Zoomdata[2];
					cmos[7] = Zoomdata[3];
				
					BSP_UART_Transmit_DMA(&husart6, &cmos[0], 9);					
					
					
					//printf("loopCMOSKEY = %d \r\n" , loopCMOSKEY);
					//BSP_UART_Transmit_DMA(&husart6, &buff[0], 8);
				}
			}			
		}else
		{
		}		
		tick += usFrequency;  /* 相对延时 */                          
		osDelayUntil(tick);			
	}
}

/*
*********************************************************************************************************
*	函 数 名: AppTaskGETKEYDATA
*	功能说明: 获取按键键值
*	形    参: 无
*	返 回 值: 无
* 优 先 级:   
*********************************************************************************************************
*/
void AppTaskGETKEYDATA(void *argument)
{
	const uint16_t usFrequency = 10; /* 相对延时500ms */	
	uint32_t tick;
	osStatus_t os_Status; 
	tick = osKernelGetTickCount();  /* 获取当前时间 */
	uint8_t ucKeyCode; 
	struct KEYDATA getkeydata;
	unsigned char oldkeydata = 0;
	while(1)
	{
		bsp_KeyScan10ms();	
		/* 按键滤波和检测由后台systick中断服务程序实现，我们只需要调用bsp_GetKey读取键值即可。 */
		ucKeyCode = bsp_GetKey();	/* 读取键值, 无键按下时返回 KEY_NONE = 0 */
		if (ucKeyCode != KEY_NONE)
		{
			switch (ucKeyCode)
			{
				case KEY_DOWN_K1:			/* K1键按下 */
					//printf("K1键按下\r\n");
					getkeydata.Key_Data = 1;
					HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_4);
				break;

				case KEY_UP_K1:				/* K1键弹起 */
					//printf("K1键弹起\r\n");
					getkeydata.Key_Data = 2;
					HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_4);
				break;

				case KEY_DOWN_K2:			/* K2键按下 */
					//printf("K2键按下\r\n");
					getkeydata.Key_Data = 3;
					HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_5);
				break;

				case KEY_UP_K2:				/* K2键弹起 */
					//printf("K2键弹起\r\n");
					getkeydata.Key_Data = 4;
					HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_5);
				break;

				case KEY_DOWN_K3:			/* K3键按下 */
					//printf("K3键按下\r\n");
					getkeydata.Key_Data = 5;
					HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
				break;

				case KEY_UP_K3:				/* K3键弹起 */
					//printf("K3键弹起\r\n");
					getkeydata.Key_Data = 6;
					HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
				break;

				case JOY_DOWN_U:			/* 摇杆UP键按下 */
					//printf("摇杆上键按下\r\n");
					getkeydata.Key_Data = 7;
					HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_8);
					HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_9);			
				
					HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
					HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_5);
					HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_4);
					oldkeydata = 0;
				break;
				
				default:
					/* 其它的键值不处理 */
					break;
			}
		}		
		if(oldkeydata != getkeydata.Key_Data)
		{
			oldkeydata = getkeydata.Key_Data;
			os_Status = osMessageQueuePut(msgQueue_KeyData, 	/* 消息队列的名字 */
																		&getkeydata, 				/* 放入消息队列的变量（消息） */
																		NULL,      					/* 放入消息的优先级 */
																		NULL      	 				/* 超时时间为0，如果osMessageQueuePut被中断回调函数调用时，此参数必须是NULL */
																		);	
		}
		tick += usFrequency;  /* 相对延时 */                          
		osDelayUntil(tick);
	}
}

/*
*********************************************************************************************************
*	函 数 名: AppTaskUart_1
*	功能说明: 链接孙工小原板
*	形    参: 无
*	返 回 值: 无
* 优 先 级:   
*********************************************************************************************************
*/
void AppTaskUart_1(void *argument)
{
	const uint16_t usFrequency = 25; /* 相对延时500ms */	
	uint32_t tick;
	osStatus_t os_Status; 
	tick = osKernelGetTickCount();  /* 获取当前时间 */
	
	unsigned char buff[8] = {1,2,3,4,5,6,7,8};
       
	uint8_t read;
	uint8_t ucStatus = 0;  /* 状态机标志 */
	uint8_t ucCount=0, i;
	uint32_t Flag = 0;	
	uint8_t timebase;
	unsigned int loopdata = 0;
	
	while(1)
	{					
		Flag = osEventFlagsGet(event_USART1_ID);
		if(Flag)
		{
			unsigned char buffuart1[25] = {0};
			memcpy(buffuart1 , g_uart1_rx_buf , 25);		
			DYTCommData(&buffuart1[0] , 25);		
			memset(g_uart1_rx_buf, 0, sizeof(g_uart1_rx_buf));
						
//			/* 开启串口接收 大小缓冲区最大长度rxSize */
//			#define UART_TX_MODE_IT	
//			#ifdef UART_TX_MODE_DMA
//			HAL_UART_Transmit_DMA(&huart1, &timebase, 1);
//			#elif defined UART_TX_MODE_IT
//			BSP_UART_Transmit_DMA(&huart1, &buffuart1[0], 25);
//			#else
//			#endif		
			
//			/* 开启串口接收 大小缓冲区最大长度rxSize */
//			#define UART_TX_MODE_IT	
//			#ifdef UART_TX_MODE_DMA
//			HAL_UART_Transmit_DMA(&huart1, &timebase, 1);
//			#elif defined UART_TX_MODE_IT
//			BSP_UART_Transmit_DMA(&husart2, &buffuart1[0], 25);
//			#else
//			#endif				
			if(osEventFlagsClear(event_USART1_ID,0x01U) != (osFlagsErrorUnknown|osFlagsErrorParameter|osFlagsErrorResource))
			{			
			}		
		}
		else
		{
		}		
		tick += usFrequency;  /* 相对延时 */                          
		osDelayUntil(tick);
	}	
}



/*
*********************************************************************************************************
*	函 数 名: 
*	功能说明: 链接库仑计,查询LM75B信息
*	形    参: 无
*	返 回 值: 无
* 优 先 级:   
*********************************************************************************************************
*/
void AppTaskUart_2(void *argument)
{
	const uint16_t usFrequency = 200;/* 相对延时500ms */	
	uint32_t tick;
	osStatus_t os_Status; 
	tick = osKernelGetTickCount();  /* 获取当前时间 */
	
	static unsigned int loop = 0;	
	static unsigned char buffuart2[12] = {0};
	unsigned int Flag = 0;
	while(1)
	{		
		Flag = osEventFlagsGet(event_USART2_ID);
		if(loop > 6)
		{
			loop = 0;
		}
		else
		{
			unsigned char sensortemp[2] = {0};
			unsigned char gettemp[2] = {0};
			unsigned char sendbuff[4] = {0xFF , 0x01 , 0x16 , 0x16};/*FF 01 16 16*/	
			struct LM75BTEMP GetLM75Btempdata;
			switch(loop)
			{
				case 0:		
				sendbuff[2] = 0x16;
				sendbuff[3] = 0x16;
				BSP_UART_Transmit_DMA(&husart2, &sendbuff[0], 4);
					break;
				
				case 1:
				sendbuff[2] = 0x08;
				sendbuff[3] = 0x08;
				BSP_UART_Transmit_DMA(&husart2, &sendbuff[0], 4);
					break;
				
				case 2:
				sendbuff[2] = 0x09;
				sendbuff[3] = 0x09;
				BSP_UART_Transmit_DMA(&husart2, &sendbuff[0], 4);
					break;
				
				case 3:
				sendbuff[2] = 0x0A;
				sendbuff[3] = 0x0A;
				BSP_UART_Transmit_DMA(&husart2, &sendbuff[0], 4);
					break;
				
				case 4:
				sendbuff[2] = 0x0D;
				sendbuff[3] = 0x0D;
				BSP_UART_Transmit_DMA(&husart2, &sendbuff[0], 4);
					break;
				
				case 5:
				sendbuff[2] = 0x0F;
				sendbuff[3] = 0x0F;
				BSP_UART_Transmit_DMA(&husart2, &sendbuff[0], 4);
				HAL_IWDG_Refresh(&hiwdg);
					break;	
				
				case 6:
					HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_10);
					HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_11);
					if(HAL_I2C_Mem_Read(&hi2c1 , 0X90 , 0x00, I2C_MEMADD_SIZE_8BIT, sensortemp, 2, 1000) != HAL_OK)
					{
						printf("the I2C find error\r\n");
					}
					else
					{
						if(LM75BTemp(sensortemp , sizeof(sensortemp) , gettemp , sizeof(gettemp)))
						{
							GetLM75Btempdata.lm75b_buff[0] = gettemp[0];
							GetLM75Btempdata.lm75b_buff[1] = gettemp[1];
							os_Status = osMessageQueuePut(msgQueue_LM75BData, /* 消息队列的名字 */
																						&GetLM75Btempdata, 	/* 放入消息队列的变量（消息） */
																						NULL,      					/* 放入消息的优先级 */
																						NULL      	 				/* 超时时间为0，如果osMessageQueuePut被中断回调函数调用时，此参数必须是NULL */
							);				
							osEventFlagsSet(event_LM75B_ID , 0x01U << 0);  /*启动事件标志组 event_Flags1的flag0置1*/								
						}
						else
						{
							printf("temp = -");
						}
					}
					break;
				
				default:
					break;
			}
			loop++;
		}			
		/* USER CODE BEGIN 3 */
		if(Flag)
		{	
			memcpy(buffuart2 , g_usart2_rx_buf , 12);		
			bsp_buttery_protocol(buffuart2 , 12);		
			memset(g_usart2_rx_buf, 0, sizeof(g_usart2_rx_buf));	
			memset(buffuart2, 0, sizeof(buffuart2));	
			if(osEventFlagsClear(event_USART2_ID,0x01U) != (osFlagsErrorUnknown|osFlagsErrorParameter|osFlagsErrorResource))
			{			
			}	
		}			
		tick += usFrequency;  											/* 相对延时 */                          
		osDelayUntil(tick);
	}	
}

/*
*********************************************************************************************************
*	函 数 名: 
*	功能说明: 链接上位机通讯
*	形    参: 无
*	返 回 值: 无
* 优 先 级:   
*********************************************************************************************************
*/
void AppTaskUart_4(void *argument)
{
	const uint16_t usFrequency = 5; /* 相对延时500ms */	
	uint32_t tick;
	uint32_t Flag = 0;
	osStatus_t os_Status; 
	tick = osKernelGetTickCount();  /* 获取当前时间 */
	
	unsigned char buff1[25] = {0x55 , 0xAA , 0xDC , 0xD6 , 0x40 , 0x01 , 0x02 , 0x00 , 0x00 , 0x00 , 
														 0x00 , 0xC3 , 0x50 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 
														 0x00 , 0x00 , 0x00 , 0x00 , 0x06};
	uint8_t ucKeyCode;        
	uint8_t read;
	uint8_t ucStatus = 0;  /* 状态机标志 */
	uint8_t ucCount=0, i;
	uint8_t buf[128];
	while(1)
	{		
//		Flag = osEventFlagsGet(event_DYTDataF_ID);
//		if(Flag)
//		{
//			//comSendBuf(COM4 , buff1 , 25);
//			if(osEventFlagsClear(event_DYTDataF_ID,0x01U) != (osFlagsErrorUnknown|osFlagsErrorParameter|osFlagsErrorResource)){
		//if(osEventFlagsClear(event_USART1_ID,0x01U) != (osFlagsErrorUnknown|osFlagsErrorParameter|osFlagsErrorResource))
//			}
//		}
//		else{
//		}
		
		if(g_tBspUart4.rxFlag == 1)
		{
			//loopdata++;
			g_tBspUart4.rxFlag = 0;
			/* 打印接收到的实际长度 rxLen */
			//#define PRINTF_MODE_1
			
			//#if defined PRINTF_MODE_1
			#ifdef PRINTF_MODE_1
			/* 这样方式打印数据如果缓冲区有之前的数据会打印出其他数据 */
			printf("UART1 len:%d buf:%s\r\n", g_tBspUart4.rxLen, g_tBspUart4.pRxBuf);
			#elif defined PRINTF_MODE_2
			printf("UART1 len:%d buf:%s\r\n", g_tBspUart4.rxLen, g_tBspUart4.pRxBuf);
			memset(g_tBspUart.pRxBuf, 0, g_tBspUart4.rxSize);
			#else
			//printf("loopdata = %d \r\n", loopdata);
			/* 这样写最好节省时间 */
			//printf("UART1 len:%d buf:%.*s\r\n", g_tBspUart4.rxLen, g_tBspUart4.rxLen, g_tBspUart4.pRxBuf);
			#endif
		}
		tick += usFrequency;  /* 相对延时 */                          
		osDelayUntil(tick);
	}	
}



/*
*********************************************************************************************************
*	函 数 名: 
*	功能说明: 
*	形    参: 无
*	返 回 值: 无
* 优 先 级:   
*********************************************************************************************************
*/
void AppTaskUart_6(void *argument)
{
	const uint16_t usFrequency = 50; /* 相对延时500ms */	
	uint32_t tick;
	osStatus_t os_Status; 
	tick = osKernelGetTickCount();  /* 获取当前时间 */
	
	unsigned char buff[8] = {1,2,3,4,5,6,7,8};
	uint8_t ucKeyCode;        
	uint8_t read;
	uint8_t ucStatus = 0;  /* 状态机标志 */
	uint8_t ucCount=0, i;
	uint8_t buf[128];
	while(1)
	{		
//		BSP_UART_Transmit_DMA(&husart6, &buff[0], 8);
		
		tick += usFrequency;  /* 相对延时 */                          
		osDelayUntil(tick);
	}	
}






/*
*********************************************************************************************************
*	函 数 名: 
*	功能说明: lcd液晶显示驱动函数
*	形    参: 无
*	返 回 值: 无
* 优 先 级:   
*********************************************************************************************************
*/
void AppTaskLcdShow(void *argument)
{
	unsigned char ucKeyCode;		/* 按键代码 */
	const uint16_t usFrequency = 25; /* 相对延时500ms */	
	uint32_t tick;
	osStatus_t os_Status; 
	tick = osKernelGetTickCount();  /* 获取当前时间 */
	
	static unsigned char msg_Number = 0;	
	static unsigned char msg_LM75B_Number = 0;
	static unsigned char msg_Rotary_encoder_Number = 0;
	//static unsigned char msg_GetKeyDATA_Number = 0;
	
	struct BUTTERY buttery;
	struct Rotary_encoder getrot_enc;
	struct LM75BTEMP LCDGetLM75Btempdata;

		
	unsigned int Flag_LM75B = 0;	
	unsigned int Flag_Battery = 0;
	//unsigned int Flag_Rotary_encoder = 0;
	
	static unsigned char getfun = 0;	
	static unsigned char returnuc = 0;//记录一下是否返回
	
	while(1)
	{
		Flag_LM75B = osEventFlagsGet(event_LM75B_ID);
		msg_LM75B_Number = osMessageQueueGetCount(msgQueue_LM75BData);
		
		Flag_Battery = osEventFlagsGet(event_Battery_ID);
		msg_Number = osMessageQueueGetCount(msgQueue_ButteryData);
		
		//Flag_Rotary_encoder = osEventFlagsGet(event_Rotary_encoder_ID);
		//msg_Rotary_encoder_Number = osMessageQueueGetCount(msgQueue_Rotary_encoderData);
		
		//msg_GetKeyDATA_Number = osMessageQueueGetCount(msgQueue_KeyData);
//		if(Flag_LM75B && msg_LM75B_Number > 0)
//		{
//			if(osEventFlagsClear(event_USART1_ID , 0x01U) == (osFlagsErrorUnknown|osFlagsErrorParameter|osFlagsErrorResource))
//			{			
//				printf("EventFlagClrer is flad \r\n");
//			}	
//			os_Status = osMessageQueueGet(msgQueue_LM75BData, /* 消息队列的名字 */
//																		&LCDGetLM75Btempdata,   					/* 存放消息的内存 */
//																		NULL,              		/* 取出消息的优先级 */
//																		osWaitForever      		/* 超时时间，在中断函数里调用osMessageQueueGet时，此参数必须是NULL */);
//			DISPlay_Temperature(&LCDGetLM75Btempdata.lm75b_buff[0] , 2);
//		}
//		
//		if(Flag_Battery && msg_Number > 0)
//		{
//			if(osEventFlagsClear(event_Battery_ID , 0x01U) == (osFlagsErrorUnknown|osFlagsErrorParameter|osFlagsErrorResource))
//			{			
//				printf("EventFlagClrer is flad \r\n");
//			}	
//			os_Status = osMessageQueueGet(msgQueue_ButteryData, /* 消息队列的名字 */
//																		&buttery,   					/* 存放消息的内存 */
//																		NULL,              		/* 取出消息的优先级 */
//																		osWaitForever      		/* 超时时间，在中断函数里调用osMessageQueueGet时，此参数必须是NULL */);
//			DisplayElectricity(buttery.Butryremaining); 								//剩余百分比
//			DISPlay_Battery_Voltage(buttery.Voltage);										//电压
//			DISPlay_Battery_electric_current(buttery.Electric_current);	//电流
//		}		
		


		//UI逻辑处理
//		if(msg_GetKeyDATA_Number > 0)
//		{
//			os_Status = osMessageQueueGet(msgQueue_KeyData, /* 消息队列的名字 */
//															&Getkeydata,   							/* 存放消息的内存 */
//															NULL,              					/* 取出消息的优先级 */
//															osWaitForever      					/* 超时时间，在中断函数里调用osMessageQueueGet时，此参数必须是NULL */);
//			printf("Getkeydata = %d \r\n" , Getkeydata.Key_Data);
//			if(getfun == 1 && Getkeydata.Key_Data == 7 && returnuc == 0)
//			{//功能1
//				DISPlay_FUN1_Break();
//				DISPlay_FUN1();		
//			}
//			if(getfun == 1 && Getkeydata.Key_Data == 5)
//			{//返回
//				DISPlay_Return();
//				returnuc = 1;
//			}
//			if(getfun == 1 && Getkeydata.Key_Data == 7 && returnuc == 1)
//			{
//				DISPlay_FUN1_Break();
//				DISPlay_Function_1(0);
//				DISPlay_Function_2(0);
//				DISPlay_Function_3(0);
//				DISPlay_Function_4(0);
//				getfun = 0;
//				returnuc = 0;
//			}
//		}		
		tick += usFrequency;  /* 相对延时 */                          
		osDelayUntil(tick);
	}
}



/*
*********************************************************************************************************
*	函 数 名: 
*	功能说明: 讨厌的很，旋转编码器明明是给CPLD用的，非要在ARM上加入，所以不得不加入这个进程
*	形    参: 无
*	返 回 值: 无
* 优 先 级:   
*********************************************************************************************************
*/
void AppTaskRot_enc(void *argument)
{
	osStatus_t os_Status; 
	unsigned char ucKeyCode;		/* 按键代码 */
	unsigned int tick;
	const uint16_t usFrequency = 2; /* 相对延时500ms */	
	tick = osKernelGetTickCount();  /* 获取当前时间 */
	static int a = 0 , b = 0 , c = 0 , d = 0;
	//static char loop = 0;
	static char loop = 1;
	static char oldloop = 1;
	struct Rotary_encoder rot_enco_data;
	while(1)
	{			
		c = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_8);  //读取编码器引脚状态
		d = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1);  //读取编码器引脚状态
		if(a == 0 && b == 0)
		{
			if(c == 1 && d == 0)
			{
				if(loop < 4)
				{
					loop++;
				}
				else if(loop >= 4)
				{
					loop = 1;
				}
				//printf("loop = %d \r\n" , loop);
			}
			else if(c == 0 && d == 1)
			{
//				if(loop <= 3 && loop > 0)
//				{
//					loop--;
//				}
//				else if(loop <= 0)
//				{
//					loop = 3;
//				}
				if(loop <= 4 && loop > 1)
				{
					loop--;
				}
				else if(loop <= 1)
				{
					loop = 4;
				}
				printf("loop = %d \r\n" , loop);
			}
		}	
		if(oldloop != loop)//键值发生改变启动消息队列
		{
			oldloop = loop;
			rot_enco_data.Rotary_encoder = loop;
			os_Status = osMessageQueuePut(msgQueue_Rotary_encoderData, /* 消息队列的名字 */
									&rot_enco_data, 															/* 放入消息队列的变量（消息） */
									NULL,      																		/* 放入消息的优先级 */
									NULL      	 				/* 超时时间为0，如果osMessageQueuePut被中断回调函数调用时，此参数必须是NULL */
									);		
			osEventFlagsSet(event_Rotary_encoder_ID , 0x01U << 0);  /*启动事件标志组 event_Flags1的flag0置1*/	
		}
		else
		{			
		}
		a = c;           
		b = d;  //a,b保存前一次引脚采集到的状态	
		tick += usFrequency;  /* 相对延时 */                          
		osDelayUntil(tick);
	}
}


/*
*********************************************************************************************************
*	函 数 名: timer_Periodic_App
*	功能说明: 软件定时器。
*	形    参: 无
*	返 回 值: 无
*   优 先 级: osPriorityHigh4  
*********************************************************************************************************
*/
void timer_Periodic_App(void *argument)
{
	unsigned int tick = 0;	
	unsigned int longtime = 0;
	//tick = osKernelGetTickCount();	

	//longtime = bsp_GetRunTime();	/* 获取系统当前的time ticks */
}
