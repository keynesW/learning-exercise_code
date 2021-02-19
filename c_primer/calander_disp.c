#include"stdio.h" 

#define DAYS  261
#define BASEDAYS 263
char * dayofwek[7] = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};


}

int inputget(int *year,int *month,int *day)
{
    scanf("%d %d %d",year,month,day);

}


//*****************************************************************************//
//                          to get the wek of the date                         //
//                       Based on date of 2020-09-20  Sunday                   //
//*****************************************************************************//
/*
int daysofmonths(int month)
{
    int days = 0 ;
    switch (month-1)
    {
        case 1: days = 31; 
               break; 
        case 2: days = 59; 
               break; 
        case 3: days = 90; 
               break; 
        case 4: days = 120;
               break; 
        case 5: days = 151; 
               break; 
        case 6: days = 181; 
               break; 
        case 7: days = 212; 
               break; 
        case 8: days = 243; 
               break; 
        case 9: days = 273; 
               break; 
        case 10: days = 304; 
               break; 
        case 11: days = 334; 
               break;     
        default : days = 0; 
    }
    return days;
}
int num_days2Base_day(int year,int month,int day)
{
    int num_Y_days =0,num_M_days = 0, num_D_days = 0 , Tot_days = 0 ;
    if(year > 2020)
        num_Y_days = 365*(year -2020-1) + (year -2020)/4;
    else if(year<2020) 
                num_Y_days = 365*(2020-1-year) + (2020 - year)/4;
    else
        num_Y_days = 0;
                            ;

    num_M_days = daysofmonths(month);

    num_D_days = day;

    Tot_days =  num_Y_days + num_M_days + num_D_days;
    return Tot_days;
}

int date2wek(int year,int month ,int day)
{
    int i_wek = 5,totaldays = 0;
    totaldays = num_days2Base_day(year,month,day);
//       totaldays > BASEDAYS ? (totaldays-=BASEDAYS):(totaldays=(-(BASEDAYS-totaldays));
        totaldays -= BASEDAYS ;
*/
        //*****************************************************//
//              printf("totadays = %d\n",totaldays);
        //*****************************************************//
/*
        i_wek = totaldays % 7 ;
        return i_wek;
}
*/

//***************************************************************************//
int isleap(int  year)
{
        if((year %4 == 0)&&(year%100 != 0)||(year%400)==0)
        {
            return 1;  
        } else
                 {   
                         return 0;
                 }
}


int monthdays(int year,int month)
{
        int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
        if (isleap(year) == 1)
        {
                days[1] = 29;
        }
        return days[month - 1];   
}

int totaldays(int year, int month, int day)
{
    int sum = 0 ;
    int i = 1;
    for(i = 1; i< month; i++)
    {
        sum += monthdays(year,i);
    }
    sum += day;
    return sum;

}
int date2wek(int year,int  month,int day)
{
    int i_wek = 0;
    i_wek = (year -1)+(year-1)/4 - (year-1)/100 + (year-1)/400 +totaldays(year,month,day);
    i_wek %= 7;
    return i_wek;


}



int wek_display(int year, int month , int day)
{
    int i_wek = 5;
    i_wek = date2wek(year, month, day);
    printf("%d %d %d is %s\n\n",year,month,day,dayofwek[i_wek]);
    return i_wek;
}
//***************************************************************************//


int getw_curr_month()
{

    return 4;
}



//**************************************************************************//
//                                                                          //
//                          calander display                                //
//                                                                          //
//**************************************************************************//
int calander_disp(int year,int month,int days)
{
        int iter_i = 0 ,maxday = 0;
        printf("\tSun\tMon\tTu\tWen\tThr\tFri\tSat\n");
        iter_i = date2wek(year,month,1);
        maxday = monthdays(year,month);
        int i= 0 , j = 0;
        for( i= 0 ;i<iter_i;++i)
        {
                printf("\t");
        }
        for(int j = 1;j< maxday ;++j){
                printf("\t%d",j);
                if(i%7==6)
                   printf("\n"); 
                i++;
        }
        printf("\n\n");
}



int main()
{
    int Year = 2020,Month = 9,Day = 18;
    tips_disp();
    inputget(&Year,&Month ,&Day);
    wek_display(Year,Month,Day);
    calander_disp(Year,Month,Day);



    return 0;

}
