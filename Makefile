tp3: Main.o EntradaESaida.o ForcaBruta.o KMP.o BMH.o Musica.o
	gcc Main.o EntradaESaida.o ForcaBruta.o KMP.o BMH.o Musica.o -o tp3

Main.o: Main.c EntradaESaida.h ForcaBruta.h Musica.h
	gcc -c Main.c

EntradaESaida.o: EntradaESaida.c EntradaESaida.h
	gcc -c EntradaESaida.c

ForcaBruta.o: ForcaBruta.c ForcaBruta.h
	gcc -c ForcaBruta.c

KMP.o: KMP.c KMP.h
	gcc -c KMP.c

BMH.o: BMH.c BMH.h
	gcc -c BMH.c

Musica.o: Musica.c Musica.h
	gcc -c Musica.c


valgrind: tp3
	clear
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./tp3 entradas/entrada10_10.txt 1

fb: tp3
	clear
	./tp3 entradas/entrada10_2.txt 1

kmp: tp3
	clear
	./tp3 entrada.txt 2

bmh: tp3
	clear
	./tp3 entrada.txt 3

clean:
	rm -f Main.o EntradaESaida.o ForcaBruta.o KMP.o BMH.o Musica.o tp3 saida.txt
	clear