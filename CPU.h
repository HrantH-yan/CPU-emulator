typedef unsigned int word;

const word reg_count = 15; //may be GPR regs??
const word counter_num = 14;
const word DefAdrReg = reg_count - 2;
const word input_num = 15;    // must be >= reg_count
const word Output_num = 15;   // must be >= reg_count
const word byte_quantity = 2; // 1, 2, 4 allowed


class CPU
{  
    private:
    MainMemBus* MMemry;
    StorageMemBus* SMemry;
    Input* in;
    Output* out;
    word regs[reg_count];
    word* counter = &regs[reg_count - 1];
    DecodedInstr DecInstr;
    word curr_instr;
    bool counter_overwritten = false;
    bool Power_off = false;
    int fetch();
    int decode();
    int execute();
    public:
    CPU(MainMemBus* mainMem, StorageMemBus* storageMem, Input* input, Output* output)
    {
        MMemry = mainMem;
        SMemry = storageMem;
        in = input;
        out = output;
    }
    int run();
};


