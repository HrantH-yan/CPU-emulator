typedef unsigned int word;
#include <fstream>
#include "MainMemBus.h"
#include "ROM.h"
#include "CustomExceptions.h"

word ROM::GetInstr(word counter, int byte_quantity)
{
    word instruction = 0;
    std::ifstream code;
    char byte;
    unsigned char unsbyte;
    code.open ("Store_Fibo.bin", std::ios::in | std::ios::binary);        
    if (!code)
    {
        throw MMemory_ex();
    }
    code.seekg(counter);
    for (int i = 0; i < byte_quantity; ++i)
    {
        if (!code.read (&byte, 1)) 
        {
            throw MMemory_ex();
        }
        unsbyte = (unsigned char)byte;
        instruction = (instruction | (unsbyte<<((byte_quantity - (i+1))*8)));
    }
    code.close();
    return instruction;
}