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
#include <string>

using namespace std;

int main()
{
    string str;
    string strw = "word";
    str = "hello word ";
    cout << str << endl;
    cout << "----------------" << endl;
    str.size();
    str.clear();
    cout << str.size() << endl;
    cout << "----------------" << endl;
    bool rsltstrcpy = str > strw;
    cout << rsltstrcpy << endl;
    cout << (str + strw) << endl;
    cout << str << endl;
    cout << (str += strw) << endl;
    cout << str << endl;

    cout << str[2] << endl;
    return 0;
}
