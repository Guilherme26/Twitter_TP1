all: tp.out

tp.out: List.o Usuario.o
	gcc -w Main.c -o tp List.o Usuario.o

List.o: List/List.c
	gcc -g -c List/List.c

Usuario.o: Usuario.c
	gcc -g -c Usuario.c

clean:
	-rm -f Usuario.o
	-rm -f a.out
	-rm -f List.o