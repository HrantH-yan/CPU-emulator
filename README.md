# CPU-emulator

This is a 32 bit CPU emulator written in C++ using Clean Architecture

There are 5 basic devices(modules) to test or run a program 
-Getting intructions from ROM
-Reading input from Keyboard
-sending output to Terminal
-Storing/Loading data in/from RAM
_sending debug messages(exceptions)to Msg_Terminal

There is also 2 programs to test CPU
-Fibo.bin  -- prints in terminal given n-th elment of Fibonacci sequence
-Store_Fibo.bin -- stores in RAM.bin all elements(from 0 to given n-th) and prints them in terminal(after storing)


It's possoble to add more devices using interfaces from (MainMemBus, Input, Output, StorageMemBus, Dbginfo)

Check out instructions in Instructions.txt file
