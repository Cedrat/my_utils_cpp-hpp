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

std::string lowercase(std::string name)
{
    int i;

    i = 0;
    while (name[i])
    {
        name[i] = std::tolower(name[i]);
        i++;
    }
    return (name);
}

std::string find_operator(std::string line)
{
    std::string ope[] = {"+", "=", "-", "*"};

    int i;

    i = 0;
    while (ope[i].size() == 1)
    {
        if (line.find(ope[i]) != std::string::npos)
            return(ope[i]);
        i++;
    }
    return ("");
}