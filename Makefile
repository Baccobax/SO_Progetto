sobaka: main.o SubroutinesSO.o Navicelle.o Nemici.o
	cc main.o SubroutinesSO.o Navicelle.o Nemici.o -lncurses -o sobaka 

main.o: Navicelle.o Nemici.o SubroutinesSO.h
	cc -c main.c SubroutinesSO.h

Navicelle.o: Navicelle.c SubroutinesSO.h
	cc -c Navicelle.c

Nemici.o: Nemici.c SubroutinesSO.h
	cc -c Nemici.c

SubroutinesSO.o: SubroutinesSO.c SubroutinesSO.h
	cc -c SubroutinesSO.c

clean:
	rm *.o
	rm *.gch
	rm sobaka