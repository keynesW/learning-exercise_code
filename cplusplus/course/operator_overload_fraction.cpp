/*******************************************************************
 *
 *     File Name    :      main.cpp
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Wed 11 Nov 2020 04:34:47 PM CST
 *     Description  :       Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include <iostream>

using namespace std;

class Fraction{
    private:
        int num;//numerator
        int denom;//denominator
    public:
        Fraction():num(1),denom(2){}
        Fraction(int num, int denom):num(num),denom(denom){}
        Fraction & operator++();
        Fraction  operator++(int);
        Fraction & operator=(const Fraction & ref_fra);
        friend ostream & operator<<( ostream & os,const Fraction & ref_fra );
        friend istream & operator>>( istream & is,Fraction & ref_fra );
        friend Fraction operator+(const Fraction & oper,const Fraction & oper1);
        friend Fraction operator*(const Fraction & oper,const Fraction & oper1);
/*
        void show();
        Fraction operator+(const Fraction & ref_fra );
        Fraction operator-(const Fraction & ref_fra );
        Fraction operator=(const Fraction & ref_fra );
*/

};

/*
void Fraction::show()
{
    cout << num << "/" << endl;
}
*/

Fraction & Fraction::operator++()
{
    this->num = this-> num + this->denom;
    //num = num+denom;
    return *this;
}

Fraction  Fraction::operator++(int)
{
    Fraction old;
    old = *this;
    num = num + denom;
    return old;
}

Fraction & Fraction::operator=(const Fraction & ref_fra)
{
    cout << "operator =" << endl;
    if(this == &ref_fra)
        return *this;
    num = ref_fra.num;
    denom = ref_fra.denom;
    return *this;
}

ostream & operator<<( ostream & os,const Fraction & ref_fra)
{
    os << ref_fra.num << "/" << ref_fra.denom << endl;
    return os;
}

istream & operator>>( istream & is, Fraction & ref_fra)
{
    cout << "please enter numerator" << endl;
    is >> ref_fra.num ;
    cout << "please enter denominator" << endl;
    is >> ref_fra.denom ;
    
    return is;
}

Fraction operator+(const Fraction & oper,const Fraction & oper1)
{
    Fraction res;
    res.num = oper.num*oper1.denom + oper1.num*oper.denom;
    res.denom = oper.denom*oper1.denom;
    return res;
}
Fraction operator*(const Fraction & oper,const Fraction & oper1)
{
    Fraction res;
    res.num = oper.num*oper1.num;
    res.denom = oper.denom*oper1.denom;
    return res;
}

int main( int argc,const char * argv[] )
{

    Fraction  fra;
    Fraction  fra1(1,3);
    //fra.show();
    
    //cin >> fra;
    cout << fra << endl;
    cout << fra+fra1 << endl; 
    cout << fra*fra1 << endl; 

    ++fra;
    cout << fra << endl;

    cout << fra1++ << endl;
    cout << fra1 << endl;
    return 0;
}
