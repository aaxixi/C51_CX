#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
uint k;
unsigned char table1[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
unsigned char table2[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
uint i;
void delay()
{
	uchar a,b;
	for(a=0;a<250;a++)
	{
		for(b=0;b<245;b++);
	}
}
void init_timer0()
{
	TMOD|=0x01;
	TH0=0x00;
	TL0=0x00;
	EA=1;
	ET0=1;
	TR0=1;
}


void timer0_server() interrupt 1
{

	k++;
	TH0=0x00;
	TL0=0x00;	
}



void main()
{	
	uint num;
	num=0;
	init_timer0();
	while(1)
	{
		if(k==20)
		{
			
			k=0;
			P0=table1[num];
		    P2=table2[num];
			num++;
		}
	}
	
}


