/*******************************************************************
 *
 *     File Name    :      proxy.cpp
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Wed 18 Nov 2020 11:20:49 AM CST
 *     Description  :      Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include <iostream>
using namespace std;

class SellPhone{
public:
    virtual void sellPhone() =0 ;

};
class AppleCompany:public SellPhone{
public:
    void sellPhone()
    {
        cout << "apple company ..." << endl;
    }

};
 
class Proxy:public SellPhone{
private:
    //AppleCompany * appcom;
    SellPhone * pselph;
public:
    Proxy()
    {
        //appcom = new AppleCompany;
        pselph = new AppleCompany;
    }
    void sellPhone()
    {
        //appcom->SellPhone(); 
        pselph->sellPhone();
    }
    ~Proxy()
    {
       //delete appcom ;
       delete pselph ;
    }
};


int main( int argc,const char * argv[] )
{

    AppleCompany * appcom = new AppleCompany;
    Proxy * apppro = new Proxy;
    
    appcom->sellPhone();
    apppro->sellPhone();

    return 0;
}
