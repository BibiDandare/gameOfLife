
all : main clean

main : tp4b.o
	gcc -o main tp4b.o

tp4b.o : tp4b.c
	gcc -o tp4b.o -c tp4b.c

clean :
	rm -f *.o