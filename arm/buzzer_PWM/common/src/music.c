int tone[][2]= {
	  0xff,0xff,//ռλ

	    /*��1-7*/
		629,314,//Do 1
		561,281,//Re 2
		500,250,//Mi 3
		473,236,//Fa 4
		421,210,//SO 5
		375,188,//La 6
		334,167,//Si 7

		/*��1-7*/
		315,158,//Do 8 1
		281,141,//Re 9 2
		250,125,//Mi a 3
		236,118,//Fa b 4
		210,105,//So c 5
		187, 94,//La d 6
		167, 84,//Si e 7
};

unsigned char zbjbxf[]={
		0x64,0xA3,0xC1,0xA2,0x62,0x84,0x61,0x81,0x61,
		0xA4,0xA1,0x91,0xA1,0x81,0x64,0xA3,0xC1,0xD2,
		0xD2,0xD2,0xA2,0xC4,0xA1,0xC1,0xA1,0xC1,0xD2,
		0xD2,0xD2,0xA2,0xC4,0xC2,0x62,0xC2,0x62,0xA2,
		0xA2,0x84,0x94,0x94,0x92,0x81,0x91,0xA2,0xC2,
		0xD4,0xE4,0xA4,0xE4,0xA2,0xE2,0xA2,0xE2,0xA2,
		0xA2,0x84,0x94,0x94,0x92,0x81,0x91,0xA2,0xC2,
		0xD8
};

void mdelay(int time)
{
	int i;
		
	for(i = 0;i < 500 * time;i ++)
		;
					
	return;	
}

int play_tone(unsigned char index,unsigned char beat)
{
	//beep_init(tone[index][0],tone[index][1]<<1);//set voice frequence CNT  CMP Register
	//beep_init(tone[index][0],tone[index][1]>>5);//voice down
	//beep_init(tone[index][0],(tone[index][1]<<6&0x7f)|0x7f);//voice up
	beep_init(tone[index][0],tone[index][0]-1);
	//beep_init(tone[index][0],tone[index][0]>>1);//high
	//beep_init(tone[index][0],tone[index][0]>>6);
	//beep_init(tone[index][0],0);//low
	beep_start();

	mdelay(beat * 500);
	beep_stop();
	mdelay(10);

	return  0;
}


int play_music()
{
	int i = 0;
	unsigned char index,beat;
	unsigned char *p = zbjbxf;

	for(i = 0;i < sizeof(zbjbxf)/sizeof(char);i ++)
	{
		index = p[i] >> 4;//�����������е��±�
		beat  = p[i] & 0xf;//���ʱ��
		play_tone(index,beat);//��������
	}

	return 0;
}
