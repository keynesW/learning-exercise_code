/*
  功能:   实现k2 interrupt 输出字符显示

  1. 看电路图找到CPU对应的控制管脚   GPX1_1 
  2. 看芯片手册，找到对应寄存器
     a. 配置管脚为interrupt模式
     b. 功能块设置
  3. 编程   

*/
/*
@UART2  com2 con7       @UART3 com3 con6        @UART0 com0 con8
@GPA1_0  RX             @GPA1_4  RX             @GPA0_0  RX
@GPA1_1  TX             @GPA1_5  TX             @GPA0_1  TX

GPA1  con   1140 0020
      dat   1140 0024
*/

#define GPA1_DAT  (*(volatile unsigned int *)(0x11400024))

#define GPA1_CON  (*(volatile unsigned int *)(0x11400020)) 
#define ULCON2    (*(volatile unsigned int *)(0x13820000))
#define UCON2     (*(volatile unsigned int *)(0x13820004))
#define UBRDIV2   (*(volatile unsigned int *)(0x13820028))
#define UFRACVAL2 (*(volatile unsigned int *)(0x1382002c))
#define UTRSTAT2  (*(volatile unsigned int *)(0x13820010))
#define UTXH2     (*(volatile unsigned int *)(0x13820020))


#define GPA1_CON  (*(volatile unsigned int *)(0x11400000)) 
#define ULCON3    (*(volatile unsigned int *)(0x13800000))
#define UCON3     (*(volatile unsigned int *)(0x13800004))
#define UBRDIV3   (*(volatile unsigned int *)(0x13800028))
#define UFRACVAL3 (*(volatile unsigned int *)(0x1380002c))
#define UTRSTAT3  (*(volatile unsigned int *)(0x13800010))
#define UTXH3     (*(volatile unsigned int *)(0x13800020))

void USART2_INIT()
{
    GPA1_CON = (GPA1_CON & ~(0xff<<0)) | (0x22<<0);
    ULCON2   = 0x3;
    UCON2    = 0x5;

    UBRDIV2  = 53;
    UFRACVAL2= 4;
}

void USART3_INIT()
{
    GPA1_CON = (GPA1_CON & ~(0xff<<16)) | (0x22<<16);
    ULCON3   = 0x3;
    UCON3    = 0x5;

    UBRDIV3  = 53;
    UFRACVAL3= 4;
}

void put_char(char ch)
{
    while(!(UTRSTAT3&0x2))
        ;
    UTXH3 = ch;
}

void putc(char ch)
{
    while(!(UTRSTAT2&0x2))
        ;
    UTXH2 = ch;
}

void delays()
{
    volatile int i,j;
    for ( i= 0; i < 1000 ; i++ )
        for ( j= 0; j < 1000 ; j++ )
            ;
}

int main(void) 
{
    USART2_INIT();
    USART3_INIT();

    while(1)
    {
        put_char('b');
        putc('d');
        delays();
    }
}
