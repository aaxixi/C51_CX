#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
uint k;
unsigned char g_hour;
unsigned char g_minute;
unsigned char g_second;

//加code 是为了让这段数据不占用内存，因为单片机内存有限，而这些数据不用修改在flash中即可
code unsigned char table_num[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x40};
code unsigned char table_wei[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};

void delay()
{
	uchar a,b;
	for(a=0;a<10;a++)
	{
		for(b=0;b<10;b++);
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


void Count_add(void)
{
    if(k==80)
	{
        k=0;
        g_second++;
        //------判断秒是不是到了60
        if(g_second==60)
        {
            g_minute++;
            g_second = 0;
            //------判断分是不是到了60
            if(g_minute==60)
            {
                g_minute = 0;
                g_hour++;
                if(g_hour==24)
                {
                    g_hour = 0;
                }
            }
        }
        
        
    }
}
//---------------------------pos:表示显示的位置，num:表示显示的内容
void display_seg(unsigned char pos,unsigned char num)
{
    P2 = table_wei[pos];
    P0 = table_num[num];
    delay();
}


void ShowTime(  unsigned char hour,
                unsigned char minute,
                unsigned char second
             )
{
    //--------------------------hour
    display_seg(0,hour/10);
    display_seg(1,hour%10);
    display_seg(2,10);
    //--------------------------minute
    display_seg(3,minute/10);
    display_seg(4,minute%10);
    display_seg(5,10);
    //--------------------------second
    display_seg(6,second/10);
    display_seg(7,second%10);
    display_seg(5,10);
}

void main()
{	
	init_timer0();
	while(1)
	{
        Count_add();
		ShowTime(g_hour,g_minute,g_second);
	}
	
}



