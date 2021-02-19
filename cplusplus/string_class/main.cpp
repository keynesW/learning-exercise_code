/*******************************************************************
 *
 *     File Name    :      main.cpp
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Thu 12 Nov 2020 10:42:45 AM CST
 *     Description  :       Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include <iostream>
//#include <string>
#include "mystring.h"
using namespace std;
 
 
int main( int argc,const char * argv[] )
{
    MyString str(5,'c');
    MyString strcp(str);
    MyString strstr("adfdasf");
    MyString strassignment;
    MyString strcin;
//*
    strassignment = str;

    cout << str << endl;
    cout << strcp << endl;
    cout << strassignment << endl;
    
    cout << "---------------" << endl;
    cout << (str + strcp) << endl;
    cout << "---------------" << endl;
    cout << str << endl;
    cout << (str+=strcp) << endl;
    cout << "---------------" << endl;

    cout << (str == strcp) << endl;
    cout << (str == (strcp += str)) << endl;///////////////////////////
    cout << (str != strcp) << endl;
    cout << (str != (strcp += str)) << endl;

    cout << str.size() << endl;
//*/
    cout << "------clear---------" << endl;
    str.clear();
    cout << str << endl;

    cout << (cin >> strcin)  << endl;
    //cout << strcin << endl;

    cout << strstr[1] << endl;

    cout << "---------------" << endl;
    strassignment = strstr;
    cout << strassignment << endl;
    cout << "---------------" << endl;
////////////////////////////////////////////////////
    cout << strstr.size() << endl;
    cout << strcp.size() << endl;
    cout << ((strassignment = (strcp + strstr)).size()) << endl;
    cout << (strassignment = (strcp + strstr)) << endl;
    cout << "---------------" << endl;
    cout << ((strassignment = (str + strstr)).size()) << endl;
    cout << ((strassignment = (str + strstr))) << endl;
    cout << ((strassignment = (str + strstr))[6]) << endl;


    return 0;

}
