#include <string>
#include <iostream>

void errors(int i)
{
    if (i == 0)
    {
        std::cout << "Error :\nnb of arguments (need two arguments)" << std::endl;
    }
    exit(0);
}