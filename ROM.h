class ROM : public MainMemBus
{
    virtual word GetInstr(word counter, int byte_quantity);
};