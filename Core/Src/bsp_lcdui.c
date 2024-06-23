
#include "bsp.h"

/*
*********************************************************************************************************
*	函 数 名: DISPlay_Return
*	功能说明: 返回
*	形    参: 无
*	返 回 值: 无
* 优 先 级:   
* 其		他: 占用y空间5个像素点，x空间240个像素点
*********************************************************************************************************
*/
void DISPlay_Return(void)
{
	//LCD_ShowString(130 , 80 , str , DARKBLUE , WHITE , 24 , 0);
	LCD_ShowChinese(130 , 80 , "确认返回" , WHITE , DARKBLUE , 24 , 0);
}


/*
*********************************************************************************************************
*	函 数 名: DISPlay_DrawCircle_Break
*	功能说明: 图案园刷新
*	形    参: 无
*	返 回 值: 无
* 优 先 级:   
* 其		他: 
*********************************************************************************************************
*/
void DISPlay_DrawCircle_Break(void)
{
		LCD_Fill(0 , 105 , 125 , 240 , DARKBLUE);
}


/*
*********************************************************************************************************
*	函 数 名: DISPlay_FUN1_Break
*	功能说明: 一级菜单刷新
*	形    参: 无
*	返 回 值: 无
* 优 先 级:   
* 其		他: 占用y空间5个像素点，x空间240个像素点
*********************************************************************************************************
*/
void DISPlay_FUN1_Break(void)
{
//	LCD_Fill(125  , 120 , 240  , 230 , DARKBLUE);
		LCD_Fill(125  , 80 , 240  , 230 , DARKBLUE);
}

/*
*********************************************************************************************************
*	函 数 名: DISPlay_FUN1
*	功能说明: 进入第一个二级菜单
*	形    参: 无
*	返 回 值: 无
* 优 先 级:   
* 其		他: 占用y空间5个像素点，x空间240个像素点
*********************************************************************************************************
*/
void DISPlay_FUN1(void)
{
	DISPlay_Function_1(0);
	unsigned char chinese1[5] = "周期";
	unsigned char chinese2[5] = "捕获"; 
	unsigned char chinese3[5] = "能量"; 	
	LCD_ShowChinese(130 , 120 , chinese1, WHITE , DARKBLUE , 24 , 0);
	LCD_ShowChinese(130 , 160 , chinese2, WHITE , DARKBLUE , 24 , 0);
	LCD_ShowChinese(130 , 200 , chinese3, WHITE , DARKBLUE , 24 , 0);
}

/*
*********************************************************************************************************
*	函 数 名: DISPlay_FUN2
*	功能说明: 进入第二个二级菜单
*	形    参: 无
*	返 回 值: 无
* 优 先 级:   
* 其		他: 占用y空间5个像素点，x空间240个像素点
*********************************************************************************************************
*/
void DISPlay_FUN2(void)
{	
	unsigned char chinese1[9] = "相机控制";
	LCD_ShowChinese(130 , 80 , chinese1, WHITE , DARKBLUE , 24 , 0);
}


/*
*********************************************************************************************************
*	函 数 名: DISPlay_FUN3
*	功能说明: 进入第三个二级菜单
*	形    参: 无
*	返 回 值: 无
* 优 先 级:   
* 其		他: 占用y空间5个像素点，x空间240个像素点
*********************************************************************************************************
*/
void DISPlay_FUN3(void)
{	
	unsigned char chinese1[9] = "循环散热";
	LCD_ShowChinese(130 , 80 , chinese1, WHITE , DARKBLUE , 24 , 0);
}



/*
*********************************************************************************************************
*	函 数 名: DISPlay_FUN3
*	功能说明: 进入第四个二级菜单
*	形    参: 无
*	返 回 值: 无
* 优 先 级:   
* 其		他: 占用y空间5个像素点，x空间240个像素点
*********************************************************************************************************
*/
void DISPlay_FUN4(void)
{	
	unsigned char chinese1[9] = "程控模式";
	LCD_ShowChinese(130 , 80 , chinese1, WHITE , DARKBLUE , 24 , 0);
}


/*
*********************************************************************************************************
*	函 数 名: DISPlay_Temperature
*	功能说明: 温度刷新显示
*	形    参: 无
*	返 回 值: 无
* 优 先 级:   
* 其		他: 占用y空间5个像素点，x空间240个像素点
*********************************************************************************************************
*/
void DISPlay_Temperature(unsigned char* gettemp , unsigned char gettrmplen)
{
	unsigned char lcdgettemp[2] = {0};		
	unsigned short get_temperature = 0;
	double FloatNum = 0.00;
	for(unsigned char i = 0 ; i < gettrmplen ; i++)
	{
		lcdgettemp[i] = *(gettemp + i);
	}
	get_temperature = lcdgettemp[0] | lcdgettemp[1]<<8;
	double fractpart = modf(get_temperature * 0.01 , &FloatNum);  //求3.1415的小数部分
	unsigned char xdata = 5;
	unsigned short ydata = 300;
	LCD_ShowChar(xdata , ydata , '+' , WHITE , DARKBLUE , 16 , 0);
	xdata = xdata + 10;
	LCD_ShowIntNum(xdata , ydata , FloatNum , 2 ,WHITE , DARKBLUE ,16);
	xdata = xdata + 17;
	LCD_ShowFloatNum1(xdata , ydata , fractpart , 2 , WHITE , DARKBLUE ,16);
	xdata = xdata + 26;	
	LCD_ShowChar(xdata , ydata , 'C' , WHITE , DARKBLUE , 16 , 0);
}


/*
*********************************************************************************************************
*	函 数 名: DisplayElectricity
*	功能说明: 电量显示
*	形    参: 无
*	返 回 值: 无
* 优 先 级:   
* 其		他: 占用y空间5个像素点，x空间240个像素点
*********************************************************************************************************
*/
void DisplayElectricity(unsigned char data)
{
	unsigned char getElectr = data;
//	enum ELECTRICITY;
	if(getElectr >= 95)
	{
			LCD_Fill(0  , 0 , 240  , 5 , GREEN);
	}
	else if(getElectr >= 90 && getElectr < 95)
	{
			LCD_Fill(0  , 0 , percentage_90_95  , 5 , GREEN);
			LCD_Fill(percentage_90_95  , 0 , 240  , 5 , DARKBLUE);
	}else if(getElectr >= 85 && getElectr < 90)
	{
			LCD_Fill(0  , 0 , percentage_85_90  , 5 , GREEN);
			LCD_Fill(percentage_85_90  , 0 , 240  , 5 , DARKBLUE);
	}else if(getElectr >= 80 && getElectr < 85)
	{
			LCD_Fill(0  , 0 , percentage_80_85  , 5 , GREEN);
			LCD_Fill(percentage_80_85  , 0 , 240  , 5 , DARKBLUE);
	}else if(getElectr >= 75 && getElectr < 80)
	{
			LCD_Fill(0  , 0 , percentage_75_80  , 5 , GREEN);
			LCD_Fill(percentage_75_80  , 0 , 240  , 5 , DARKBLUE);
	}else if(getElectr >= 70 && getElectr < 75)
	{
			LCD_Fill(0  , 0 , percentage_70_75  , 5 , GREEN);
			LCD_Fill(percentage_70_75  , 0 , 240  , 5 , DARKBLUE);
	}else if(getElectr >= 65 && getElectr < 70)
	{
			LCD_Fill(0  , 0 , percentage_65_70  , 5 , GREEN);
			LCD_Fill(percentage_65_70  , 0 , 240  , 5 , DARKBLUE);
	}else if(getElectr >= 60 && getElectr < 65)
	{
			LCD_Fill(0  , 0 , percentage_60_65  , 5 , GREEN);
			LCD_Fill(percentage_60_65  , 0 , 240  , 5 , DARKBLUE);
	}else if(getElectr >= 55 && getElectr < 60)
	{
			LCD_Fill(0  , 0 , percentage_55_60  , 5 , GREEN);
			LCD_Fill(percentage_55_60  , 0 , 240  , 5 , DARKBLUE);
	}else if(getElectr >= 50 && getElectr < 55)
	{
			LCD_Fill(0  , 0 , percentage_50_55  , 5 , GREEN);
			LCD_Fill(percentage_50_55  , 0 , 240  , 5 , DARKBLUE);
	}else if(getElectr >= 45 && getElectr < 50)
	{
			LCD_Fill(0  , 0 , percentage_45_50  , 5 , GREEN);
			LCD_Fill(percentage_45_50  , 0 , 240  , 5 , DARKBLUE);
	}else if(getElectr >= 40 && getElectr < 45)
	{
			LCD_Fill(0  , 0 , percentage_40_45  , 5 , GREEN);
			LCD_Fill(percentage_40_45  , 0 , 240  , 5 , DARKBLUE);
	}else if(getElectr >= 35 && getElectr < 40)
	{
			LCD_Fill(0  , 0 , percentage_35_40  , 5 , GREEN);
			LCD_Fill(percentage_35_40  , 0 , 240  , 5 , DARKBLUE);
	}else if(getElectr >= 30 && getElectr < 35)
	{
			LCD_Fill(0  , 0 , percentage_30_35  , 5 , GREEN);
			LCD_Fill(percentage_30_35  , 0 , 240  , 5 , DARKBLUE);
	}else if(getElectr >= 25 && getElectr < 30)
	{
			LCD_Fill(0  , 0 , percentage_25_30  , 5 , GREEN);
			LCD_Fill(percentage_25_30  , 0 , 240  , 5 , DARKBLUE);
	}else if(getElectr >= 20 && getElectr < 25)
	{
			LCD_Fill(0  , 0 , percentage_20_25  , 5 , GREEN);
			LCD_Fill(percentage_20_25  , 0 , 240  , 5 , DARKBLUE);
	}else if(getElectr >= 15 && getElectr < 20)
	{		
			LCD_Fill(0  , 0 , percentage_15_20  , 5 , GREEN);
			LCD_Fill(percentage_15_20  , 0 , 240  , 5 , DARKBLUE);
	}else if(getElectr >= 10 && getElectr < 15)
	{
			LCD_Fill(0  , 0 , percentage_10_15  , 5 , GREEN);
			LCD_Fill(percentage_10_15  , 0 , 240  , 5 , DARKBLUE);
	}else if(getElectr >= 5 && getElectr < 10)
	{
			LCD_Fill(0  , 0 , percentage_5_10  , 5 , GREEN);
			LCD_Fill(percentage_5_10  , 0 , 240  , 5 , DARKBLUE);
	}
}


/*
*********************************************************************************************************
*	函 数 名: DISPlay_Battery_Voltage
*	功能说明: 电压
*	形    参: 无
*	返 回 值: 无
* 优 先 级:   
* 其		他: 电压只有正值
*********************************************************************************************************
*/
void DISPlay_Battery_Voltage(unsigned short getvol)
{
	//float getvoldata = getvol * 0.001;
	unsigned short getnumber = getvol;
	unsigned char Num = 0;
	//double FloatNum = 0.00;
	//double fractpart = modf(getvoldata, &FloatNum);  //求3.1415的小数部分
	unsigned char ydata = 7;
	unsigned char xdata = 0;
	const unsigned char str[3] = "mV";
	//LCD_ShowChinese(0 , ydata , "电压", WHITE , DARKBLUE , 16 , 0);
	xdata = 65;
	LCD_ShowChar(xdata , ydata , '+' , WHITE , DARKBLUE , 16 , 0);
	xdata = xdata + 10;
	LCD_ShowIntNum(xdata , ydata , getnumber , 5 ,WHITE , DARKBLUE ,16);
//	LCD_ShowIntNum(xdata , ydata , FloatNum , 2 ,WHITE , DARKBLUE ,16);
//	xdata = xdata + 20;
//	LCD_ShowFloatNum1(xdata , ydata , fractpart , 2 , WHITE , DARKBLUE ,16);
	xdata = xdata + 40;
	LCD_ShowString(xdata , ydata , str , WHITE , DARKBLUE , 16 , 0);
}


/*
*********************************************************************************************************
*	函 数 名: DISPlay_Battery_electric_current
*	功能说明: 电流
*	形    参: 无
*	返 回 值: 无
* 优 先 级:   
* 其		他: 电流有正值和负值
*********************************************************************************************************
*/
void DISPlay_Battery_electric_current(unsigned short getcul)
{
	unsigned char symbol = getcul >> 15;
	unsigned char ydata = 7;
	unsigned char xdata = 150;
	unsigned char getcul_negative_number = getcul;
	const unsigned char str[3] = "mA";
	
	xdata = 165;
	LCD_ShowChar(xdata , ydata , '(' , WHITE , DARKBLUE , 16 , 0);
	
	xdata = 213;
	LCD_ShowChar(xdata , ydata , ')' , WHITE , DARKBLUE , 16 , 0);	
	
	if(symbol == 1)
	{//-
		getcul_negative_number = ~(getcul_negative_number - 1);
		xdata = 175;
		LCD_ShowChar(xdata , ydata , '-' , WHITE , DARKBLUE , 16 , 0);
	}
	else
	{//+
		xdata = 170;
		LCD_ShowChar(xdata , ydata , '+' , WHITE , DARKBLUE , 16 , 0);
	}
		xdata = 180;
		//LCD_ShowIntNum(xdata , ydata , 9999 , 4 , WHITE , DARKBLUE , 16);	
		LCD_ShowIntNum(xdata , ydata , getcul_negative_number , 4 , WHITE , DARKBLUE , 16);	
		xdata = 220;
		LCD_ShowString(xdata , ydata , str , WHITE , DARKBLUE , 16 , 0);
}



void DISPlay_Title(void)
{
	const unsigned char str[4] = "DYT";
	unsigned char chinese1[13] = "室外测试系统";
	unsigned char chinese2[21] = "西安莱凯光电有限公司";
	LCD_ShowString(5 , 5 , str , WHITE , DARKBLUE , 24 , 0);
	LCD_ShowChinese(20 , 30 , chinese1, WHITE , DARKBLUE , 32 , 0);
	LCD_ShowChinese(0 , 260 , chinese2, WHITE , DARKBLUE , 24 , 0);	
}

/*
*********************************************************************************************************
*	函 数 名: DISPlay_Function_1
*	功能说明: 一级菜单-1
*	形    参: 无
*	返 回 值: 无
* 优 先 级:   
* 其		他: 电压只有正值
*********************************************************************************************************
*/
void DISPlay_Function_1(unsigned char selected)
{
	unsigned char getselected = selected;
	unsigned char chinese1[5] = "激光";
	const unsigned char str[4] = "DYT";
	if(getselected == 1)
	{
		LCD_ShowString(130 , 80 , str , DARKBLUE , WHITE , 24 , 0);
		LCD_ShowChar(165 , 80 , '-' , DARKBLUE , WHITE , 24 , 0);
		LCD_ShowChinese(175 , 80 , chinese1 , DARKBLUE , WHITE , 24 , 0);
	}else
	{
		LCD_ShowString(130 , 80 , str , WHITE , DARKBLUE , 24 , 0);
		LCD_ShowChar(165 , 80 , '-' , WHITE , DARKBLUE , 24 , 0);
		LCD_ShowChinese(175 , 80 , chinese1 , WHITE , DARKBLUE , 24 , 0);
	}
}


/*
*********************************************************************************************************
*	函 数 名: DISPlay_Function_2
*	功能说明: 一级菜单-2
*	形    参: 无
*	返 回 值: 无
* 优 先 级:   
* 其		他: 电压只有正值
*********************************************************************************************************
*/
void DISPlay_Function_2(unsigned char selected)
{
	unsigned char getselected = selected;	
	unsigned char chinese1[9] = "相机控制";
	if(getselected == 1)
	{
		LCD_ShowChinese(130 , 120 , chinese1, DARKBLUE , WHITE , 24 , 0);
	}
	else
	{
		LCD_ShowChinese(130 , 120 , chinese1, WHITE , DARKBLUE , 24 , 0);
	}
}


/*
*********************************************************************************************************
*	函 数 名: DISPlay_Function_3
*	功能说明: 一级菜单-3
*	形    参: 无
*	返 回 值: 无
* 优 先 级:   
* 其		他: 电压只有正值
*********************************************************************************************************
*/
void DISPlay_Function_3(unsigned char selected)
{
	unsigned char getselected = selected;	
	unsigned char chinese1[9] = "循环散热";
	if(getselected == 1)
	{
		LCD_ShowChinese(130 , 160 , chinese1, DARKBLUE , WHITE , 24 , 0);
	}
	else
	{
		LCD_ShowChinese(130 , 160 , chinese1, WHITE , DARKBLUE , 24 , 0);
	}

}


void DISPlay_self_test()
{
	unsigned char chinese1[9] = "自检通过";
	LCD_ShowChinese(5 , 80 , chinese1 , BLACK , GREEN , 24 , 0);	
}


/*
*********************************************************************************************************
*	函 数 名: DISPlay_Function_4
*	功能说明: 一级菜单-4
*	形    参: 无
*	返 回 值: 无
* 优 先 级:   
* 其		他: 电压只有正值
*********************************************************************************************************
*/
void DISPlay_Function_4(unsigned char selected)
{
	unsigned char getselected = selected;	
	unsigned char chinese1[9] = "程控模式";
	if(getselected == 1)
	{
		LCD_ShowChinese(130 , 200 , chinese1, DARKBLUE , WHITE , 24 , 0);
	}
	else
	{
		LCD_ShowChinese(130 , 200 , chinese1, WHITE , DARKBLUE , 24 , 0);
	}
}

/*
*********************************************************************************************************
*	函 数 名: UI_CilckFun
*	功能说明: 一级UI切换
*	形    参: 无
*	返 回 值: 无
* 优 先 级:   
* 其		他: 
*********************************************************************************************************
*/
unsigned char UI_CilckFun(unsigned char cilck)
{
	unsigned char getcilck = cilck;
	unsigned char ucreturn = 0;
	switch(getcilck)
	{
		case 1:
			DISPlay_Function_1(1);
			DISPlay_Function_2(0);
			DISPlay_Function_3(0);
			DISPlay_Function_4(0);	
			ucreturn = 1;		
			break;
		
		case 2:
			DISPlay_Function_1(0);
			DISPlay_Function_2(1);
			DISPlay_Function_3(0);
			DISPlay_Function_4(0);
			ucreturn = 2;		
			break;
		
		case 3:
			DISPlay_Function_1(0);
			DISPlay_Function_2(0);
			DISPlay_Function_3(1);
			DISPlay_Function_4(0);
			ucreturn = 3;		
			break;
		
		case 4:
			DISPlay_Function_1(0);
			DISPlay_Function_2(0);
			DISPlay_Function_3(0);
			DISPlay_Function_4(1);
			ucreturn = 4;		
			break;
		
		default:
			ucreturn = 0;	
			break;
	}
	return ucreturn;
}




/*
*********************************************************************************************************
*	函 数 名: 
*	功能说明: 
*	形    参: 无
*	返 回 值: 无
* 优 先 级:   
* 其		他: 
*********************************************************************************************************
*/
void DISPlay_image_park(enum DYTState dyts , enum DYTPlace dytp)
{
	unsigned char ydata = 7;
	unsigned char xdata = 60;	
	unsigned char draw_y = 175;
	unsigned char draw_x = 60;
	if(dyts == initialize)
	{
		LCD_DrawCircle(60 , 175 , 15 , WHITE);					//激光实心圆
		Draw_Circle(xdata , 175 , 60 , WHITE);				//空心圆	
		LCD_DrawLine(0 , 175 , 120 , 175 , WHITE);			//x轴
		LCD_DrawLine(xdata, 115 , xdata , 235 , WHITE);	//y轴
	}
	else if(dyts == capture)
	{
		Draw_Circle(xdata , 175 , 60 , WHITE);					//空心圆	
		LCD_DrawLine(0 , 175 , 120 , 175 , WHITE);			//x轴
		LCD_DrawLine(xdata, 115 , xdata , 235 , WHITE);	//y轴		
		switch(dytp)
		{
			case center: //中心
				LCD_DrawCircle(draw_x , draw_y , 15 , GREEN);
				break;
			
			case north://北
				draw_y = draw_y - 35;
				LCD_DrawCircle(draw_x , draw_y , 15 , GREEN);				
				break;
			
			case south://南
				draw_y = draw_y + 35;
				LCD_DrawCircle(draw_x , draw_y , 15 , GREEN);		
				break;
			
			case west://西
				draw_x = draw_x - 35;
				LCD_DrawCircle(draw_x , draw_y , 15 , GREEN);									
				break;
			
			case east://东
				draw_x = draw_x + 35;
				LCD_DrawCircle(draw_x , draw_y , 15 , GREEN);		
				break;
			
			case north_by_west://北偏西
				draw_y = draw_y - 27;
				draw_x = draw_x - 27;
				LCD_DrawCircle(draw_x , draw_y , 15 , GREEN);		
				break;
			
			case north_by_east://北偏东
				draw_y = draw_y - 27;
				draw_x = draw_x + 27;
				LCD_DrawCircle(draw_x , draw_y , 15 , GREEN);	
				break;
			
			case south_by_west://南偏西
				draw_y = draw_y + 27;
				draw_x = draw_x - 27;
				LCD_DrawCircle(draw_x , draw_y , 15 , GREEN);		
				break;
			
			case south_by_east://南偏东
				draw_y = draw_y + 27;
				draw_x = draw_x + 27;
				LCD_DrawCircle(draw_x , draw_y , 15 , GREEN);		
				break;	
			
			default:
				break;
		}
	}
	else if(dyts == not_caught)
	{
		Draw_Circle(xdata , 175 , 60 , WHITE);					//空心圆	
		LCD_DrawLine(0 , 175 , 120 , 175 , WHITE);			//x轴
		LCD_DrawLine(xdata, 115 , xdata , 235 , WHITE);	//y轴		
		switch(dytp)
		{
			case center: //中心
				LCD_DrawCircle(draw_x , draw_y , 15 , RED);
				break;
			
			case north://北
				draw_y = draw_y - 35;
				LCD_DrawCircle(draw_x , draw_y , 15 , RED);				
				break;
			
			case south://南
				draw_y = draw_y + 35;
				LCD_DrawCircle(draw_x , draw_y , 15 , RED);		
				break;
			
			case west://西
				draw_x = draw_x - 35;
				LCD_DrawCircle(draw_x , draw_y , 15 , RED);									
				break;
			
			case east://东
				draw_x = draw_x + 35;
				LCD_DrawCircle(draw_x , draw_y , 15 , RED);		
				break;
			
			case north_by_west://北偏西
				draw_y = draw_y - 27;
				draw_x = draw_x - 27;
				LCD_DrawCircle(draw_x , draw_y , 15 , RED);		
				break;
			
			case north_by_east://北偏东
				draw_y = draw_y - 27;
				draw_x = draw_x + 27;
				LCD_DrawCircle(draw_x , draw_y , 15 , RED);	
				break;
			
			case south_by_west://南偏西
				draw_y = draw_y + 27;
				draw_x = draw_x - 27;
				LCD_DrawCircle(draw_x , draw_y , 15 , RED);		
				break;
			
			case south_by_east://南偏东
				draw_y = draw_y + 27;
				draw_x = draw_x + 27;
				LCD_DrawCircle(draw_x , draw_y , 15 , RED);		
				break;	
			
			default:
				break;
		}		
	}
}




/*
*********************************************************************************************************
*	函 数 名: LCD_DrawCircle
*	功能说明: 画实心圆
*	形    参: 无
*	返 回 值: 无
* 优 先 级:   
* 其		他: 
*********************************************************************************************************
*/
void LCD_DrawCircle(int xc,int yc,int r,int color)
{
    int x,y,d;
    y = r;
    d = 3 - (r + r);
    x = 0;
    while(x <= y)
    {
			LCD_DrawLine(xc+x,yc+y,xc-x,yc+y,color);
			LCD_DrawLine(xc+x,yc-y,xc-x,yc-y,color);
			LCD_DrawLine(xc+y,yc+x,xc-y,yc+x,color);
			LCD_DrawLine(xc+y,yc-x,xc-y,yc-x,color);                       
			if(d < 0)
			{
				d += 4*x + 6;
			}
			else
			{
				d+=4*(x - y)+ 10;
				y --;
			}
			x ++;
    }
}

