typedef unsigned int word;
#include <fstream>
#include "MainMemBus.h"
#include "ROM.h"

word ROM::GetInstr(word counter, int byte_quantity)
{
    word instruction = 0;
    std::ifstream code;
    char byte;
    unsigned char unsbyte;
    code.open ("Store_Fibo.bin", std::ios::in | std::ios::binary);        
    if (!code)
    {
        throw std::runtime_error("Failed to open MainMem file");

    }
    for (int i = 0; i < byte_quantity; ++i)
    {
        code.seekg(counter +i);
        if (!code.read (&byte, 1)) 
        {
            throw std::runtime_error("Failed to read from MainMem file");

        }
        unsbyte = (unsigned char)byte;
        instruction = (instruction | (unsbyte<<((byte_quantity - (i+1))*8)));
    }
    code.close();
    return instruction;
}