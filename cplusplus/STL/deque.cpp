/*******************************************************************
 *
 *     File Name    :      deque.cpp
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Mon 16 Nov 2020 09:20:12 AM CST
 *     Description  :      Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include <iostream>
#include <deque>
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
    deque <int> ideque;
    deque <int> ideque1({1,2,3,4,5});

    int a[] = {1,3,4,5,6};
    ideque = ideque1;

    cout << ideque.size() << endl;
/*
    for( int x : a)
        cout << x << endl;
    //cout << ( ideque.begin() ) << endl;
*/
    cout << "size  :  " << ideque.size() << endl; 
    cout << "max size  :  " << ideque.max_size() << endl;

    cout << (ideque < ideque1) <<endl;

    deque<int>::iterator iter_int = ideque.begin();
    cout << *iter_int << endl; 
    cout << *++iter_int << endl; 

    print(ideque.begin(),ideque.end());

    ideque.insert(ideque.begin(),9);
    print(ideque.begin(),ideque.end());

   // ideque.clear();
    cout << ideque.size() << endl;

    ideque.push_back(6);
    print(ideque.begin(),ideque.end());
    
    ideque.pop_back();
    print(ideque.begin(),ideque.end());

    ideque.resize(ideque.size()+3,9);
    print(ideque.begin(),ideque.end());
    ideque.resize(ideque.size()-3);
    print(ideque.begin(),ideque.end());

    cout << ideque.front() << endl;

    cout << "==================" << endl;
    cout << ideque[0] << endl;
    try{

        ideque.at(ideque.size()+2);
    }
    catch(out_of_range e)
    {
        cout << e.what() << endl;

    }
/*
    cout << ideque.capacity() << endl;

    cout << ideque.capacity() << endl;
    ideque.reserve(18);
    cout << ideque.size() << endl;
    cout << ideque.capacity() << endl;
*/
    ideque.push_front(4);
    print(ideque.begin(),ideque.end());
    
    ideque.pop_front();
    print(ideque.begin(),ideque.end());


    return 0;
}
