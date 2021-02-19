/*******************************************************************
 *
 *     File Name    :      tst.cpp
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Mon 09 Nov 2020 06:55:31 PM CST
 *
 ******************************************************************/

#include <iostream>
using namespace std;

int func(int n);
int max_same_char(char *s);
double an(double n);

int main(int argc ,const char * argv[])
{
    char str[]="abcdddddddaaaaaabb\0";
    //func(6);
    //max_same_char(str);
    
    an(11);
    return 0;
}

int func(int n)
{
    if ( n <=2 )
        return 1;
    int first = 1,second =1,third;

    for(int i =1; i < n; i++)
    {
        third = second + first;
        first = second;
        second = third;
    }
    cout << second << endl;
    return second;
}

int max_same_char(char *s)
{
    char * iter = s;
    int cunt=1 ,max = 0;
    for( ;iter && iter[1]; iter ++)
    {
        if( iter[1]  == *iter )
            cunt++;
        else
            cunt = 1;
        max = cunt > max ? cunt: max;
    }
    cout << max << endl;
    return max;
}

double an(double n)
{
    double sum = 2/((n)*(n+1));
    if(n > 1)
        sum +=  an(n-1);
    cout << sum << endl;
    return sum;
}
