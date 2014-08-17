#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#define ZBX_TCP_HEADER_DATA		"ZBXD"
#define ZBX_TCP_HEADER_VERSION		"\1"
#define ZBX_TCP_HEADER			ZBX_TCP_HEADER_DATA ZBX_TCP_HEADER_VERSION
#define ZBX_TCP_HEADER_LEN		5

std::unordered_map<std::string, std::string> bar;


void foo()
{
    bar.erase("foo");
}


int main()
{
    bar["foo"] = "bar";

    std::cout << ZBX_TCP_HEADER << std::endl;
    std::string& blah = bar["foo"];
    foo();
    blah += "test";
    system("pause");
    return 0;
}