server	:	server.o	calc.o
					gcc -o server	server.o calc.o -lm -pthread
server.o	:	server.c
						gcc -c server.c
calc.o	:	calc.c	calc.h
					gcc -c calc.c
