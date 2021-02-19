/*******************************************************************
 *
 *     File Name    :      toyfactory.cpp
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Wed 18 Nov 2020 08:47:42 AM CST
 *     Description  :      Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include <iostream>
using namespace std;

class Toy{
public:
    virtual void play() = 0 ;
};

class Car :public Toy{
public:
    void play()
    {
        cout << "sou sou ..." << endl;
    }

};

class Doll :public Toy{ 
public:
    void play()
    {
        cout << "comb hair ..." << endl;
    }

};

class Factory{
public:
    Car * create_Car()
    {
        return new Car;
    }
    Doll * create_Doll()
    {
        return new Doll;
    }

};

int main( int argc,const char * argv[] )
{

    int n;
    cout << "please enter a num to select:" << endl;
    cin >> n;
/*   
*/    
    Car * pcar = nullptr;
    Doll *pdoll = nullptr;
    pcar->play();

    Factory * pfactory = new Factory;
    Toy * ptoy = nullptr;

    cout << "----------------" << endl;

    switch(n)
    {
    case 1: 
        ptoy = pfactory->create_Car();
        //pcar = pfactory->create_Car();
        pcar->play();
        break;
    case 2: 
        ptoy = pfactory->create_Doll();
        //pdoll = pfactory->create_Doll();
        //pcar->play();
        pdoll->play();
        break;
    }

    ptoy->play();

    return 0;
}
