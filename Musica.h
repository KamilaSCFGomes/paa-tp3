#ifndef MUSICA_H
#define MUSICA_H


typedef struct Musica {
    int *diferencaEntreNotas;
    int tam;
} Musica;


Musica *alocaMusica();

void defineTamanhoMusica(Musica *musica, int tamanho);

void destroiMusica(Musica *musica);

void notaComoInteiroParaSequencia(Musica *musica, int notas[]);


#endif