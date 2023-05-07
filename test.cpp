#include <reg51.h>
#include <intrins.h>  
#define uchar unsigned char
#define uint unsigned int 
void delay_long(uint);
void delay_1ms();
void T0_time();
void key_service();
void key_scan();
void display1();
void display2();
void display3();
void display4();
void display11();
void display22();
void display33();
void display44();
void display55();
void display66();
unsigned char const discode[] = { 0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F };
xdata uchar wei _at_ 0x8002;
xdata uchar duan _at_ 0x8004;
sbit key1 = P3 ^ 0;
sbit key2 = P3 ^ 1;
sbit key3 = P3 ^ 2;
sbit key4 = P3 ^ 3;
sbit left = P1 ^ 0; sbit left2 = P1 ^ 1; sbit left3 = P1 ^ 2;
sbit right = P1 ^ 3; sbit right2 = P1 ^ 4; sbit right3 = P1 ^ 5;
unsigned int ucKeySec = 0;
unsigned int i = 0; uidisplayTimeCnt1 = 0;
unsigned int temp = 0;
void main() //主函数 
{
	P1 = 0x00;
	TMOD = 0x01; //定时器选择方式一
	TH0 = 0xf8;//设置定时器初值
	TL0 = 0x80;//溢出时间为0.5ms   
	EA = 1;//开中断 
	ET0 = 1;//开定时器0中断   
	TR0 = 1;
	while (1)//等待中断
	{
		key_service();
	}
}
void key_scan()
{
	if (key1 == 0)
	{
		while (!key1);
		if (key1 == 1)
		{
			ucKeySec = 1;
		}
	}
	if (key2 == 0)
	{
		while (!key2);
		if (key2 == 1)
		{
			ucKeySec = 2;
		}
	}
	if (key3 == 0)
	{
		while (!key3);
		if (key3 == 1)
		{
			ucKeySec = 3;
		}
	}
	if (key4 == 0)
	{
		while (!key4);
		if (key4 == 1)
		{
			ucKeySec = 4;
		}
	}
}
void key_service()
{
	switch (ucKeySec)
	{
	case 1:
		while (ucKeySec == 1)
		{
			display1();
			ucKeySec = 0;
		}
		break;
	case 2:
		while (ucKeySec == 2)
		{
			display2();
			ucKeySec = 0;
		}
		break;
	case 3:
		while (ucKeySec == 3)
		{
			display3();
			ucKeySec = 0;
		}
		break;
	case 4:
		while (ucKeySec == 4)
		{
			display4();
			ucKeySec = 0;
		}
		break;
	}
}
void T0_time() interrupt 1
{
	TF0 = 0;//清除中断标志位  
	TR0 = 0; //关中断
	key_scan();
	TH0 = 0xf8;//设置定时器初值
	TL0 = 0x80;//溢出时间为0.5ms
	TR0 = 1;// 开中断
}
void delay_1ms()
{
	unsigned int i, j;
	for (i = 0; i < 10; i++)
		for (j = 0; j < 33; j++)
			;//相当于汇编语言中Nop操作
}
void delay_long(unsigned int uiDelayLong)
{
	unsigned int i;
	for (i = 0; i < uiDelayLong; i++)
		delay_1ms();
}
void display1()
{
	unsigned  int  temp, i;
	i = 0;
	for (temp = 0; temp < 10; temp++)
	{
		wei = 0x20;//数码管位选
		duan = discode[temp];
		delay_long(333);
		i++;
		if (i == 1)left3 = 1;
		if (i == 2)left2 = 1;
		if (i == 3)left = 1;
		if (ucKeySec == 2)
		{
			left = 0; left2 = 0; left3 = 0;
			display22();
			break;
		}
		if (ucKeySec == 3 || i > 9)
		{
			display33();
			break;
		}
		if (ucKeySec == 4)
		{
			display55();
			break;
		}
	}
}
void display2()
{
	unsigned  int  temp, i;
	i = 0;
	for (temp = 0; temp < 10; temp++)
	{
		wei = 0x20;//位码有效
		duan = discode[temp];//段码有效
		delay_long(333);//延时1秒
		i++;
		if (i == 1)right = 1;
		if (i == 2)right2 = 1;
		if (i == 3)right3 = 1;
		if (ucKeySec == 1)
		{
			right = 0; right2 = 0; right3 = 0;
			display11();
			break;
		}
		if (ucKeySec == 3 || i > 9)//如果在右转时按下正常行驶键
		{
			display33();
			break;
		}
		if (ucKeySec == 4)//如果在右转时按下刹车键
		{
			display66();
			break;
		}
	}
}
void display3()
{
	unsigned  int  temp;
	for (temp = 0; temp < 100; temp++)
	{
		wei = 0x20;//位码有效
		duan = discode[0];//段码有效
		delay_long(333);//延时1秒
		left = 0; left2 = 0; left3 = 0;
		right = 0; right2 = 0; right3 = 0;
		if (ucKeySec == 1)
		{
			display11();
			break;
		}
		if (ucKeySec == 2)
		{
			display22();
			break;
		}
		if (ucKeySec == 4)
		{
			display44();
			break;
		}
	}
}
void display4()
{
	unsigned  int  temp, i;
	i = 0;
	for (temp = 0; temp < 10; temp++)
	{
		wei = 0x20;//位码有效
		duan = discode[temp];//段码有效
		delay_long(166);//延时0.5秒
		left = 1; left2 = 1; left3 = 1;//6只尾灯同时点亮
		right = 1; right2 = 1; right3 = 1;
		delay_long(166);//延时0.5秒
		left = 0; left2 = 0; left3 = 0;//6只尾灯同时熄灭
		right = 0; right2 = 0; right3 = 0;
		i++;
		if (ucKeySec == 1)//如果在正常行驶时按下左转键
		{
			display11();
			break;
		}
		if (ucKeySec == 2)//如果在正常行驶时按下右转键
		{
			display22();
			break;
		}
		if (ucKeySec == 3 || i > 9)//如果在刹车时按下正常行驶键
		{
			display33();
			break;//退出循环
		}
	}
}
void display11()
{
	unsigned  int  temp, i;
	i = 0;
	left = 0; left2 = 0; left3 = 0;//6只尾灯同时熄灭
	right = 0; right2 = 0; right3 = 0;
	for (temp = 0; temp < 10; temp++)
	{
		wei = 0x20;//数码管位选
		duan = discode[temp];
		delay_long(333);
		i++;
		if (i == 1)left3 = 1;//第一秒时，左侧第一个尾灯亮
		if (i == 2)left2 = 1;//第二秒时，左侧第二个尾灯亮
		if (i == 3)left = 1;//第三秒时，左侧第三个尾灯亮
		if (i > 9)//大于9则超过十秒需要关闭尾灯，
		{
			left = 0; left2 = 0; left3 = 0;//关闭尾灯
			duan = discode[0];//数码管置0
			break;//退出循环
		}
	}
}
void display22()
{
	unsigned  int  temp, i;
	i = 0;
	left = 0; left2 = 0; left3 = 0;//6只尾灯同时熄灭
	right = 0; right2 = 0; right3 = 0;
	for (temp = 0; temp < 10; temp++)
	{
		wei = 0x20;//位码有效
		duan = discode[temp];//段码有效
		delay_long(333);//延时1秒
		i++;
		if (i == 1)right = 1;//第一秒时右侧第一个尾灯亮
		if (i == 2)right2 = 1;//第三秒时右侧第二个尾灯亮
		if (i == 3)right3 = 1;//第五秒时右侧第三尾灯亮
		if (i > 9)//如果数码管数字大于9，则计时超过十秒
		{
			right = 0; right2 = 0; right3 = 0;//右侧尾灯关闭
			duan = discode[0];//数码管置0
			break;
		}
	}
}
void display33()
{
	wei = 0x20;//位码有效
	duan = discode[0];//段码有效
	left = 0; left2 = 0; left3 = 0;
	right = 0; right2 = 0; right3 = 0;
}
void display44()
{
	unsigned  int  temp, i;
	i = 0;
	left = 0; left2 = 0; left3 = 0;//6只尾灯同时熄灭
	right = 0; right2 = 0; right3 = 0;
	for (temp = 0; temp < 10; temp++)
	{
		wei = 0x20;//位码有效
		duan = discode[temp];//段码有效
		delay_long(166);//延时0.5秒
		left = 1; left2 = 1; left3 = 1;//6只尾灯同时点亮
		right = 1; right2 = 1; right3 = 1;
		delay_long(166);//延时0.5秒
		left = 0; left2 = 0; left3 = 0;//6只尾灯同时熄灭
		right = 0; right2 = 0; right3 = 0;
		i++;
		if (i > 9)//如果数码管数字大于9，则计时超过十秒
		{
			duan = discode[0];//数码管置0
			break;//退出循环
		}
	}
}
void display55()
{
	unsigned  int  temp, i;
	i = 0;
	left = 0; left2 = 0; left3 = 0;//6只尾灯同时熄灭
	right = 0; right2 = 0; right3 = 0;
	for (temp = 0; temp < 10; temp++)
	{
		wei = 0x20;//位码有效
		duan = discode[temp];//段码有效
		delay_long(166);//延时0.5秒
		left = 1; left3 = 1;//3只尾灯同时点亮
		right2 = 1;
		delay_long(166);//延时0.5秒
		left = 0; left3 = 0;//3只尾灯同时熄灭
		right2 = 0;
		i++;
		if (i > 9)//如果数码管数字大于9，则计时超过十秒
		{
			duan = discode[0];//数码管置0
			break;//退出循环
		}
	}
}
void display66()
{
	unsigned  int  temp, i;
	i = 0;
	left = 0; left2 = 0; left3 = 0;//6只尾灯同时熄灭
	right = 0; right2 = 0; right3 = 0;
	for (temp = 0; temp < 10; temp++)
	{
		wei = 0x20;//位码有效
		duan = discode[temp];//段码有效
		delay_long(166);//延时0.5秒
		left2 = 1;//6只尾灯同时点亮
		right = 1; right3 = 1;
		delay_long(166);//延时0.5秒
		left2 = 0;//6只尾灯同时熄灭
		right = 0; right3 = 0;
		i++;
		if (i > 9)
		{
			duan = discode[0];
			break;
		}
	}
}