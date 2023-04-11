typedef unsigned int word;

#include "DecodedInstr.h"
#include "MainMemBus.h"
#include "StorageMemBus.h"
#include "Input.h"
#include "Output.h"
#include "Dbginfo.h"
#include "CPU.h"

#include "ROM.h"
#include "RAM.h"
#include "Keyboard.h"
#include "Terminal.h"
#include "Msg_Terminal.h"


int main()
{

    MainMemBus* MMemry = new ROM;
    StorageMemBus* SMemry = new RAM;
    Input* in = new Keyboard;
    Output* out = new Terminal;
    Dbginfo* dbg_out = new Msg_Terminal; 

    CPU proc(MMemry, SMemry, in, out, dbg_out);

    int is_ok = proc.run();

    return is_ok;
}