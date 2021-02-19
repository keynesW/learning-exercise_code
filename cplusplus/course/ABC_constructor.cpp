/*******************************************************************
 *
 *      File Name    :      tst.cpp 
 *      Author       :      Keynes 
 *      QQ           :      1446160257       
 *      Email        :      1446160257@qq.com      
 *      Blog£º :      http://www.    .com/      
 *      Created Time :      Fri 20 Nov 2020 07:32:42 PM CST      
 *      Description  :      Hello Word in C++ , GUN-style 
 *
 *******************************************************************/ 

#include <iostream> 
using namespace std; 

class ABC
{
protected:
    int a ;
public:
    ABC();
    ~ABC();
    virtual void tst() = 0;
};
ABC::ABC()
{
    a = 5;
    cout << "ABC construct" << endl;
}
ABC::~ABC()
{
    cout << "ABC deconstruct" << endl;
}

class Tst : public ABC{
public:
    Tst();
    ~Tst();
    void tst();

};
Tst::Tst()
{
    cout << "Tst construct" << endl;
}
Tst::~Tst()
{
    cout << "Tst deconstruct" << endl;
}
void Tst::tst()
{
    cout <<  a <<endl;
}

 
int main( int argc,const char * argv[] )
{

    {
        Tst tst;
        tst.tst();
    }

    return 0;

}
