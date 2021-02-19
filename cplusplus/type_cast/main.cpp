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

class Person{
    private:
        string name;
        int age;
        int score;
    public:
        Person(){}
        Person(string _name): name(_name){}
        void show(){
            cout << "in Person's show" << endl;
            cout << "name = "<< name << endl;
            cout <<"age =  " << age << endl;
            cout << "score =  " << score << endl;
        }
        ~Person(){}

};
class Teacher  :public virtual Person{
    private:
        int number; 
    public:
        Teacher(){}
        void show(){
            cout << "in Teacher's show" << endl;
            Person::show();
            //cout << "number =  "  << number << endl;
        }
        ~Teacher(){}

};
class  Student :public virtual Person{
    private:
        int number; 
    public:
        Student(){}
        void show(){
            cout << "in student's show" << endl;
            Person::show();
            //cout << "number =  "  << number << endl;
        }
        ~Student(){}

};
class Assistent :public Student,public Teacher{
    public:
        Assistent(){}
        void show(){
            Teacher::show();
            Student::show();
            //Person::show();
        }
        ~Assistent(){}

};

int main( int argc,const char * argv[] )
{
/*{{{*/
    /*
    int a = 5;
    double b = 3.15;
    a = b;


    Student  ps;
    Student st;

    ps = st;

    Student *ptrps = &st;

    //st = ps;

    Student *ptrst = nullptr;// &ps;
    Student &refst = reinterpret_cast<Student &>(ps);

    ptrst = reinterpret_cast<Student *>(&ps);
    /////////////////////////////////////////////
    
    ptrst->show();
    refst.show();
    */
/*}}}*/
    Teacher tea;
    tea.show();

    Assistent ass;
    ass.show();
    
    return 0;

}
