/*******************************************************************
 *
 *     File Name    :      decorate.cpp
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog?? :      http://www.    .com/ 
 *     Created Time :      Wed 18 Nov 2020 01:48:21 PM CST
 *     Description  :      Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include <iostream>
using namespace std;

class Show {
public:
    virtual void show() = 0;
};

class ShowGirl :public Show{
private:
    string name;
public:
    ShowGirl( string _name )
    {
       name = _name; 
    }

    void show()
    {
        cout << name << "show" << endl;
        cout << "bikini" << endl;
    }
    ~ShowGirl(){}
};
 
class ShowBoy :public Show{
private:
    string name;
public:
    ShowBoy( string _name )
    {
       name = _name; 
    }

    void show()
    {
        cout << name << "show" << endl;
        cout << "短裤" << endl;
    }
    ~ShowBoy(){}
};

class Decorator :public Show{
private:
    Show * pshow;
public:

    void show()
    {
        pshow->show();
    }
    void setShow(Show * psw)
    {
        pshow = psw;
    }
};

class SpecilaizeDecorator:public Decorator{
public:
    void show()
    {
        Decorator::show();
        cout << "someclouth" << endl;
    }
};


int main( int argc,const char * argv[] )
{

    Show*  show = new ShowGirl("不知火舞");
    show->show();
cout << "---------------" << endl;
    Decorator *  pspdec = new SpecilaizeDecorator;
    pspdec->setShow( show );
    pspdec->show();

cout << "---------------" << endl;

    Decorator * pnspdec = new SpecilaizeDecorator;
    //pnspdec->setShow( show );
    pnspdec->setShow( pspdec );
    pnspdec->show();

cout << "---------------" << endl;

    Show* pshow = new ShowBoy("八神庵");
    pshow->show();

    return 0;
}
