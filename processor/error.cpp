#include <iostream>
#include <cstdlib>
#include <string_view>

void error(std::string_view message)
{
    std::cerr << message << std::endl;
    exit(-1);
}
