typedef unsigned int word;
#include <iostream>
#include "Output.h"
#include "Terminal.h"


void Terminal::send(word Data)
{
    std::cout<<Data<<' ';
}