#include "Musica.h"
#include "ShiftAnd.h"
#include <stdlib.h>
#include <stdio.h>

void printBinario(int numero, int bits) { // Imprimir binário para facilitar o debug

    for(int i = bits-1; i >= 0; i--) {
        printf("%d", (numero >> i) & 1);
    }
    printf("\n");

}

void criaMascaraShiftAnd(Musica* possivelPlagio, int* mascara) {

    for(int i = 0; i < 12; i++) { // Preenche com 0
        mascara[i] = 0;
    }

    for(int i = 0; i < possivelPlagio->tam; i++) { // Preenche com 1 nas posições correspondentes
        mascara[possivelPlagio->diferencaEntreNotas[i]] |= (1 << i);
    }

}


int ShiftAnd(Musica *musica, Musica *possivelPlagio) {

    int *mascara = (int*) malloc (12 * sizeof(int)); // 12 porque são 12 notas diferentes
    criaMascaraShiftAnd(possivelPlagio, mascara);

    int r = 0; // r será comparado com a máscara, começa com 0^m
    int mascaraCasamento = 1 << (possivelPlagio->tam - 1); // 10^(m-1), requisito para o casamento

    for (int i = 0; i < musica->tam; i++) { // Percorre a música
        r = ((r << 1) | 1) & mascara[musica->diferencaEntreNotas[i]];
        
        if (r & mascaraCasamento){
            free(mascara);
            return i - possivelPlagio->tam + 1; // posição do casamento
        }
    }

    free(mascara);
    return -1; // não houve casamento :(
}