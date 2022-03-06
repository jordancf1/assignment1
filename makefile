fulawkaJordanA1: fulawkaJordanA1.o main.o 
	gcc -Wall -std=c99 fulawkaJordanA1.o main.o -o fulawkaJordanA1 

fulawkaJordanA1.o: fulawkaJordanA1.c fulawkaJordanA1.h 
	gcc -Wall -std=c99 -c fulawkaJordanA1.c

main.o: main.c fulawkaJordanA1.h 
	gcc -Wall -std=c99 -c main.c

clean: 
	rm *.o fulawkaJordanA1 