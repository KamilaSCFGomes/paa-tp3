#ifndef ENTRADAESAIDA_H
#define ENTRADAESAIDA_H


#include <sys/resource.h>
#include <sys/time.h>

#include "ForcaBruta.h"


void imprimeRelogio(struct timeval comeco, struct timeval fim, struct rusage usoCPU);

void imprimeErro(char *texto);

int leMusicas(FILE *arquivoMusicas, Musica *musica, Musica *possivelPlagio);

void geraSaida(FILE *saida, int resultado);


#endif