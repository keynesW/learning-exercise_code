/*******************************************************************
 *
 *     File Name    :      map.cpp
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
    map<string,int> imap;
    map<string,int> imap1({ {"jerry",1},{"joker",4},{"loser",3} });
    imap = imap1; 
    print(imap.begin(),imap.end());
    
    imap.insert(imap.begin(),{"tom",6});
    print(imap.begin(),imap.end());

    imap.erase("joker");
    print(imap.begin(),imap.end());

    cout << "==================" << endl;
    imap.insert(imap.begin(),{"tom",6});//不支持重复元素 
    print(imap.begin(),imap.end());

    cout << "==================" << endl;
    cout << imap.at("jerry") << endl ;

    return 0;
}
