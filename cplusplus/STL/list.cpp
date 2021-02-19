/*******************************************************************
 *
 *     File Name    :      list.cpp
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Mon 16 Nov 2020 09:20:12 AM CST
 *     Description  :      Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include <iostream>
#include <list>
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
    list <int> ilist;
    list <int> ilist1({1,2,3,4,5});

    int a[] = {1,3,4,5,6};
    ilist = ilist1;

    cout << ilist.size() << endl;
/*
    for( int x : a)
        cout << x << endl;
    //cout << ( ilist.begin() ) << endl;
*/
    cout << "size  :  " << ilist.size() << endl; 
    cout << "max size  :  " << ilist.max_size() << endl;

    cout << (ilist < ilist1) <<endl;

    list<int>::iterator iter_int = ilist.begin();
    cout << *iter_int << endl; 
    cout << *++iter_int << endl; 

    print(ilist.begin(),ilist.end());

    ilist.insert(ilist.begin(),9);
    print(ilist.begin(),ilist.end());

   // ilist.clear();
    cout << ilist.size() << endl;

    ilist.push_back(6);
    print(ilist.begin(),ilist.end());
    
    ilist.pop_back();
    print(ilist.begin(),ilist.end());

    ilist.resize(ilist.size()+3,9);
    print(ilist.begin(),ilist.end());
    ilist.resize(ilist.size()-3);
    print(ilist.begin(),ilist.end());

    cout << ilist.front() << endl;

    cout << "==================" << endl;
/*
//    cout << ilist[0] << endl;
    try{

        ilist.at(ilist.size()+2);
    }
    catch(out_of_range e)
    {
        cout << e.what() << endl;

    }
    cout << ilist.capacity() << endl;

    cout << ilist.capacity() << endl;
    ilist.reserve(18);
    cout << ilist.size() << endl;
    cout << ilist.capacity() << endl;
*/
    ilist.push_front(4);
    print(ilist.begin(),ilist.end());
    
    ilist.pop_front();
    print(ilist.begin(),ilist.end());

    ilist.resize(20,2);
    print(ilist.begin(),ilist.end());
    cout << "==================" << endl;

    ilist.unique();
    cout << ilist.size() << endl;
    print(ilist.begin(),ilist.end());

    cout << "==================" << endl;
    ilist.remove(2);
    print(ilist.begin(),ilist.end());


    return 0;
}
