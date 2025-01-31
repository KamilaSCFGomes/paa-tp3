tp3: Main.o EntradaESaida.o ForcaBruta.o KMP.o BMH.o Musica.o ShiftAnd.o
	gcc Main.o EntradaESaida.o ForcaBruta.o KMP.o BMH.o Musica.o ShiftAnd.o -o tp3

Main.o: Main.c EntradaESaida.h ForcaBruta.h Musica.h KMP.h BMH.h ShiftAnd.h
	gcc -c Main.c

EntradaESaida.o: EntradaESaida.c EntradaESaida.h
	gcc -c EntradaESaida.c

ForcaBruta.o: ForcaBruta.c ForcaBruta.h
	gcc -c ForcaBruta.c

KMP.o: KMP.c KMP.h
	gcc -c KMP.c

BMH.o: BMH.c BMH.h
	gcc -c BMH.c

ShiftAnd.o: ShiftAnd.c ShiftAnd.h
	gcc -c ShiftAnd.c

Musica.o: Musica.c Musica.h
	gcc -c Musica.c


valgrind: tp3
	clear
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./tp3 entrada.txt 1

fb: tp3
	clear
	./tp3 entrada.txt 1

kmp: tp3
	clear
	./tp3 entrada.txt 2

bmh: tp3
	clear
	./tp3 entrada.txt 3

shift: tp3
	clear
	./tp3 entrada.txt 4

clean:
	rm -f Main.o EntradaESaida.o ForcaBruta.o KMP.o BMH.o Musica.o ShiftAnd.o tp3 saida.txt
	clear