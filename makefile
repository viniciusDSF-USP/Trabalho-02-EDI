A = lib/avl
B = lib/filme
C = lib/aluno

all: main.o $(A).o $(B).o $(C).o
	@gcc main.o $(A).o $(B).o $(C).o -o main -Wall
	@./main

silent: main.o $(A).o $(B).o $(C).o
	@clear
	@gcc main.o $(A).o $(B).o $(C).o -o main -Wall
	@./main

main.o: main.c $(A).h $(B).h $(C).h
	@gcc -c main.c -o main.o

$(A).o: $(A).c $(A).h
	@gcc -c $(A).c -o $(A).o

$(B).o: $(B).c $(B).h $(A).h
	@gcc -c $(B).c -o $(B).o

$(C).o: $(C).c $(C).h $(A).h $(B).h
	@gcc -c $(C).c -o $(C).o

clean:
	@rm -rf *.o lib/*.o main