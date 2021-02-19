/*
  ����:   ʵ��k2 interrupt ����ַ���ʾ

  1. ����·ͼ�ҵ�CPU��Ӧ�Ŀ��ƹܽ�   GPX1_1 
  2. ��оƬ�ֲᣬ�ҵ���Ӧ�Ĵ���
     a. ���ùܽ�Ϊinterruptģʽ
     b. ���ܿ�����
  3. ���   

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
