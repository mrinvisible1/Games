.PHONY : clean

SHIPS: main.o ships.o
	gcc -o SHIPS ships.o main.o
ships.o: ships.c
	gcc -c ships.c
main.o : main.c
	gcc -c main.c

clean:
	rm -f *~
	rm -f *.o
	rm -f SHIPS