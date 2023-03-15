class RAM : public StorageMemBus
{
    void Store (word address, word data);
    word Load (word address);
};