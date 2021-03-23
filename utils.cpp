#include "my_utils_cpp.h"

std::string capslock(std::string name)
{
    int i;

    i = 0;
    while (name[i])
    {
        name[i] = std::toupper(name[i]);
        i++;
    }
    return (name);
}