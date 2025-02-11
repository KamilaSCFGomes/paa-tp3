#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "EntradaESaida.h"
#include "ForcaBruta.h"
#include "KMP.h"
#include "BMH.h"
#include "ShiftAnd.h"
#include "Musica.h"


int main(int argc, char *argv[]) {

    struct timeval comeco, fim;
    struct rusage usoCPU;

    char *nomeDaEntrada = argv[1]; // Nome de arquivo inserido na execução do programa
    int numeroDoAlgoritmo = atoi(argv[2]); // Valor inserido na execução do programa (1 a 4)

    FILE *entrada = fopen(nomeDaEntrada, "r");
    if(argc != 3 || entrada == NULL || numeroDoAlgoritmo < 1 || numeroDoAlgoritmo > 4) {
        imprimeErro("Argumentos com formatação incorreta");
        if(entrada != NULL)
            fclose(entrada);
        return 0;
    }
    FILE *saida = fopen("saida.txt", "w");

    int arquivoFoiLido = 1;
    while(arquivoFoiLido != 0) { // Será 0 se há erro crítico ou se chegou ao fim

        Musica *musica = alocaMusica();
        Musica *possivelPlagio = alocaMusica();
        arquivoFoiLido = leMusicas(entrada, musica, possivelPlagio);

        if(arquivoFoiLido == 0) { // Repetição da comparação porque deve ocorrer aqui, mas while(1) causa erro
            destroiMusica(musica);
            destroiMusica(possivelPlagio);
            break;
        }

        int resultado = -1;
        switch(numeroDoAlgoritmo) { // Valor inserido na execução do programa (1 a 4)
            case 1:
                gettimeofday(&comeco, NULL);
                resultado = forcaBruta(musica, possivelPlagio); // Força Bruta
                imprimeRelogio(comeco, fim, usoCPU); // Para análise de complexidade
                break;
            case 2:
                gettimeofday(&comeco, NULL);
                resultado = KMP(musica, possivelPlagio); // KMP
                imprimeRelogio(comeco, fim, usoCPU); // Para análise de complexidade
                break;
            case 3:
                gettimeofday(&comeco, NULL);
                resultado = BMH(musica, possivelPlagio); // BMH
                imprimeRelogio(comeco, fim, usoCPU); // Para análise de complexidade
                break;
            case 4:
                gettimeofday(&comeco, NULL);
                resultado = ShiftAnd(musica, possivelPlagio); // ShiftAnd
                imprimeRelogio(comeco, fim, usoCPU); // Para análise de complexidade
                break;
        }

        geraSaida(saida, resultado); // Impressão no arquivo e no terminal

        destroiMusica(musica);
        destroiMusica(possivelPlagio);

    }

    fclose(entrada);
    fclose(saida);
    return 0;
}