all: tp.out

tp.out: List.o Usuario.o Timeline.o
	gcc -w Main.c -o tp List.o Usuario.o Timeline.o

List.o: List/List.c
	gcc -g -c List/List.c

Timeline.o: Timeline/Timeline.c
	gcc -g -c Timeline/Timeline.c

Usuario.o: Usuario.c
	gcc -g -c Usuario.c

clean:
	-rm -f Usuario.o
	-rm -f a.out
	-rm -f List.o
	-rm -f Timeline.o