sobaka: main.o NavicellaPL.o
	cc main.o NavicellaPL.o -lncurses -o sobaka 

main.o: NavicellaPL.o SubroutinesSO.h
	cc -c main.c SubroutinesSO.h

NavicellaPL.o: NavicellaPL.c SubroutinesSO.h
	cc -c NavicellaPL.c

clean:
	rm *.o
	rm *.gch
	rm sobaka