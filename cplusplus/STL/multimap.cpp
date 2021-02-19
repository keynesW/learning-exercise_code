/*******************************************************************
 *
 *     File Name    :      multimap.cpp
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog： :      http://www.    .com/ 
 *     Created Time :      Mon 16 Nov 2020 01:39:26 PM CST
 *     Description  :      Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include <iostream>
#include <map>
using namespace std;

template <typename K,typename V>
ostream& operator<<(ostream& os,const pair<K,V> pr)
{
    os << '(' << pr.first << " , " << pr.second << ')';
    os << endl; 
    return os;

}

template <typename T1>
void print( T1 start,T1 end)
{
    for ( T1 iter = start; iter != end; iter ++)
        cout << *iter ;
    cout << endl;
}
 
int main( int argc,const char * argv[] )
{
    multimap<string,int> imultimap;
    multimap<string,int> imultimap1({ {"jerry",1},{"joker",4},{"loser",3} });
    imultimap = imultimap1; 
    print(imultimap.begin(),imultimap.end());
    
    imultimap.insert(imultimap.begin(),{"tom",6});
    print(imultimap.begin(),imultimap.end());

    imultimap.erase("joker");
    print(imultimap.begin(),imultimap.end());

    cout << "==================" << endl;
    imultimap.insert(imultimap.begin(),{"tom",6});//不支持重复元素 
    print(imultimap.begin(),imultimap.end());

    cout << "==================" << endl;
//    cout << imultimap.at("jerry") << endl ;

    return 0;
}
