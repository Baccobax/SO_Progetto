sobaka: main.o menu.o 
	cc main.o menu.o -lpthread -lncurses -o sobaka 

main.o: SubroutinesSO.h
	cc -c main.c SubroutinesSO.h

menu.o: menu.c SubroutinesSO.h
	cc -c menu.c


clean:
	rm *.o
	rm *.gch
	rm sobaka