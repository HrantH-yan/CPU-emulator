typedef unsigned int word;
#include <fstream>
#include "StorageMemBus.h"
#include "RAM.h"



void RAM::Store(word address, word data)
{
    std::fstream ram;
    char byte;
    ram.open ("RAM.bin", std::ios::in | std::ios::out | std::ios::binary);        
    if (!ram)
    {
        throw std::runtime_error("Failed to open RAM file");
    }

    // copy all data of ram in temp and write it in ram(if not all this data will be set to zero)
    if(address != 0)
    {
        ram.seekp(address);
        char * temp = new char[ram.tellp()];
        if (!ram.read(temp, ram.tellp())) 
        {
            throw std::runtime_error("Failed to store data in RAM file");
        }
        if (!ram.write(temp,ram.tellp())) 
        {
            throw std::runtime_error("Failed to store data in RAM file");
        }
        delete temp;
        ram.seekp(0);
    }

    for(int i = 0; i < sizeof(word); ++i)
    {
        ram.seekp(address + i);
        byte = ((data>>((sizeof(word)-(i+1))*8)) & 0xff);

        if (!ram.write (&byte, 1)) 
        {
            throw std::runtime_error("Failed to store data in RAM file");
        }
    }    
    ram.close();
}
word RAM::Load (word address)
{
    word data = 0;
    std::ifstream ram;
    char byte;
    unsigned char unsbyte;
    ram.open ("RAM.bin", std::ios::in | std::ios::binary);        
    if (!ram)
    {
        throw std::runtime_error("Failed to open RAM file");
    }
    for(int i = 0; i < sizeof(word); ++i)
    {
        ram.seekg(address + i);

        if (!ram.read (&byte, 1)) 
        {
            throw std::runtime_error("Failed to load data from RAM file");
        }
        unsbyte = (unsigned char)byte;
        data = (data | (unsbyte<<((sizeof(word) - (i+1))*8)));
    }    
    ram.close();
    return data;
}
