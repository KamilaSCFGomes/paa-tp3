#include <stdlib.h>

#include "KMP.h"
#include "Musica.h"


// Complexidade (tam trecho) * (3)
void determinaPrefixo(Musica *possivePlagio, int v[]) { // Prefixos evitarão a busca repetida
    int tam = 0;
    v[0] = 0;

    int i = 1;
    while(i < possivePlagio->tam) { // Calcula o maior prefixo para cada posição 
        if(possivePlagio->diferencaEntreNotas[i] == possivePlagio->diferencaEntreNotas[tam]) {
            tam++;
            v[i] = tam;
            i++;
        } else { // Tenta aproveitar dos valores já encontrados se a casa atual não corresponder àquela do maior tam
            if(tam != 0)
                tam = v[tam - 1];
            else {
                v[i] = 0;
                i++;
            }
        }
    }

}

// Complexidade (complexidade de determinaPrefixo()) + (tam musica) * 5 = O(m + t)
int KMP(Musica *musica, Musica *possivelPlagio) {
    int *v = (int*) malloc (possivelPlagio->tam * sizeof(int)); // Prefixos evitarão a busca repetida

    determinaPrefixo(possivelPlagio, v); // Calcula esses prefixos
    int i = 0, j = 0;
    while(i < musica->tam) { // Percorre por toda a música

        if(musica->diferencaEntreNotas[i] == possivelPlagio->diferencaEntreNotas[j])
            i++, j++; // Avança caso haja equivalência entre trecho e música
        if(possivelPlagio->tam == j) { // Correspondência completa encontrada
            free(v);
            return i - j; // Casa correta
        } else if(i < musica->tam && possivelPlagio->diferencaEntreNotas[j] != musica->diferencaEntreNotas[i]) {
            if(j == 0) // Caractere não corresponde e não existe prefixo usável
                i++; // (apenas avança)
            else
                j = v[j - 1]; // Caractere não corresponde e existe prefixo usável
        }

    } 
    
    free(v);
    return -1; // Caso onde toda a música foi percorrida e não há correspondência
}