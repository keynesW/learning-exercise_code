/*******************************************************************
 *
 *     File Name    :      main.cpp
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Wed 11 Nov 2020 11:36:53 AM CST
 *     Description  :       Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include <iostream>
using namespace std;

class Animal{
    public :
        int a;
        virtual void move()
        {
            cout << "move move ...." << endl;
        }
};

class Bird : protected Animal{

    public :
        /*
        void move()
        {
            cout << "fly  fly ...." << endl;
            cout << this-> a  << endl;

        }
        */
        void move(int){ cout << "move int"<< endl;}
        void eatWorm(){
            cout << "eat worm ..." << endl;
        }
};
 
class Rabbit :public Animal{
    public :
        void move()
        {
            cout << "jump jump ...." << endl;
        }
};
void hunt(Animal & ani)
{
    ani.move();
}

void hunt(Animal * ani)
{
    (*ani).move();
}

int main( int argc,const char * argv[] )
{
/*{{{*/
    /*
    Animal ani;
    hunt(ani);
    Bird bir;
    hunt(bir);
    Rabbit rab;
    hunt(rab);
    */

    Bird bir;
    bir.move();
    cout << "-------------------" << endl;

//    static_cast<Animal>(bir).move();

    cout << "-------------------" << endl;
    hunt(&rab);
/*}}}*/
/*
    Animal *ptrani;
    int n;
    cout << "please enter a num to select"<< endl;
    cout << " 1 : bird,   2 : rabbit"<< endl;
    cin >> n;
    switch (n)
    {
    case 1:
        ptrani = new Bird;
        break;
    case 2:
        ptrani = new Bird;
        break;
    }
    ptrani->move();

//    if(Bird * bird = dynamic_cast<Bird*>(ptrani))
//    {
//        bird->eatWorm();
//    }

    if(Bird * bird = reinterpret_cast<Bird*>(ptrani))
    {
        bird->eatWorm();
    }

*/
    return 0;
}
