exeq: main.o Keyboard.o CPU.o ROM.o RAM.o Terminal.o Msg_Terminal.o
	g++ -o exeq main.o CPU.o ROM.o RAM.o Terminal.o Keyboard.o Msg_Terminal.o

main.o: main.cpp
	g++ -c main.cpp

Keyboard.o: Keyboard.cpp
	g++ -c Keyboard.cpp

CPU.o: CPU.cpp
	g++ -c CPU.cpp

ROM.o: ROM.cpp
	g++ -c ROM.cpp

RAM.o: RAM.cpp
	g++ -c RAM.cpp

Terminal.o: Terminal.cpp
	g++ -c Terminal.cpp

msg_Terminal.o: Msg_Terminal.cpp
	g++ -c Msg_Terminal.cpp

clean:
	rm *.o exeq
