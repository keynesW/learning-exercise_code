/*
  功能:   实现k2 interrupt 输出字符显示

  1. 看电路图找到CPU对应的控制管脚   GPX1_1 
  2. 看芯片手册，找到对应寄存器
     a. 配置管脚为interrupt模式
     b. 功能块设置
  3. 编程   

*/


int main(void) 
{
    int *GPX2_CON = (int *) 0x11000c20;
    int *GPX2_DAT = (int *) 0x11000c24;
    *GPX2_CON = *GPX2_CON & ~(0xf<<0) | (0x1<<0);

    while(1)
    {
        *GPX2_DAT |= (1<<0);
        delay();
        *GPX2_DAT &= ~(1<<0);
        delay();
    }

}
