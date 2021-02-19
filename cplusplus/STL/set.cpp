/*******************************************************************
 *
 *     File Name    :      set.cpp
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
 
int main( int argc,const char * argv[] )
{
    set<int> iset;
    set<int> iset1({1,4,3,2,5});
    iset = iset1; 
    print(iset.begin(),iset.end());

    set<int> *ptrset = new set<int>({1,2,3,5,4});
    //set<int> *ptrset1 = new set<int>[5]({1,3});
    
    iset.insert(iset.begin(),6);
    print(iset.begin(),iset.end());

    iset.erase(5);
    print(iset.begin(),iset.end());

    cout << "==================" << endl;
    iset.insert(iset.begin(),6);
    print(iset.begin(),iset.end());

    cout << *iset.find(6) << endl;
    print(iset.find(6),iset.find(6));

    return 0;
}
