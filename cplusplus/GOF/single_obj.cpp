/*******************************************************************
 *
 *     File Name    :      single_obj.cpp
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Tue 17 Nov 2020 09:18:02 AM CST
 *     Description  :      Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include <iostream>
using namespace std;

class Window{

    static Window * pwd;

private:
    Window(){}
    Window(const Window & ref_wd){}

public:
    static Window * create_window();

    void show();
    ~Window(){}

};

//int Window::flag = 0;
Window* Window::pwd = nullptr;

void Window::show()
{
    cout << "========================" << endl;
    cout << "=   " << this <<"     =" << endl;
    for(int i = 0; i < 10; i++)
        cout << "=                      =" << endl;
    cout << "========================" << endl;
}

Window * Window::create_window()
{
    //lock()  thread_safty
    if(!pwd)
        pwd = new Window;
    //unlock()
    return pwd;
}
 
int main( int argc,const char * argv[] )
{
    Window * wd = nullptr;
    int n = 0;
    while(1)
    {
        cout << "window building..." << endl;
        cin >> n;
        if ( n == 666 )
        {
            wd = Window::create_window();
            wd->show();
        }
        else
            getchar();
        //    wd->show();
    }

    return 0;
}
