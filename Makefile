tp3: Main.o EntradaESaida.o ForcaBruta.o
	gcc Main.o EntradaESaida.o ForcaBruta.o -o tp3

Main.o: Main.c EntradaESaida.h ForcaBruta.h
	gcc -c Main.c

EntradaESaida.o: EntradaESaida.c EntradaESaida.h
	gcc -c EntradaESaida.c

ForcaBruta.o: ForcaBruta.c ForcaBruta.h
	gcc  -c ForcaBruta.c


valgrind: tp3
	clear
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./tp3 entrada.txt 1

fb: tp3
	clear
	./tp3 entrada.txt 1

clean:
	rm -f Main.o EntradaESaida.o ForcaBruta.o tp3 saida.txt
	clear