#include <stdlib.h>

#include "BMH.h"
#include "Musica.h"

int BMH(Musica *musica, Musica *possivelPlagio) {
    int *v = (int*) malloc (12 *sizeof(int)); // 12 porque são 12 notas diferentes
    
    for(int i = 0; i < 12; i++) { // Preenche com o tamanho do trecho
        v[i] = possivelPlagio->tam;
    }

    for(int i = 0; i < possivelPlagio->tam - 1; i++) { // Acha deslocamento
        v[possivelPlagio->diferencaEntreNotas[i]] = possivelPlagio->tam - i - 1;
    }

    int i = possivelPlagio->tam - 1;
    while(i < musica->tam) { // Procura na música
        int j = possivelPlagio->tam - 1;
        int k = i;

        while(j >= 0 && musica->diferencaEntreNotas[k] == possivelPlagio->diferencaEntreNotas[j]) {
            j--, k--; // Testa correspondência e passa para as casas anteriores
        }

        if(j < 0) { // Trecho encontrado
            free(v);
            return k + 1; // Casa de ocorrência
        }

        i+= v[musica->diferencaEntreNotas[i]]; // Atualiza índice

    }

    free(v);
    return -1; // Trecho não encontrado

}