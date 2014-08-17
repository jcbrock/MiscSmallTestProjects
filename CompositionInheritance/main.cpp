#include <iostream>
#include <vector>
#include <string>

class Parent
{
public:
    Parent() { std::cout << "Parent constructor" << std::endl; };
    ~Parent() {};

    void HideMe() { std::cout << "Parent HideMe" << std::endl; };

};

class Child : Parent
{
public:
    Child(){ std::cout << "Child constructor" << std::endl; };
    ~Child(){};

private:
    void HideMe() { std::cout << "Parent HideMe" << std::endl; };
};

class Contained
{
public:
    Contained(){
        std::cout << "Contained constructor" << std::endl;
    };
    ~Contained(){
        std::cout << "Contained destructor" << std::endl;
    };

};


class CompContainer
{
public:
    CompContainer(){ std::cout << "CompContainer constructor" << std::endl; };
    ~CompContainer(){
        std::cout << "CompContainer destructor" << std::endl;
        if (con)
        {
            std::cout << "Deleting con" << std::endl;
            delete con;
        }
    };

    //Contained con; //this has to be constructed first before CompContainer constructor can run obviously
    Contained* con = NULL; //this does NOT call the constructor of Contained, obviously nothing is made here
};


int main()
{
    Child c;
    {
        CompContainer cc;
        cc.con = new Contained();
    }

    system("pause");
    return 0;
}