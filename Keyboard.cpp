typedef unsigned int word;
#include <iostream>
#include "input.h"
#include "Keyboard.h"


word Keyboard::read()
{
    word prpdigit = 1; //proper digit
    word in = 0;
    std::string input;
    std::cout<<"Enter the input(non-negative integer)"<<std::endl; // Keyboard doesn't really say us to input,
    std::cin>>input;                                               // but for simulator it's more convenient
    for (int i = 0; i < input.length(); ++i)
    {
        if(isdigit(input[input.length()-1 - i]))
        {
            in += (input[input.length()-1 - i] - '0')*prpdigit;
            prpdigit *= 10;
        }
        else
        {
            throw std::runtime_error("Wrong Input: Only non-negative integers allowed");
        }
    }
    return in;
}