sobaka: main.o SubroutinesSO.o Navicelle.o
	cc main.o SubroutinesSO.o Navicelle.o -lncurses -o sobaka 

main.o: Navicelle.o SubroutinesSO.h
	cc -c main.c SubroutinesSO.h

Navicelle.o: Navicelle.c SubroutinesSO.h
	cc -c Navicelle.c

SubroutinesSO.o: SubroutinesSO.c SubroutinesSO.h
	cc -c SubroutinesSO.c

clean:
	rm *.o
	rm *.gch
	rm sobaka