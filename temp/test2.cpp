/*******************************************************************
 *
 *     File Name    :      test2.c
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Thu 21 Jan 2021 06:35:46 PM CST
 *     Description  :      Hello Word in C++ , GUN-style
 *
 ******************************************************************/
#include <iostream>

using namespace std;

class Base{
    int x;
public:
    static int a;

    void show()
    {
        cout << "show" << endl;
    }
    Base(int b):x(b){}
    virtual void display()
    {
        cout << x << endl;
    }
};

class Derived :public Base{
    int y;
public:
    Derived(int d):Base(d),y(4){}
    void display()
    {
        cout << y << endl;
    }
    void display(int c)
    {
        cout << y << " c :" << c <<endl;
    }
};
class Der:public Derived{

public:
    Der():Derived(3){}
    ~Der(){}
    void display()
    {
        cout << "in der" << endl;
    }
    void display(int c)
    {
        cout <<  "in der c :" << c <<endl;
    }
    
};
int Base::a = 5;

int main()
{
    Base * pbase = NULL;
    pbase->show();
    printf("%d\n",pbase->a);
    printf("------------\n");

    Base b(2);
    Derived d(3);
    b.display();
    //d.display();
    d.display(5);
    Base *p = &d;
    p->display();
    //Base p = static_cast<Base >(d);
    //p.display();
    //p->display(3);
    printf("------------\n");
    Der der;
    Derived * pderived = &der;
    pderived->display();
    pderived->display(3);
    der.display(3);

    //system("pause");
    return 0;
}

/*
#include <stdio.h>

int main( int argc,const char * argv[] )
{
    char c1,c2;
    int a1,a2;
    c1 = getchar();
    scanf("%2d",&a1);
    c2 = getchar();
    scanf("%3d",&a2);

    printf("%d,%d,%c,%c\n",a1,a2,c1,c2);

    return 0;
}

union Test{
    char a[4];
    short b;
}test; 
 
int main( int argc,const char * argv[] )
{
    short a = 0xff00;
    printf("%zd\n",sizeof(short));
    //test.a[0] = 256;
    test.a[0] = -256;
    printf("%#x\n",test.b);
    test.a[1] = 255;
    test.a[2] = 254;
    test.a[3] = 253;
    printf("%d\n",test.b);
    printf("%#x\n",test.b);
    printf("%d\n",a);
    return 0;
}
*/
