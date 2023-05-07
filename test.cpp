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
void main() //������ 
{
	P1 = 0x00;
	TMOD = 0x01; //��ʱ��ѡ��ʽһ
	TH0 = 0xf8;//���ö�ʱ����ֵ
	TL0 = 0x80;//���ʱ��Ϊ0.5ms   
	EA = 1;//���ж� 
	ET0 = 1;//����ʱ��0�ж�   
	TR0 = 1;
	while (1)//�ȴ��ж�
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
	TF0 = 0;//����жϱ�־λ  
	TR0 = 0; //���ж�
	key_scan();
	TH0 = 0xf8;//���ö�ʱ����ֵ
	TL0 = 0x80;//���ʱ��Ϊ0.5ms
	TR0 = 1;// ���ж�
}
void delay_1ms()
{
	unsigned int i, j;
	for (i = 0; i < 10; i++)
		for (j = 0; j < 33; j++)
			;//�൱�ڻ��������Nop����
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
		wei = 0x20;//�����λѡ
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
		wei = 0x20;//λ����Ч
		duan = discode[temp];//������Ч
		delay_long(333);//��ʱ1��
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
		if (ucKeySec == 3 || i > 9)//�������תʱ����������ʻ��
		{
			display33();
			break;
		}
		if (ucKeySec == 4)//�������תʱ����ɲ����
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
		wei = 0x20;//λ����Ч
		duan = discode[0];//������Ч
		delay_long(333);//��ʱ1��
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
		wei = 0x20;//λ����Ч
		duan = discode[temp];//������Ч
		delay_long(166);//��ʱ0.5��
		left = 1; left2 = 1; left3 = 1;//6ֻβ��ͬʱ����
		right = 1; right2 = 1; right3 = 1;
		delay_long(166);//��ʱ0.5��
		left = 0; left2 = 0; left3 = 0;//6ֻβ��ͬʱϨ��
		right = 0; right2 = 0; right3 = 0;
		i++;
		if (ucKeySec == 1)//�����������ʻʱ������ת��
		{
			display11();
			break;
		}
		if (ucKeySec == 2)//�����������ʻʱ������ת��
		{
			display22();
			break;
		}
		if (ucKeySec == 3 || i > 9)//�����ɲ��ʱ����������ʻ��
		{
			display33();
			break;//�˳�ѭ��
		}
	}
}
void display11()
{
	unsigned  int  temp, i;
	i = 0;
	left = 0; left2 = 0; left3 = 0;//6ֻβ��ͬʱϨ��
	right = 0; right2 = 0; right3 = 0;
	for (temp = 0; temp < 10; temp++)
	{
		wei = 0x20;//�����λѡ
		duan = discode[temp];
		delay_long(333);
		i++;
		if (i == 1)left3 = 1;//��һ��ʱ������һ��β����
		if (i == 2)left2 = 1;//�ڶ���ʱ�����ڶ���β����
		if (i == 3)left = 1;//������ʱ����������β����
		if (i > 9)//����9�򳬹�ʮ����Ҫ�ر�β�ƣ�
		{
			left = 0; left2 = 0; left3 = 0;//�ر�β��
			duan = discode[0];//�������0
			break;//�˳�ѭ��
		}
	}
}
void display22()
{
	unsigned  int  temp, i;
	i = 0;
	left = 0; left2 = 0; left3 = 0;//6ֻβ��ͬʱϨ��
	right = 0; right2 = 0; right3 = 0;
	for (temp = 0; temp < 10; temp++)
	{
		wei = 0x20;//λ����Ч
		duan = discode[temp];//������Ч
		delay_long(333);//��ʱ1��
		i++;
		if (i == 1)right = 1;//��һ��ʱ�Ҳ��һ��β����
		if (i == 2)right2 = 1;//������ʱ�Ҳ�ڶ���β����
		if (i == 3)right3 = 1;//������ʱ�Ҳ����β����
		if (i > 9)//�����������ִ���9�����ʱ����ʮ��
		{
			right = 0; right2 = 0; right3 = 0;//�Ҳ�β�ƹر�
			duan = discode[0];//�������0
			break;
		}
	}
}
void display33()
{
	wei = 0x20;//λ����Ч
	duan = discode[0];//������Ч
	left = 0; left2 = 0; left3 = 0;
	right = 0; right2 = 0; right3 = 0;
}
void display44()
{
	unsigned  int  temp, i;
	i = 0;
	left = 0; left2 = 0; left3 = 0;//6ֻβ��ͬʱϨ��
	right = 0; right2 = 0; right3 = 0;
	for (temp = 0; temp < 10; temp++)
	{
		wei = 0x20;//λ����Ч
		duan = discode[temp];//������Ч
		delay_long(166);//��ʱ0.5��
		left = 1; left2 = 1; left3 = 1;//6ֻβ��ͬʱ����
		right = 1; right2 = 1; right3 = 1;
		delay_long(166);//��ʱ0.5��
		left = 0; left2 = 0; left3 = 0;//6ֻβ��ͬʱϨ��
		right = 0; right2 = 0; right3 = 0;
		i++;
		if (i > 9)//�����������ִ���9�����ʱ����ʮ��
		{
			duan = discode[0];//�������0
			break;//�˳�ѭ��
		}
	}
}
void display55()
{
	unsigned  int  temp, i;
	i = 0;
	left = 0; left2 = 0; left3 = 0;//6ֻβ��ͬʱϨ��
	right = 0; right2 = 0; right3 = 0;
	for (temp = 0; temp < 10; temp++)
	{
		wei = 0x20;//λ����Ч
		duan = discode[temp];//������Ч
		delay_long(166);//��ʱ0.5��
		left = 1; left3 = 1;//3ֻβ��ͬʱ����
		right2 = 1;
		delay_long(166);//��ʱ0.5��
		left = 0; left3 = 0;//3ֻβ��ͬʱϨ��
		right2 = 0;
		i++;
		if (i > 9)//�����������ִ���9�����ʱ����ʮ��
		{
			duan = discode[0];//�������0
			break;//�˳�ѭ��
		}
	}
}
void display66()
{
	unsigned  int  temp, i;
	i = 0;
	left = 0; left2 = 0; left3 = 0;//6ֻβ��ͬʱϨ��
	right = 0; right2 = 0; right3 = 0;
	for (temp = 0; temp < 10; temp++)
	{
		wei = 0x20;//λ����Ч
		duan = discode[temp];//������Ч
		delay_long(166);//��ʱ0.5��
		left2 = 1;//6ֻβ��ͬʱ����
		right = 1; right3 = 1;
		delay_long(166);//��ʱ0.5��
		left2 = 0;//6ֻβ��ͬʱϨ��
		right = 0; right3 = 0;
		i++;
		if (i > 9)
		{
			duan = discode[0];
			break;
		}
	}
}