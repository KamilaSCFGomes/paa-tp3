#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {

    char *numSaidas = (char*) malloc (6 * sizeof(char));
    char *tamMusica = (char*) malloc (6 * sizeof(char));
    char *tamTrecho = (char*) malloc (6 * sizeof(char));
    scanf("%5s", numSaidas);
    scanf("%5s", tamMusica);
    scanf("%5s", tamTrecho);

   

    char *nomeArquivo = (char*) malloc (100 * sizeof(char));
    snprintf(nomeArquivo, 100 * sizeof(char), "entradas/entrada%s_%s.txt", tamMusica, tamTrecho);


    FILE *arquivoEntrada = fopen(nomeArquivo, "w");
    for(int i = 0; i < atoi(numSaidas); i++) {
        fprintf(arquivoEntrada, "%s %s\n", tamMusica, tamTrecho);
        for(int j = 0; j < atoi(tamMusica); j++) {
            fprintf(arquivoEntrada, "A ");
        }
        fprintf(arquivoEntrada, "\n");
        for(int j = 0; j < atoi(tamTrecho) - 1; j++) {
            fprintf(arquivoEntrada, "A ");
        }
        fprintf(arquivoEntrada, "B\n");
    }
    fprintf(arquivoEntrada, "0 0");

    free(numSaidas);
    free(tamMusica);
    free(tamTrecho);
    free(nomeArquivo);
    fclose(arquivoEntrada);
    return 0;
}