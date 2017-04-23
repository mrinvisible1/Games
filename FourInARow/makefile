.PHONY : clean

FIAR: Main.o FIAR.o
	gcc -o FIAR FIAR.o Main.o -lncurses

FIAR.o: FIAR.c
	gcc -c FIAR.c -lncurses

Main.o : Main.c
	gcc -c Main.c

clean:
	rm -f *~
	rm -f *.o
	rm -f FIAR