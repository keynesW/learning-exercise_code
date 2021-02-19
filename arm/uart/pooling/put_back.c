/*
  ����:   ʵ��ͨ������com2 ����ַ���ʾ

  1. ����·ͼ�ҵ�CPU��Ӧ�Ŀ��ƹܽ�   GPA1_1  GPA1_0
  2. ��оƬ�ֲᣬ�ҵ���Ӧ�Ĵ���
     a. ���ùܽ�Ϊ����ģʽ
     b. ���ܿ�����
  3. ���   
     

*/

#define  GPA1CON    (*(volatile unsigned int *)0x11400020)
#define  ULCON2     (*(volatile unsigned int *)0x13820000) 
#define  UCON2      (*(volatile unsigned int *)0x13820004) 
#define  UBRDIV2    (*(volatile unsigned int *)0x13820028) 
#define  UFRACVAL2  (*(volatile unsigned int *)0x1382002C) 
#define  UTXH2      (*(volatile unsigned int *)0x13820020) 
#define  UTRSTAT2   (*(volatile unsigned int *)0x13820010) 
#define  URXH2      (*(volatile unsigned int *)0x13820024) 
void uart_init(void)
{
  //-----��: ���ùܽŵĹ���ģʽ
  GPA1CON = 0x22;  //����GPA1_1 GPA10 Ϊuart����ģʽ
  //GPA1CON = (GPA1CON & ~0xff) | 0x22;
  //-----��: ���ܿ�����
  //1.  uart ͨѶЭ���ʽ������
  ULCON2 = 0x03;  //����Э���ʽ(  ��У��λ  1��ֹͣλ 8������λ)
  UCON2 = 0x05;   //���ô��ڷ��ͽ���ģʽΪpollingģʽ
  
  /*2.  ����uart ���ٶ�Ϊ115200
  DIV_VAL = (100000000/(115200 *16)) - 1 = 53.253
  UBRDIVn =  53
  UFRACVALn/16 = 0.253
  Therefore, UFRACVALn = 4
  */
  UBRDIV2 = 53;
  UFRACVAL2 = 4;
    
}


void putc(char c)
{
   while(!(UTRSTAT2&0x02));
   
   UTXH2 = c;  //�����ַ�
}

char getc()
{
   char c;
   c = (char)URXH2;
   return c;
}
int main(void) 
{
	char c;
    uart_init();
	#if 0
	while(1)
	{
      putc('f');
	  delay1s();
	}
	#else
	while(1)
    {
        while(UTRSTAT2&0x01)	
        {
            c =  getc();
            if (c == 0x0d)
            {
                UTXH2 = 0x0a;
                delay1s(1);
                UTXH2 = 0x0d;
            }
            else
            {
               putc(c);
            }
            delay1s(1);
        } 

    }
	#endif 
	return 0;
}
