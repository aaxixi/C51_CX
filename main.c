#include<reg52.h>
#include<string.h>
#define uchar unsigned char
#define uint unsigned int
sbit lcd_rs=P2^2;
sbit lcd_rw=P2^3;
sbit lcd_en=P2^4;

uchar table1[]=" i love you ";
uchar table2[]=" heluyao ";
void delay50us(uint t)   //?? 0us
{
    unsigned char a,b;
    for(b=t;b>0;b--)
        for(a=22;a>0;a--);
}

void writecom(uchar com)
{
	lcd_en=0;
	lcd_rs=0;
	lcd_rw=0;
	P3=com;
	delay50us(1);
	lcd_en=1;
	delay50us(15);
	lcd_en=0;
}

void writedate(uchar date)
{
	lcd_en=0;
	lcd_rs=1;
	lcd_rw=0;
	P3=date;
	delay50us(1);
	lcd_en=1;
	delay50us(15);
	lcd_en=0;	
}

void init ()
{
	delay50us(300);
	writecom(0x38);
	delay50us(100);
	writecom(0x38);
	delay50us(100);
	writecom(0x38);
	writecom(0x38);
	writecom(0x08);
	writecom(0x01);
    writecom(0x06);
	writecom(0x0c);
	
}



void DisPlay_char(int x,int y,char ch);
void Display_str(int x,int y,char* pstr);

void main()
{
	uchar j;
	init();
	writecom(0x80);
	for(j=0;j<16;j++)

	{
		writedate(table1[j]);
		delay50us(10);
	}
	writecom(0x80+0x40);
	for(j=0;j<16;j++)
	{
		writedate(table2[j]);
		delay50us(10);
	}
    
    Display_str(0,0,"this is test!!!more char!!");
	while(1);

}


void DisPlay_char(int x,int y,char ch)
{
	int a=0;
	if(y>0)
	{
		a = 0x40;
	}
	a = a+x;
	writecom(0x80+a);
	writedate(ch);
	delay50us(10);
}

void Display_str(int x,int y,char* pstr)
{
	int a=0;
	int str_len=0;
	int first_line_display_cnt=0;
	int second_line_display_cnt=0;
	int i=0;
	int temp=0;

	if(y==0)
	{
		first_line_display_cnt = 16-x;
		str_len = strlen(pstr);
		if(first_line_display_cnt>=str_len) 
		{
			for(i=0;i<str_len;i++)
			{
				DisPlay_char(x+i,y,pstr[i]);
			}
		}
		else
		{

			second_line_display_cnt = str_len - i;
			temp = i;
	
			if(second_line_display_cnt>16)
			{
				second_line_display_cnt = 16;
			}
			for(i=0;i<second_line_display_cnt;i++)
			{
				DisPlay_char(i,y+1,pstr[i+temp]);
			}
			
		}
	}
	
	else 
	{
		second_line_display_cnt = 16-x;
		str_len = strlen(pstr);
		if(first_line_display_cnt>=str_len) 
		{
			first_line_display_cnt = str_len;
		}
		
		for(i=0;i<first_line_display_cnt;i++)
		{
			DisPlay_char(x+i,y,pstr[i]);
		}
	}
	
}
