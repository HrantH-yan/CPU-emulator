typedef unsigned int word;

#include "DecodedInstr.h"
#include "MainMemBus.h"
#include "StorageMemBus.h"
#include "input.h"
#include "output.h"
#include "CPU.h"

#include "ROM.h"
#include "RAM.h"
#include "Keyboard.h"
#include "Terminal.h"


int main()
{
    int is_ok;
    MainMemBus* MMemry = new ROM;
    StorageMemBus* SMemry = new RAM;
    Input* in = new Keyboard;
    Output* out = new Terminal;
    CPU proc(MMemry, SMemry, in, out);
    is_ok = proc.run();
    return is_ok;
}