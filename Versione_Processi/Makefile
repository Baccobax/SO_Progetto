Progetto_Processi: main.o menu.o Navicelle.o Nemici.o collision.o
	cc main.o menu.o Navicelle.o Nemici.o collision.o -lncurses -o Progetto_Processi

main.o: Navicelle.o Nemici.o SubroutinesSO.h
	cc -c main.c SubroutinesSO.h

Navicelle.o: Navicelle.c SubroutinesSO.h
	cc -c Navicelle.c

Nemici.o: Nemici.c SubroutinesSO.h
	cc -c Nemici.c

menu.o: menu.c SubroutinesSO.h
	cc -c menu.c

collision.o: collision.c SubroutinesSO.h
	cc -c collision.c

clean:
	rm *.o
	rm *.gch
	rm Progetto_Processi