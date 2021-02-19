/*******************************************************************
 *
 *     File Name    :      adaptor.cpp
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Wed 18 Nov 2020 10:48:48 AM CST
 *     Description  :      Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include <iostream>
using namespace std;


class DomesticVotage{
public:
    int output()
    {
        return 220;
    }
};

class PhoneVotage{
public:
    virtual int output() = 0;
/*    
    {
        return 5;
    }
*/

};
 
class VotageAdaptor :public PhoneVotage{
private:
    DomesticVotage * hmvtg;
public:
    VotageAdaptor()
    {
        hmvtg = new DomesticVotage;
    }

    int output()
    {
        return hmvtg->output() - 215;
    }
    ~VotageAdaptor()
    {
       delete hmvtg ;
    }
};
 
int main( int argc,const char * argv[] )
{
    PhoneVotage * pphovtg = new VotageAdaptor;
    if ( pphovtg->output() == 5 )
    {
        cout << "charging ..." << endl;
    }

    return 0;
}
