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

class Gun :public Toy{ 
public:
    void play()
    {
        cout << "biu biu ..." << endl;
    }

};
class Factory{
public:
    //virtual   Toy* create_Toy() = 0;
    virtual   Toy* create_Toy() { Toy * toy;return toy;};
};

//{{{
//    Car * create_Car()
//    {
//        return new Car;
//    }
//    Doll * create_Doll()
//    {
//        return new Doll;
//    }
//}}}//

template<typename T>
class specilize_Factory: public Factory{
    public:
        //virtual
        Toy * caeate_Toy()
        {
            return new T;
        }
};

/*{{{
class CarFactory :public Factory{
public:
    Toy* create_Toy()
    {
        return new Car;
    }
};

class DollFactory : public Factory{
public:
    Toy* create_Toy()
    {
        return new Doll;
    }
};

class GunFactory : public Factory{
public:
    Toy* create_Toy()
    {
        return new Gun;
    }
};
*//*}}}*/

int main( int argc,const char * argv[] )
{

    int n;
    cout << "please enter a num to select:" << endl;
    cin >> n;

    Factory * pfactory = nullptr;
    Toy * ptoy = nullptr;

    cout << "----------------" << endl;

    switch(n)
    {
    case 1: 
        //pfactory = new CarFactory;
        pfactory = new specilize_Factory<Car>;
        break;
    case 2: 
        //pfactory = new DollFactory;
        pfactory = new specilize_Factory<Doll>;
        break;
    case 3: 
        //pfactory = new GunFactory;
        pfactory = new specilize_Factory<Gun>;
        break;
    }

    ptoy = pfactory->create_Toy();
    ptoy->play();

    return 0;
}
