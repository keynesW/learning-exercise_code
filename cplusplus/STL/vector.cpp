/*******************************************************************
 *
 *     File Name    :      vector.cpp
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Mon 16 Nov 2020 09:20:12 AM CST
 *     Description  :      Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include <iostream>
#include <vector>
using namespace std;

template <typename T1>
void print( T1 start,T1 end)
{
    for ( T1 iter = start; iter != end; iter ++)
        cout << *iter << "  ";
    cout << endl;
}
 
int main( int argc,const char * argv[] )
{
    vector <int> vint;
    vector <int> vint1({1,2,3,4,5});

    int a[] = {1,3,4,5,6};
    vint = vint1;

    cout << vint.size() << endl;
/*
    for( int x : a)
        cout << x << endl;
    //cout << ( vint.begin() ) << endl;
*/
    cout << "size  :  " << vint.size() << endl; 
    cout << "max size  :  " << vint.max_size() << endl;

    cout << (vint < vint1) <<endl;

    vector<int>::iterator iter_int = vint.begin();
    cout << *iter_int << endl; 
    cout << *++iter_int << endl; 

    print(vint.begin(),vint.end());

    vint.insert(vint.begin(),9);
    print(vint.begin(),vint.end());

   // vint.clear();
    cout << vint.size() << endl;

    vint.push_back(6);
    print(vint.begin(),vint.end());
    
    vint.pop_back();
    print(vint.begin(),vint.end());

    vint.resize(vint.size()+3,9);
    print(vint.begin(),vint.end());
    vint.resize(vint.size()-3);
    print(vint.begin(),vint.end());

    cout << vint.front() << endl;

    cout << "==================" << endl;
    cout << vint[0] << endl;

    try{

        vint.at(vint.size()+2);
    }
    catch(out_of_range e)
    {
        cout << e.what() << endl;

    }
    cout << vint.capacity() << endl;

    cout << vint.capacity() << endl;
    vint.reserve(18);
    cout << vint.size() << endl;
    cout << vint.capacity() << endl;


    return 0;
}
