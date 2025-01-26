#include <stdlib.h>

#include "ForcaBruta.h"


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

int comparaCasaAtual(Musica *musica, Musica *possivelPlagio, int casaAtualMusica) { // Loop interior da Força Bruta
    for(int i = 0; i < possivelPlagio->tam; i++) {
        if(possivelPlagio->diferencaEntreNotas[i] != musica->diferencaEntreNotas[casaAtualMusica + i])
            return 0; // Retorna falha caso não haja equivalência
    }

    return 1; // Sucesso se há equivalência para toda casa do trecho suspeito
}

int forcaBruta(Musica *musica, Musica *possivelPlagio) {
    if(musica->tam < possivelPlagio->tam)
        return -1; // O trecho suspeito não pode ser maior que o original

    for(int i = 0; i <= musica->tam - possivelPlagio->tam; i++) { // Testa toda casa
        if(comparaCasaAtual(musica, possivelPlagio, i) == 1)
            return i; // Casa haja sucesso, retorna a primeira casa de ocorrência
    }

    return -1; // Caso onde toda casa foi testada e não houve sucesso
}

void notaComoInteiroParaSequencia(Musica *musica, int notas[]) { // Faz a dif de valor de uma nota para pŕox
    for(int i = 0; i < musica->tam; i++) {
        int diferenca = notas[i + 1] - notas[i];
        if(diferenca < 0)
            diferenca += 12; // Evita que a diferença seja negativa
        musica->diferencaEntreNotas[i] = diferenca; // O vetor guarda a diferença até a próx pos
    }
}