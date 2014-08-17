#include <iostream>

//Goal: Sum the fibonacci sequence up to some specified number
//0 1 1 2 3 5 8 13 21
int main()
{

    int prev = 0;
    int current = 1;    

    int numOfLoops;
    std::cout << "Enter in number of loops:" << std::endl;
    std::cin >> numOfLoops;
    
    if (numOfLoops == 0)
    {
        std::cout << "It";
    }

    std::cout << std::endl;
    for (int loopCounter = 0; loopCounter < numOfLoops; loopCounter = loopCounter + 1)
    {
        //std::cout << loopCounter << std::endl;
        
    }

    
    std::cout << "Fib number: " << numOfLoops << " is " << current << std::endl;

    system("pause");
    return 0;
}