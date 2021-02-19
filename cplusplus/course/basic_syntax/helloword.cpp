/*******************************************************************
 *
 *     File Name    :      hollowrod.cpp
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Mon 09 Nov 2020 09:12:52 AM CST
 *
 ******************************************************************/
#include <cstdio>
#include <iostream>

using namespace std;

int main()
{
    char name[10];
    int age;
    string str;
    str = "hello word str";
    cout << str << endl;

    cout << "hello word" << endl;

    //printf("please enter your name\n");
    cout << "please enter your name" << endl;
    //scanf("%s",name);
    cin >> name;
    //printf("your name : %s\n",name);
    cout << "your name is :" << name << endl;

    printf("please enter your age\n");
    scanf("%d",&age);

    cout << "your name is :" << name << '\n' << "your age is :" << age << endl;

    return 0;
}
