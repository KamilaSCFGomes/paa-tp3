#include <stdlib.h>

#include "ForcaBruta.h"
#include "Musica.h"


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