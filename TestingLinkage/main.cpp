//Learnings
//  - so the default linkage of a symbol is external (except for consts - their default is internal)
//      - Although "extern" still needs to be used on the receiving end so the compiler knows that shit is coming from somewhere else
//
//  - static keyword is used to declare internal linkage (i.e. this symbol is restricted to this translation unit, available through whole file)
//      - static has separate meaning within a function, so that is a totally different case
//
//  - extern keyword is used to declare external linkage. Useful for consts since they default to internal linkage
//      - Obviously also used in "usage" file to tell compiler this is coming from somewhere else.
//
//  - With C++ 11 it is better to use anonymous namespaces for internal linkage than static
//      - This is because static only applies to variables/functions, not user-defined types (i.e. static class sample_class {...} is NOT valid)
//
//  - How does this all fit in with UnityBuild?
//      - Well, that combines shit into larger translation files, so there is a chance for more collisions if things are in unnamed namespaces, right?
//      - Yes, for example, my unnamed namespace with int withinNS works fine in this case, but in unibuild those unnamed namespaces are going to get
//          combined, and thus conflict because they have the same variable in it.
//
//  - Tangent: A translation unit == a basic compilation unit of a cpp file plus its headers


#include <iostream>

extern int i; // "heads up, I'm coming from a different translation unit"
int externalFoo(); // need to use forward declaration for the same reason ^^^ (compiler needs to know signature and that def will come from somewhere else)

//extern const int constI; //Linker error - needs to ALSO be extern in declaration file because const linkage is internal by default
extern const int constE;

// int foobar = 0; //also declared in foo.cpp - will this conflict? YEEEEP
//int foobar2;

//extern int invisibleOutside; //Linker error - unnamed namespace worked

namespace{
    int withinNS;
}


//Testing class declarations / definitions
class A;

class A
{
   // A() {};
    int bar;
};

class A;

#include "CircularA.h"
#include "CircularB.h"


int main()
{
    CircularA circularA;
    circularA.foo = new CircularB();

    //i is in a different translation unit, so I need to extern it above so compiler knows this isn't some undeclared variable
    std::cout << i << std::endl;
    std::cout << externalFoo() << std::endl;

    std::cout << "Printing const: " << constE << std::endl;

    //std::cout << "namespace variable: " << invisibleOutside << std::endl;

    system("pause");
    return 0;
}

