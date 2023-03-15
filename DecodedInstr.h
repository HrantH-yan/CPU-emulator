typedef unsigned int word;
struct DecodedInstr
{
    unsigned char Op;     //Operation (ALU, Comparison, Load/Store)
    unsigned char Instr;  //Instruction of Operation
    word * src1;          //source 1
    word * src2;          //source 2
    word dest;   //destination consider to make it pointer
};

enum OPS
{
    ALU, Comparison, MemOp, 
    PowOFF 
};
enum Instr 
{
    Add = 0, Sub, Mul, Or, And, Xor, Not, SHL, SHR,      // ALU instructions
    Equal = 0, Lesser, Bigger, EqLess, EqBigg, Always,    // Comparison instructions
    Store = 0, Load    // Storage memory instructions
};