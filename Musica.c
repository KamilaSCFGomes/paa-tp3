#include <stdlib.h>

#include "Musica.h"


Musica *alocaMusica() { // Alocação
    Musica *musica = (Musica*) malloc (sizeof(Musica));
    return musica;
}

void defineTamanhoMusica(Musica *musica, int tamanho) { // Separada da alocação inicial porque depende da leitura
    musica->tam = tamanho - 1; // Tamanho - 1 porque o vetor guarda a diferença até a próx pos,
                               // e não o próprio valor
    musica->diferencaEntreNotas = (int*) malloc (musica->tam * sizeof(int));
}

void destroiMusica(Musica *musica) { // Desalocação
    if(musica != NULL) {
        free(musica->diferencaEntreNotas);
        free(musica);
    }
}

void notaComoInteiroParaSequencia(Musica *musica, int notas[]) { // Faz a dif de valor de uma nota para pŕox
    for(int i = 0; i < musica->tam; i++) {
        int diferenca = notas[i + 1] - notas[i];
        if(diferenca < 0)
            diferenca += 12; // Evita que a diferença seja negativa
        musica->diferencaEntreNotas[i] = diferenca; // O vetor guarda a diferença até a próx pos
    }
}