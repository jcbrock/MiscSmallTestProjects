int i = 123; //external by default
int externalFoo() //external by default
{
    return 321;
}

const int constI = 100; // internal by default
extern const int constE = 100; // external explicitly


//Ok, how about namespaces?? With C++ 11 it is better to use anonymous namespaces for internal linkage than static
namespace {
    int invisibleOutside;
}

namespace{
    int withinNS;
}

int foobar = 111;
int foobar2;

//Testing class declarations / definitions
class A;

class A
{
    // A() {};
    int bar;
};

class A;

