#ifndef __LCD_INIT_H
#define __LCD_INIT_H

//#include "sys.h"
#define USE_HORIZONTAL 0  //���ú�������������ʾ 0��1Ϊ���� 2��3Ϊ����


#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 240
#define LCD_H 320

#else
#define LCD_W 320
#define LCD_H 240
#endif

//-----------------LCD�˿ڶ���---------------- 
/**************************************
// �ⲿ��˵���Ĺܽ�ӳ��Ͷ��ܷ����ĳ���ͬ���������⣡����
SCL --- LCD.3 -- PB13 -- SPI_SCK   	Ӳ��SPI����
SDA --- LCD.4 -- PB15 -- SPI_MOSI		Ӳ��SPI����

RES --- LCD.5 -- PA0 -- LCD_RESET		����
DC  --- LCD.6 -- PC13 -- LCD_DC			
CS  --- LCD.7 -- PC15 -- SPI_NSS			����û��ô��
BLK --- LCD.8 -- PE7 -- LCD_BLK			����
**************************************/

/*����*/
#define LCD_BLK_Clr()  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET)
#define LCD_BLK_Set()  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET)

/*����*/
#define LCD_RES_Clr()  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET)//RES
#define LCD_RES_Set()  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET)


#define LCD_DC_Clr()   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET)//DC
#define LCD_DC_Set()   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET)
 		     
#define LCD_CS_Clr()   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_RESET)//CS
#define LCD_CS_Set()   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_SET)



void LCD_Clear(uint16_t Color);
void LCD_GPIO_Init(void);							
void LCD_Writ_Bus(unsigned char dat);		
void LCD_WR_DATA8(unsigned char dat);		
void LCD_WR_DATA(unsigned short dat);		
void LCD_WR_REG(unsigned char dat);			
void LCD_Address_Set(unsigned short x1,unsigned short y1,unsigned short x2,unsigned short y2);
void LCD_Init(void);
#endif




