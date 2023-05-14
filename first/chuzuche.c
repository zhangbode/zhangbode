//出租车计价器
//宏定义
#define uchar unsigned char
#define uint unsigned int

//头函数声明
#include "AT24C02.h"
#include "DS1302.h"
#include "Data.h"
#include "Lcd.h"
#include <reg52.h>

//键盘定义
sbit K1 = P3 ^ 4; //模式切换
sbit K2 = P3 ^ 6; //减按键
sbit K3 = P3 ^ 5; //加按键
sbit K4 = P3 ^ 7; //万年历模式时：设置时间信息。计价器模式时：设置单价

//模式0时钟 1时钟调整
uchar Mode = 0;
//时钟屏幕调整
uchar Wei = 0;
uchar SS = 0;
//价格调整
uchar JGWei = 0;

//计价器参数
uint Day = 0;
uint Night = 0;
uint DanJia = 0;
uint DJ_min = 0;
uint ZJ = 0;
unsigned long GL = 0;
uint Time = 0;
uint count = 0;
uchar m = 0;
//白天/晚上
uchar DN = 0;
//公里/时间
uchar GT = 0;

//初始化函数
void InitTimer0();
//写初值
void SETS();
//读初值
void READS();

//主函数
void main()
{
    //初始化
    Ds1302_Init();
    Init_LCD();
    initeeprom();
    // SETS();
    //读取初始参数
    READS();
    //定时器初始化
    InitTimer0();
    //循环
    while (1)
    {
        //时钟模式
        if (Mode == 0)
        {
            //读时间
            if (Wei == 0)
            {
                Ds1302_Read_Time();
                //显示时间
                display_NYR(time_buf1, Wei, 0);
            }
        }
        else if (Mode == 1)
        {
            if (time_buf1[4] >= 23 || time_buf1[4] < 7)
                DN = 1;
            else
                DN = 0;
            //显示计价器信息

            display_S(Day, Night, DanJia, ZJ, GL / 10, Time, GT, DN);
        }

        if (K4 == 0)
        {
            delay(100);
            //调时
            if (Mode == 0)
            {
                Wei++;
                if (Wei == 1)
                {
                    SS = 1;
                }
                //闪烁
                display_NYR(time_buf1, Wei, SS);
                if (Wei == 7)
                {
                    Wei = 0;
                    //保存时间
                    Ds1302_Write_Time();
                    Init_LCD();
                }
            }
            else if (Mode == 1)
            {
                JGWei++;
                if (JGWei == 1)
                {
                    Mode = 2;
                    //显示计价器价格
                    Init_LCD_JGTZ();
                    display_D(Day, Night, DanJia, JGWei, DJ_min);
                }
            }
            else if (Mode == 2)
            {
                JGWei++;
                display_D(Day, Night, DanJia, JGWei, DJ_min);
                if (JGWei == 5)
                {
                    Mode = 1;
                    JGWei = 0;
                    //参数初始化
                    //保存
                    SETS();
                    //读初值
                    READS();

                    ZJ = 0;
                    GL = 0;
                    Time = 0;
                    //开启定时器
                    TR0 = 1;
                    //显示计价器
                    Init_LCD_JJQ();
                }
            }
            while (K4 == 0)
                ;
        }
        //+
        if (K3 == 0)
        {
            delay(100);
            //调时
            if (Mode == 0)
            {
                //年
                if (Wei == 1)
                {
                    time_buf1[1]++;
                    if (time_buf1[1] >= 100)
                        time_buf1[1] = 0;
                }
                //月
                else if (Wei == 2)
                {
                    time_buf1[2]++;
                    if (time_buf1[2] >= 13)
                        time_buf1[2] = 1;
                }
                //日
                else if (Wei == 3)
                {
                    time_buf1[3]++;
                    if (time_buf1[3] >= YDay(time_buf1[1], time_buf1[2]) + 1)
                        time_buf1[3] = 1;
                }
                //时
                else if (Wei == 4)
                {
                    time_buf1[4]++;
                    if (time_buf1[4] >= 24)
                        time_buf1[4] = 0;
                }
                //分
                else if (Wei == 5)
                {
                    time_buf1[5]++;
                    if (time_buf1[5] >= 60)
                        time_buf1[5] = 0;
                }
                //秒
                else if (Wei == 6)
                {
                    time_buf1[6]++;
                    if (time_buf1[6] >= 60)
                        time_buf1[6] = 0;
                }
                //显示
                if (Wei != 0)
                    display_NYR(time_buf1, Wei, SS);
            }
            //调价
            else if (Mode == 2)
            {
                //单价
                if (JGWei == 1)
                {
                    DanJia++;
                    if (DanJia > 999)
                    {
                        DanJia = 1;
                    }
                }
                //等待时间单价
                else if (JGWei == 2)
                {
                    DJ_min++;
                    if (DJ_min > 999)
                    {
                        DJ_min = 1;
                    }
                }
                //夜间
                else if (JGWei == 3)
                {
                    Night++;
                    if (Night > 999)
                    {
                        Night = 1;
                    }
                }
                //白天
                else if (JGWei == 4)
                {
                    Day++;
                    if (Day > 999)
                    {
                        Day = 1;
                    }
                }
                display_D(Day, Night, DanJia, JGWei, DJ_min);
            }

            while (K3 == 0)
                ;
        }

        //-
        if (K2 == 0)
        {
            delay(100);
            //调时
            if (Mode == 0)
            {
                //年
                if (Wei == 1)
                {
                    time_buf1[1]--;
                    if (time_buf1[1] < 0)
                        time_buf1[1] = 99;
                }
                //月
                else if (Wei == 2)
                {
                    time_buf1[2]--;
                    if (time_buf1[2] <= 0)
                        time_buf1[2] = 12;
                }
                //日
                else if (Wei == 3)
                {
                    time_buf1[3]--;
                    if (time_buf1[3] <= 0)
                        time_buf1[3] = YDay(time_buf1[1], time_buf1[2]);
                }
                //时
                else if (Wei == 4)
                {
                    time_buf1[4]--;
                    if (time_buf1[4] < 0)
                        time_buf1[4] = 23;
                }
                //分
                else if (Wei == 5)
                {
                    time_buf1[5]--;
                    if (time_buf1[5] < 0)
                        time_buf1[5] = 59;
                }
                //秒
                else if (Wei == 6)
                {
                    time_buf1[6]--;
                    if (time_buf1[6] < 0)
                        time_buf1[6] = 59;
                }
                //显示
                if (Wei != 0)
                    display_NYR(time_buf1, Wei, SS);
            }
            //调价
            else if (Mode == 2)
            {
                //单价
                if (JGWei == 1)
                {
                    DanJia--;
                    if (DanJia == 0)
                    {
                        DanJia = 999;
                    }
                }
                //等待时间单价
                else if (JGWei == 2)
                {
                    DJ_min--;
                    if (DJ_min == 0)
                    {
                        DJ_min = 999;
                    }
                }
                //夜间
                else if (JGWei == 3)
                {
                    Night--;
                    if (Night == 0)
                    {
                        Night = 999;
                    }
                }
                //白天
                else if (JGWei == 4)
                {
                    Day--;
                    if (Day == 0)
                    {
                        Day = 999;
                    }
                }
                display_D(Day, Night, DanJia, JGWei, DJ_min);
            }
            while (K2 == 0)
                ;
        }
        //切换
        if (K1 == 0)
        {
            delay(100);
            //计价器模式
            if (Mode == 1)
            {
                Mode = 0;
                ZJ = 0;
                GL = 0;
                Time = 0;
                //开启定时器
                TR0 = 0;
                EX0 = 0;
                //显示计价器
                Init_LCD();
            }
            else if (Mode == 0)
            {
                Mode = 1;
                //参数初始化
                //读初值
                READS();
                ZJ = 0;
                GL = 0;
                Time = 0;
                //开启定时器
                m = 0;
                TR0 = 1;
                EX0 = 1;
                //显示计价器
                Init_LCD_JJQ();
            }
            while (K1 == 0)
                ;
        }
    }
}

//初始化函数
void InitTimer0(void)
{
    TMOD = 0x01;
    TH0 = 0x3C;
    TL0 = 0xB0; // 10ms
    EA = 1;
    ET0 = 1;
    TR0 = 1;
    IT0 = 1; // INT0负跳变触发
    EX0 = 0; //开外部INTO中断
}

//定时器0中断10ms
void Timer0Interrupt(void) interrupt 1
{
    TH0 = 0x3C;
    TL0 = 0xB0; //赋初值
    m++;
    if (m >= 20)
    {
        m = 0;
        if (count >= 60)
        {
            GT = 0;
            GL = GL + count / 10;
            count = 0;
        }
        else
        {
            count = 0;
            GT = 1;
            Time++; //时间++
        }
    }
    //计算钱数
    //公里数小于3
    if (GL <= 300)
    {
        if (DN == 0)
        {
            if (Time > 60)
                ZJ = Day + Time / 60 * DJ_min;
            else
                ZJ = Day;
        }
        else
        {
            if (Time > 60)
                ZJ = Night + Time / 60 * DJ_min;
            else
                ZJ = Night;
        }
    }
    else
    {
        if (DN == 0)
        {
            if (Time > 60)
                ZJ = Day + (GL / 10 - 20) / 10 * DanJia + Time / 60 * DJ_min;
            else
                ZJ = Day + (GL / 10 - 20) / 10 * DanJia;
        }
        else
        {
            if (Time > 60)
                ZJ = Night + (GL / 10 - 20) / 10 * DanJia + Time / 60 * DJ_min;
            else
                ZJ = Night + (GL / 10 - 20) / 10 * DanJia;
        }
    }
}
void EXINT0() interrupt 0
{
    count++;
}

//读初值
void READS()
{
    uchar SH = 0, SL = 0;
    uint temp = 0;

    delay(10);
    SL = read_add(0x01);
    delay(10);
    SH = read_add(0x02);
    temp = SH;
    temp = temp << 8;
    temp = temp + SL;
    Day = temp;

    delay(10);
    SL = read_add(0x03);
    delay(10);
    SH = read_add(0x04);
    temp = SH;
    temp = temp << 8;
    temp = temp + SL;
    Night = temp;

    delay(10);
    SL = read_add(0x05);
    delay(10);
    SH = read_add(0x06);
    temp = SH;
    temp = temp << 8;
    temp = temp + SL;
    DanJia = temp;

    delay(10);
    SL = read_add(0x07);
    delay(10);
    SH = read_add(0x08);
    temp = SH;
    temp = temp << 8;
    temp = temp + SL;
    DJ_min = temp;
}

//写初值
void SETS()
{
    uchar SH = 0, SL = 0;
    uint temp = 0;

    temp = Day;
    SL = temp & 0x00ff;
    SH = temp >> 8;
    delay(10);
    write_add(0x01, SL);
    delay(10);
    write_add(0x02, SH);

    temp = Night;
    SL = temp & 0x00ff;
    SH = temp >> 8;
    delay(10);
    write_add(0x03, SL);
    delay(10);
    write_add(0x04, SH);

    temp = DanJia;
    SL = temp & 0x00ff;
    SH = temp >> 8;
    delay(10);
    write_add(0x05, SL);
    delay(10);
    write_add(0x06, SH);

    temp = DJ_min;
    SL = temp & 0x00ff;
    SH = temp >> 8;
    delay(10);
    write_add(0x07, SL);
    delay(10);
    write_add(0x08, SH);
}
