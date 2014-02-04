#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
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
void timeing (i)
{
	i=0;
	while(1)
	{	
		i++;
		delay();
	}
}

//void display (i)
//{
//	P2=table1[i];
//	P0=table2[i];
//}  

void main()
{
	P2=table1[i];
	P0=table2[i];
	display();
	delay();
}


