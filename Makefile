tp3: Main.o EntradaESaida.o ForcaBruta.o KMP.o Musica.o
	gcc Main.o EntradaESaida.o ForcaBruta.o KMP.o Musica.o -o tp3

Main.o: Main.c EntradaESaida.h ForcaBruta.h Musica.h
	gcc -c Main.c

EntradaESaida.o: EntradaESaida.c EntradaESaida.h
	gcc -c EntradaESaida.c

ForcaBruta.o: ForcaBruta.c ForcaBruta.h
	gcc -c ForcaBruta.c

KMP.o: KMP.c KMP.h
	gcc -c KMP.c

Musica.o: Musica.c Musica.h
	gcc -c Musica.c


valgrind: tp3
	clear
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./tp3 entrada.txt 2

fb: tp3
	clear
	./tp3 entrada.txt 1

kmp: tp3
	clear
	./tp3 entrada.txt 2

clean:
	rm -f Main.o EntradaESaida.o ForcaBruta.o KMP.o Musica.o tp3 saida.txt
	clear