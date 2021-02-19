/*******************************************************************
 *
 *     File Name    :      mystring.cpp
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Thu 12 Nov 2020 10:42:57 AM CST
 *     Description  :       Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include "mystring.h" 
#include <cstring>

/*
extern "C"
{
#include <strings.h>
}
//#include <strings.h>
//#include <cstrings>
*/

#define INPUT_ARRAY_SIZE   10


static char * mystrncpy(char * dst,const char * src, int n)
{
    for(int i = 0 ; i <= n ; ++ i)
        dst[i] = src[i];
    return dst;
}

MyString::MyString()
{
    pstr = new char[1]{'\0'};
    //size_ = 0;
    len = 0;
}
MyString::MyString(const char * ptr_c)
{
    if(ptr_c)
    {
        len = strlen(ptr_c);
        //size_ = len+1;
        pstr = new char[len+1];
        //strncpy( pstr , ptr_c ,len);
        mystrncpy( pstr , ptr_c, len);
    }
    else
        MyString();
}
MyString::MyString(char ch,int n)
{
    len = n;
    //size_ = n + 1;
    pstr = new char[n+1];
    for(int i = 0 ; i < n ; i++)
        pstr[i] = ch;
    pstr[n] = '\0';
    //memset((void *)pstr , ch, n);// there may be some problems
}
MyString::MyString(int n,char ch)
{
    len = n;
    //size_ = n + 1;
    pstr = new char[n+1];
    for(int i = 0 ; i < n ; i++)
        pstr[i] = ch;
    pstr[n] = '\0';
}
MyString::MyString(const MyString & ref_str)
{
    //cout << "in coyp constructor" << endl;
    len = ref_str.len;
    pstr = new char[len+1];
    strncpy(pstr,ref_str.pstr,len);
    mystrncpy( pstr , ref_str.pstr, len);
}

MyString & MyString::operator=( const MyString & ref_str )
{
    //cout << "in assignment operator" << endl;
    if( this == & ref_str )
        return *this;
    
    //char *ptr2free = str;
    //delete[] ptr2free;
    delete[] pstr;
    len = ref_str.len;
    pstr = new char[len+1];
    //strncpy(pstr,ref_str.pstr,len);
    mystrncpy( pstr , ref_str.pstr, len);
    //for(int i = 0; i <= ref_str.len ; ++ i)
    //    str[i] = ref_str.str[i];

    return *this;
}

MyString MyString::operator+(const MyString & ref_str)const
//shell be overloaded after copy constructor 
{
    //cout << "in operator +" << endl;
    MyString temp;

    temp.len = this->len + ref_str.len;
    temp.pstr = new char[len+1];

    //strncpy(temp.pstr,pstr,len);
    mystrncpy( temp.pstr , pstr, len);
    //cout << ref_str.pstr << endl;
    //strcat(&temp.pstr[len],ref_str.pstr);
    mystrncpy( &temp.pstr[len] , ref_str.pstr, ref_str.len);

    return temp;
}

MyString & MyString::operator+=(const MyString & ref_str)
{
    char * ptr2free = pstr;
    int len_old = len;
    len = this->len + ref_str.len;
    //size_ = len + 1;
    pstr = new char[len+1];
    //strncpy(pstr,ptr2free,len_old);
    mystrncpy( pstr , ptr2free, len_old);
    //strcat(&pstr[len_old],ref_str.pstr);
    mystrncpy( &pstr[len_old] , ref_str.pstr, ref_str.len);
    pstr[len] = '\0';
    delete [] ptr2free;

    return *this;
}
char MyString::operator[](int n)const
{
    //cout << "in operator [ ]" << endl;
    if ( n > len || n <= 0 )
        return 0;
    //cout << pstr[n-1] << endl;
    return pstr[n-1];
}
bool MyString::operator==(const MyString & ref_str)const
{
    if(!strcpy(pstr,ref_str.pstr))
        return true;
    return false;
}
bool MyString::operator!=(const MyString & ref_str)const
{
    if( *this == ref_str )
        return false;
    return true;
}
ostream & operator<<(ostream & os,const MyString & ref_str)
{
    //os << ref_str.pstr ;
    
    //for(int i = 0; i <= ref_str.len; ++i)
    //    os << (ref_str.pstr)[i]<< "  " ;
        
    for(int i = 0; i <= ref_str.len ; ++i)
    //{
    //    if( (const_cast<MyString &>(ref_str) )[i+1] <= 20 )
    //        os << " ";
    //    else
            os << ( ( const_cast<MyString &>(ref_str) )[i+1] );// << "  " ;
    //}
    os << " END ";
    return os; 
}
//istream & operator>>(istream & is,MyString & ref_str)
MyString & operator>>(istream & is,MyString & ref_str)
{
    char ch;
    int n = 0;
    char *input_array = new char[INPUT_ARRAY_SIZE];
    char * ptr2free = nullptr;

    int cunt = 0;
    while( ( ch = getchar() ) != '\n')
    {
        input_array[cunt+INPUT_ARRAY_SIZE*n] = ch;
        cunt++; 
        if( cunt == INPUT_ARRAY_SIZE )
        {
            cunt = 0;
            ptr2free = input_array;
            n+=2;
            input_array = new char [INPUT_ARRAY_SIZE*n];
            strcpy(input_array,ptr2free);
            delete[] ptr2free;
            n--;
        }
    }
    ref_str.len = cunt+INPUT_ARRAY_SIZE*n;
    ptr2free = ref_str.pstr;
    ref_str.pstr = new char[ref_str.len+1];
    strcpy(ref_str.pstr,input_array);
    delete [] ptr2free;

    //return is; 
    return ref_str; 
}

int MyString::size()const
{
    return len;
}
void MyString::clear()
{
    //bzero(pstr,len);
    //for( int i = 0 ; i < len ; ++i )
    //    pstr[i] = '\0';
    delete [] pstr; 
    len = 0;
    pstr = new char[1]{'\0'};
    //*str = '\0';

}

MyString::~MyString()
{
    //cout << "in deconstructor" << endl;
    delete[] pstr;
}
