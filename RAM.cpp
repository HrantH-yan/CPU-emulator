typedef unsigned int word;
#include <fstream>
#include "StorageMemBus.h"
#include "CustomExceptions.h"
#include "RAM.h"



void RAM::Store(word address, word data)
{
    std::fstream ram;
    char byte;
    ram.open ("RAM.bin", std::ios::in | std::ios::out | std::ios::binary);      
    if (!ram)
    {
        throw SMemory_ex();
    }

    // copy all data from ram in temp and write it in ram(if not, all this data will be set to zero)
    ram.seekp(0,std::ios::end);
    word ram_size = ram.tellp();
    ram.seekg(0);
    if(ram_size != 0)
    {
        char * temp = new char[ram_size];
        if (!ram.read(temp, ram_size)) 
        {
            delete temp;
            throw SMemory_ex();
        }
        ram.seekp(0);
        if (!ram.write(temp,ram_size)) 
        {
            delete temp;
            throw SMemory_ex();
        }
        delete temp;
    }

    // store data
    ram.seekp(address);
    for(int i = 0; i < sizeof(word); ++i)
    {
        byte = ((data>>((sizeof(word)-(i+1))*8)) & 0xff);

        if (!ram.write (&byte, 1)) 
        {
            throw SMemory_ex();
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
        throw SMemory_ex();
    }
    for(int i = 0; i < sizeof(word); ++i)
    {
        ram.seekg(address + i);

        if (!ram.read (&byte, 1)) 
        {
            throw SMemory_ex();
        }
        unsbyte = (unsigned char)byte;
        data = (data | (unsbyte<<((sizeof(word) - (i+1))*8)));
    }    
    ram.close();
    return data;
}
