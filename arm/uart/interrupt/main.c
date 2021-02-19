/*
  功能:   实现k2 interrupt 输出字符显示

  1. 看电路图找到CPU对应的控制管脚   GPX1_1 
  2. 看芯片手册，找到对应寄存器
     a. 配置管脚为interrupt模式
     b. 功能块设置
  3. 编程   

*/


#define GPX1CON         (*(volatile unsigned int *)0x11000C20) 
#define EXT_INT41CON    (*(volatile unsigned int *)0x11000E04) 
#define EXT_INT41_MASK  (*(volatile unsigned int *)0x11000F04) 

#define ICDDCR          (*(volatile unsigned int *)0x10490000)
#define ICCICR_CPU0     (*(volatile unsigned int *)0x10480000)
#define ICCPMR_CPU0     (*(volatile unsigned int *)0x10480004)

#define ICDISER1_CPU0   (*(volatile unsigned int *)0x10490104) 

#define ICDIPTR14_CPU0  (*(volatile unsigned int *)0x10490838)
#define ICCIAR_CPU0     (*(volatile unsigned int *)0x1048000C)
#define EXT_INT41_PEND  (*(volatile unsigned int *)0x11000f44)
#define ICDICPR1_CPU0   (*(volatile unsigned int *)0x10490284)
#define ICCEOIR_CPU0    (*(volatile unsigned int *)0x10480010)

/*
 * GPX3_2  K4  0x11000c60   0xf<<8
 * //XEINT_26 0x11000714  2<<8
 * XET_INT43CON  0X11000e0c  2<<8
 * EXT_INT43_MASK 0x11000fc0  & ~(1<<2)
 * ICDISER2_CPU0  0x10490108  1 
 * ICDIPTR16_CPU0  0x10490840 1
 * ICDICPR2_CPU0  0x10490288  1 
 * EXT_INT43_PEND 0X11000F4C  1 << 2
 */
#define GPX3_CON     (*(volatile unsigned int *)0x11000c60)
#define XET_INT43CON (*(volatile unsigned int *)0x11000e0c)

#define GPA1CON     (*(volatile unsigned int *)0x11400020) 
#define ULCON2      (*(volatile unsigned int *)0x13820000) 
#define UCON2       (*(volatile unsigned int *)0x13820004) 
#define UBRDIV2     (*(volatile unsigned int *)0x13820028) 
#define UFRACVAL2   (*(volatile unsigned int *)0x1382002c) 
#define UTXH2       (*(volatile unsigned int *)0x13820020) 
#define UTRSTAT2    (*(volatile unsigned int *)0x13820010) 

void uart_init(void)
{
  //1. config pin  GPA1_1 GPA1_0  uart mode
  GPA1CON = 0x22;

  //2. set uart function block
  ULCON2  =  0x03;              // data bit =8  parity=none  stop bit=1
  UCON2 = 0x05;                 // set polling mode

  /*
   * set Baud-Rate = 115200
   * DIV_VAL = (100000000/(115200 *16)) - 1 = 53.253  UBRDIV2  =50
   * UFRACVAL2 = 0x253*16=4
   * 
   */

   UBRDIV2 = 53;  
   UFRACVAL2  = 4;

}

void putc(char c)
{
  while(1)
  {
	if( UTRSTAT2&0x02 )
		break;
  }

   UTXH2 = c; 

}
	
void interrupt_init()
{
  GPX1CON=(GPX1CON&~(0xff<<4))|(0xff<<4); //set gpx1_1 interrupt mode   
  EXT_INT41CON =(EXT_INT41CON&~(0x77<<4))|(0x22<<4);//  set GPX1_1 falling edge triger  

  EXT_INT41_MASK = (EXT_INT41_MASK &~(0x3<<1)); //set pin interrupt enable 
  
  ICDISER1_CPU0 = ICDISER1_CPU0 | (0x3<<25);	//EINT9 (GPX1_1)  GIC中断使能
  ICDIPTR14_CPU0 = 0x01010101; 

  ICDDCR = ICDDCR|1; //GIC 分发总使能
  ICCICR_CPU0 = 1;  // CPU0  中断使能
  ICCPMR_CPU0 = 0XFF;   //设置CPU0的优先级门槛为最低
}

void do_irq(void )
{
	  int irq_num;

	  irq_num = ICCIAR_CPU0&0x000003ff; ////中断ID号
	  switch(irq_num)
	  {
      case 57:
	      putc('2');
		  EXT_INT41_PEND = EXT_INT41_PEND|(1<<1);  //清GPX1_1中断标志
		  ICDICPR1_CPU0 = ICDICPR1_CPU0|(1<<25);    //清GIC GPX1_1中断标志
		  break;
      case 58:
	      putc('3');
		  EXT_INT41_PEND = EXT_INT41_PEND|(1<<2);  //清GPX1_1中断标志
		  ICDICPR1_CPU0 = ICDICPR1_CPU0|(1<<26);    //清GIC GPX1_1中断标志
		  break;
      default:
		  putc('e');
		  break;
	  }
	  ICCEOIR_CPU0 = (ICCEOIR_CPU0 & (~0x3FF)) | irq_num;    //结束中断	将处理完成的中断ID号写入该寄存器，则表示相应的中断处理完成
}

int main(void) 
{
	uart_init();
	interrupt_init();
	while(1)
	{
	  putc('a');
	  delay1s();
	}
	return 0;
}
