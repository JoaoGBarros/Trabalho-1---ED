all: trabalho

trabalho: main.o NetMap.o ListaTerminal.o ListaRoteador.o terminal.o roteador.o
	gcc -o  trabalho main.o NetMap.o ListaTerminal.o ListaRoteador.o terminal.o roteador.o

main.o: main.c
	gcc -c main.c

NetMap.o: NetMap.c
	gcc -c NetMap.c

ListaTerminal.o: ListaTerminal.c
	gcc -c ListaTerminal.c

ListaRoteador.o: ListaRoteador.c
	gcc -c ListaRoteador.c

terminal.o: terminal.c
	gcc -c terminal.c

roteador.o: roteador.c
	gcc -c roteador.c

clean:
	rm -rf *.o

rmproper: clean
	rm -rf trabalho

run: trabalho
	./trabalho