#ifndef FORCABRUTA_H
#define FORCABRUTA_H


typedef struct Musica {
    int *diferencaEntreNotas;
    int tam;
} Musica;


Musica *alocaMusica();

void defineTamanhoMusica(Musica *musica, int tamanho);

void destroiMusica(Musica *musica);

int forcaBruta(Musica *musica, Musica *possivelPlagio);

void notaComoInteiroParaSequencia(Musica *musica, int notas[]);


#endif