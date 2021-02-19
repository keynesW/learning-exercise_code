/*******************************************************************
 *
 *     File Name    :      main.cpp
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Fri 13 Nov 2020 09:05:23 AM CST
 *     Description  :       Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include <iostream>
#include <utility>

using namespace std;

template<typename K,typename V>
ostream& operator<<(ostream & os,const pair< K ,V >& ref_obj)
{

    os << '(' << ref_obj.first << "," << ref_obj.second << ')';
    return os;

}

int main( int argc,const char * argv[] )
{
    pair<int ,int > point(1,4);
    cout << point.first << endl;
    cout << point.second << endl;

    pair<int ,int > point1(1,3);
    cout << (point < point1) <<endl;
    cout << point << endl;

    pair<int ,string> st(3,"name");
    cout << st << endl;

    return 0;
}

