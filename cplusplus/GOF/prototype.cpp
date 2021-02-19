/*******************************************************************
 *
 *     File Name    :      monstor.cpp
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Tue 17 Nov 2020 10:57:43 AM CST
 *     Description  :      Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include <iostream>
using namespace std;

class Monster{
public:
    virtual void change() = 0;
    virtual Monster * clone() = 0;
};

class MasterSun :public Monster{
    void change(){
        cout << "72 changes" << endl;
    }
    Monster *clone()
    {
        return new MasterSun(*this);
    }

};

class MasterZhu :public Monster{
    void change(){
        cout << "36 changes" << endl;
    }
    Monster *clone()
    {
        return new MasterZhu(*this);
    }
};
 
int main( int argc,const char * argv[] )
{
    Monster *pmster;
    Monster *clone;

    cout << "please enter a num to select :" << endl;
    int n;
    cin >> n;
    
    switch(n)
    {
        case 1:
            pmster = new MasterSun;
            break;
        case 2:
            pmster = new MasterZhu;
            break;
    }
    pmster->change();

    clone = pmster->clone();
    clone->change();


    return 0;
}
