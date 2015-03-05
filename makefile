# MAKEFILE

proj: main.o 
	gcc -o proj main.o
main.o: main.c
	gcc -c main.c
clean:
	rm -f *.o proj
