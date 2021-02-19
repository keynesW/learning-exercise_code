/*******************************************************************
 *
 *     File Name    :      multiset.cpp
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Mon 16 Nov 2020 01:39:26 PM CST
 *     Description  :      Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include <iostream>
#include <set>
using namespace std;
 

template <typename T1>
void print( T1 start,T1 end)
{
    for ( T1 iter = start; iter != end; iter ++)
        cout << *iter << "  ";
    cout << endl;
}
 
template<> 
void print<multiset<int>::iterator>(multiset<int>::iterator start,\
                                         multiset<int>::iterator end)
{
    using tpname = multiset<int>::iterator;
    for ( tpname iter = start; iter != end; iter ++)
        cout << *iter << "  ";
    cout << endl;
}

template 
void print<multiset<int>::iterator>(multiset<int>::iterator start,\
                                    multiset<int>::iterator end);

int main( int argc,const char * argv[] )
{
    multiset<int> imultiset;
    multiset<int> imultiset1({1,4,3,2,5});
    imultiset = imultiset1; 
    print(imultiset.begin(),imultiset.end());
    
    imultiset.insert(imultiset.begin(),6);
    print(imultiset.begin(),imultiset.end());

    imultiset.erase(5);
    print(imultiset.begin(),imultiset.end());

    cout << "==================" << endl;
    imultiset.insert(imultiset.begin(),6);
    print(imultiset.begin(),imultiset.end());

    cout << *imultiset.find(6) << endl;
    print(imultiset.find(6),imultiset.find(6));

    return 0;
}
