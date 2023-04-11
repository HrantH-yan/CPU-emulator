typedef unsigned int word;
#include <iostream>
#include "Dbginfo.h"
#include "Msg_Terminal.h"


void Msg_Terminal::dbgsend(word msg_code)
{
    switch (msg_code)
    {
    case 1:
        std::cerr<<"!!!Debug message!!!\n Failed to get Instruction from MainMemBus\n";
        break;
    case 2:
        std::cerr<<"!!!Debug message!!!\n Failed to read Input(src1)\n";
        break;
    case 3:
        std::cerr<<"!!!Debug message!!!\n Unavailable Instruction code: Wrong source 1 address\n";
        break;
    case 4:
        std::cerr<<"!!!Debug message!!!\n Failed to read Input(src2)\n";
        break;
    case 5:
        std::cerr<<"!!!Debug message!!!\n Unavailable Instruction code: Wrong source 2 address\n";
        break;
    case 6:
        std::cerr<<"!!!Debug message!!!\n Wrong ALU instruction\n";
        break;
    case 7:
        std::cerr<<"!!!Debug message!!!\n Failed to send data to output\n";
        break;
    case 8:
        std::cerr<<"!!!Debug message!!!\n Wrong Comparison Instruction\n";
        break;
    case 9:
        std::cerr<<"!!!Debug message!!!\n Failed to store data in Storage\n";
        break;
    case 10:
        std::cerr<<"!!!Debug message!!!\n Wrong destination(number of Register) to store\n";
        break;
    case 11:
        std::cerr<<"!!!Debug message!!!\n Failed to load data from Storage\n";
        break;
    case 12:
        std::cerr<<"!!!Debug message!!!\n Wrong destination(number of Register) to load\n";
        break;
    case 13:
        std::cerr<<"!!!Debug message!!!\n Wrong ALU destination\n";
        break;
    default:
        std::cerr<<"!!!Debug message!!!\n Unregistered message code("<<msg_code<<")\n";
    }

}