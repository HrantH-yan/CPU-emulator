class StorageMemBus
{
    public:
    virtual void Store (word address, word data) = 0;
    virtual word Load (word address) = 0;
};