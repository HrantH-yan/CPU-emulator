#include <iostream>
#include "DecodedInstr.h"
#include "MainMemBus.h"
#include "StorageMemBus.h"
#include "input.h"
#include "output.h"
#include "CPU.h"


int CPU::run()
{  
    while(true)
    { 
        int is_ok;
        is_ok = fetch(); 
        if(is_ok != 0)
        {
            return is_ok;
        }

        is_ok = decode();
        if(is_ok != 0)
        {
            return is_ok;
        }

        is_ok = execute();
        if(is_ok != 0)
        {
            return is_ok;
        }   
        
        if (Power_off)
        {
            break;
        } 
        if(!counter_overwritten)
        {
            *counter += 4;
            
        }
        counter_overwritten = false;
           
    }

    return 0;
}
int CPU::fetch()
{
    curr_instr = 0;
    for(int i = 0; sizeof(word) > i * byte_quantity; ++i)
    {
        try
        {
            word temp = MMemry->GetInstr(*counter + (i*byte_quantity), byte_quantity);
            curr_instr = (curr_instr | (temp<<(8*(sizeof(word) - (i + 1)*byte_quantity))));
        }
        catch(std::exception & ex)
        {
            std::cerr<<ex.what()<<'\n';
            return 1;
        }
    }                                  
    return 0;
}
int CPU::decode()
{
    // Operation
    DecInstr.Op = ((curr_instr>>28) & 0b11);      //00XX0000 of Operation byte

    //Instruction    
    DecInstr.Instr = ((curr_instr>>24) & 0xf);    //0000XXXX of Operation byte


        bool isInputSrc1 = false; //if src1 is input then input src2 must be same src1!

    //source 1
    if (((curr_instr>>24) & 0x80) == 0x80)            //Immediate src1 
    {
        DecInstr.src1 = new word;
        *DecInstr.src1 = (curr_instr>>16) & 0xff;
    }                              
    else if (((curr_instr>>16) & 0xff) == input_num)  //Input src1
    {
        try
        {
        DecInstr.src1 = new word;
        *DecInstr.src1 = in->read();   
        isInputSrc1 = true;        
        }
        catch(std::exception &ex)
        {
            std::cerr<<ex.what()<<'\n';
            return 2;
        }
    }
    else if( (((curr_instr>>16) & 0xff) < reg_count)) //Register src1
    {
        DecInstr.src1 = new word;
        *DecInstr.src1 = regs[(curr_instr>>16) & 0xff];
    }
    else
    {
        std::cerr<<"Unavailable Instruction code: Wrong source 1 address"<<'\n';
        return 3;
    }

    //source 2
    if (((curr_instr>>24) & 0x40) == 0x40)            //Immediate src2
    {
        DecInstr.src2 = new word;
        *DecInstr.src2 = (curr_instr>>8) & 0xff;
    }      
    else if (((curr_instr>>8) & 0xff) == input_num)   //Input src2
    {
        if (isInputSrc1)
        {
            DecInstr.src2 = DecInstr.src1;
        }
        else
        {
            try
            {
            DecInstr.src2 = new word;
            *DecInstr.src2 = in->read();           
            }
            catch(std::exception &ex)
            {
                std::cerr<<ex.what()<<'\n';
                return 4;
            }            
        }
    }                        
    else if((((curr_instr>>8) & 0xff) < reg_count))   //Register src2
    {
        DecInstr.src2 = new word;
        *DecInstr.src2 = regs[(curr_instr>>8) & 0xff];
    }
    else
    {
        std::cerr<<"Unavailable Instruction code: Wrong source 2 address"<<'\n';
        return 5;
    }

    /// Destination
    DecInstr.dest = curr_instr & 0xff;

    return 0;
}
int CPU::execute()
{
    if((DecInstr.Op == ALU) && DecInstr.dest < reg_count)
    {
        if(DecInstr.dest == counter_num)
        {
            counter_overwritten = true;
        }
        switch (DecInstr.Instr)
        {
        case Add:
            regs[DecInstr.dest] = (*DecInstr.src1) + (*DecInstr.src2);
            break;
        case Sub:  
            regs[DecInstr.dest] = (*DecInstr.src1) - (*DecInstr.src2);
            break;
        case Mul:
            regs[DecInstr.dest] = (*DecInstr.src1) * (*DecInstr.src2);
            break;
        case Or:
            regs[DecInstr.dest] = (*DecInstr.src1) | (*DecInstr.src2);
            break;
        case And:
            regs[DecInstr.dest] = (*DecInstr.src1) & (*DecInstr.src2);
            break;
        case Xor:
            regs[DecInstr.dest] = (*DecInstr.src1) ^ (*DecInstr.src2);
            break;        
        case Not:
            regs[DecInstr.dest] = ~(*DecInstr.src1);
            break;
        case SHL:
            regs[DecInstr.dest] = (*DecInstr.src1)<<(*DecInstr.src2);
            break;        
        case SHR:
            regs[DecInstr.dest] = (*DecInstr.src1)>>(*DecInstr.src2);
            break;
        default:
            std::cerr<<"Wrong ALU instruction"<<'\n';
            return 6;
        }
    }
    else if ((DecInstr.Op == ALU) && (DecInstr.dest == Output_num))
    {
        try
        {
            switch (DecInstr.Instr)
            {
            case Add:
                out->send((*DecInstr.src1) + (*DecInstr.src2));
                break;
            case Sub:  
                out->send((*DecInstr.src1) - (*DecInstr.src2));
                break;
            case Mul:
                out->send((*DecInstr.src1) * (*DecInstr.src2));
                break;
            case Or:
                out->send((*DecInstr.src1) | (*DecInstr.src2));
                break;
            case And:
                out->send((*DecInstr.src1) & (*DecInstr.src2));
                break;
            case Xor:
                out->send((*DecInstr.src1) ^ (*DecInstr.src2));
                break;        
            case Not:
                out->send(~(*DecInstr.src1));
                break;
            case SHL:
                out->send((*DecInstr.src1)<<(*DecInstr.src2));
                break;        
            case SHR:
                out->send((*DecInstr.src1)>>(*DecInstr.src2));
                break;
            default:
                std::cerr<<"Wrong ALU instruction"<<'\n';
                return 6;
            }       
        }
        catch(const std::exception& ex)
        {
            std::cerr<<ex.what()<<'\n';
            return 7;
        }
    }
    else if (DecInstr.Op == Comparison)
    {
        switch (DecInstr.Instr) 
        {
        case Equal:
            if (*DecInstr.src1 == *DecInstr.src2)
            {
                *counter = DecInstr.dest;
                counter_overwritten = true;
            }
            break;
        case Lesser:
            if (*DecInstr.src1 < *DecInstr.src2)
            {
                *counter = DecInstr.dest;
                counter_overwritten = true;
            }
            break;
        case Bigger:
            if (*DecInstr.src1 > *DecInstr.src2)
            {
                *counter = DecInstr.dest;
                counter_overwritten = true;
            }
            break;
        case EqLess:
            if (*DecInstr.src1 <= *DecInstr.src2)
            {
                *counter = DecInstr.dest;
                counter_overwritten = true;
            }
            break;
        case EqBigg:
            if (*DecInstr.src1 >= *DecInstr.src2)
            {
                *counter = DecInstr.dest;
                counter_overwritten = true;
            }
            break;
        case Always:
            *counter = DecInstr.dest;
            counter_overwritten = true;
            break;
        default:
            std::cerr<<"Wrong Comparison Instruction"<<'\n';
            return 8; 
        }
    }
    else if (DecInstr.Op == MemOp)
    {
        switch (DecInstr.Instr)
        {
        case Store:
            if(DecInstr.dest < reg_count) //Dest here is Register number to store
            {
                try
                {
                    SMemry->Store(regs[DefAdrReg], regs[DecInstr.dest]);
                }
                catch(const std::exception& ex)
                {
                    std::cerr<<ex.what()<<'\n';
                    return 9;
                }
                break;                
            }
            else 
            {
                std::cerr<<"Wrong destination(number of Register) to store"<<'\n';
                return 10;
            }
            break;
        case Load:
            if (DecInstr.dest < reg_count)
            {
                try
                {
                    regs[DecInstr.dest] = SMemry->Load(regs[DefAdrReg]);
                }
                catch(const std::exception& ex)
                {
                    std::cerr<<ex.what()<<'\n';
                    return 11;
                }
            }
            else
            {
                std::cerr<<"Wrong destination(number of Register) to load"<<'\n';
                return 12;
            }
        default:
            break;
        }
    }
    else if (DecInstr.Op == PowOFF) 
    {
        Power_off = true;
    }
    else 
    {
        std::cerr<<"Wrong ALU destination"<<'\n';
        return 13;
    }

    // Freeing pointers
    if (DecInstr.src1)
    {
        delete DecInstr.src1;
    }
    if (DecInstr.src2)
    {
        delete DecInstr.src2;
    }
    return 0;
}
