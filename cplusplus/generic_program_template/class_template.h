#include <iostream>
using namespace std;
 
 
template <typename T1,typename T2>
//class Demo{};
class Demo{
    private:
    T1  a;
    T2  b;
    public:
        Demo(){}
        Demo(T1 _a,T2 _b):a(_a),b(_b){}
        int compare();
        void show(T2 data);
        ~Demo(){}
};

template <typename T1,typename T2>
int Demo<T1,T2>:: compare()
{
    if( a == (T1) b )
        return 0;
    return a>(T1)b? 1:-1;
}

template<typename T1,typename T2>
void Demo< T1,T2 >::show(T2 data)
{
    cout << data << endl;
}
 
