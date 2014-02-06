#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
uint k;
uint num;
uint num_hour,num_hour1,num_hou1,num_hou;
uint num_mine,num_mine1,num_min1,num_min;
uint num_seco,num_seco1;
unsigned char table_num[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x40};
unsigned char table_wei[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
uint i;
void delay()
{
	uchar a,b;
	for(a=0;a<25;a++)
	{
		for(b=0;b<24;b++);
	}
}
void init_timer0()
{
	TMOD|=0x01;
	TH0=(65536-50000);
	TL0=(65536-50000);
	EA=1;
	ET0=1;
	TR0=1;
}


void timer0_server() interrupt 1
{

	k++;
	TH0=(65536-50000);
	TL0=(65536-50000);	
}


void display()
{
	num_seco1=num/10;
	num_seco=num%10;
	num_min1=num_mine/10;
	num_min=num_mine%10;
	num_hou1=num_hour/10;
	num_hou=num_hour%10;
	P0=0x40;
	P2=0x20;
	delay();
	P0=0x40;
	P2=0x04;
	delay();
	P0=table_num[num_seco];
	P2=0x80;
	delay();
	P0=table_num[num_seco1];
	P2=0x40;
	delay();
	P0=table_num[num_min];
	P2=0x10; 
	delay();
	P0=table_num[num_min1];
	P2=0x08;
	delay();
	P0=table_num[num_hou];
	P2=0x02;
	delay();
	P0=table_num[num_hou1];
	P2=0x01;
	delay();				
}
void main()
{	

	num=0;
	init_timer0();
	while(1)
	{
		if(k==80)
		{
			
			k=0;
			num++;
			if(num==60)
			{
				num=0;
				num_mine++;
				if(num_mine==60)
				{
					num_mine=0;
					num_hour++;
					if(num_hour==24)
					{
						num_hour=0;
					}	
				}	
			}
		}

		display();
	}
	
}



