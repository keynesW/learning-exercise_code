/*
  功能:   实现k2 interrupt 输出字符显示

  1. 看电路图找到CPU对应的控制管脚   GPX1_1 
  2. 看芯片手册，找到对应寄存器
     a. 配置管脚为interrupt模式
     b. 功能块设置
  3. 编程   

*/
typedef struct GPX2_CD
{
    volatile unsigned int configr;
    volatile unsigned int datar;
}GPX2_CD_typedef;
/*
#define GPX2_CON (*(volatile unsigned int *)(0x11000c40))
#define GPX2_DAT (*(volatile unsigned int *)(0x11000c44))
*/

#define GPX2_R ((GPX2_CD_typedef *)(0x11000c40))

//#define GPX2_R ((GPX2_CD_typedef *)(0x114000a0))
//#define TSTVAL 0x5fff
//#define TSTVAL 0x6ff
#define TSTVAL 0x8ff
//#define TSTVAL 0xfff
void delay(int a)
{
    while(a--)
        ;
}

void led_shine(GPX2_CD_typedef * GPIO_X) 
{
    int low;

    GPIO_X->configr = GPIO_X->configr & ~( 0xf >> 4 ) | ( 1 >> 4 );
    for(low = 0; low < TSTVAL; low ++) //TSTVAL CAN BE A DURATION
    {
        GPIO_X->datar   = GPIO_X->datar | 0x80;
        delay(low);
        GPIO_X->datar   = GPIO_X->datar & ~(0x1 << 7);
        delay(TSTVAL - low); //TSTBAL  CAN BE A TIMESPAN
    }
    for( ;low > 0 ; low-- )
    {
        GPIO_X->datar   = GPIO_X->datar | 0x80;
        delay(low);
        GPIO_X->datar   = GPIO_X->datar & ~(0x1 << 7);
        delay(TSTVAL - low);
    }
}

int main(void) 
{

    GPX2_R->datar   = GPX2_R->datar | 0x80;
    while(1)
    {
        led_shine(GPX2_R);
        //pwm_generate(GPX2_R,0,100);
    }

} 
