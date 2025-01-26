#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "EntradaESaida.h"
#include "ForcaBruta.h"
#include "KMP.h"
#include "BMH.h"
#include "Musica.h"


int main(int argc, char *argv[]) {

    struct timeval comeco, fim;
    struct rusage usoCPU;
    gettimeofday(&comeco, NULL);

    char *nomeDaEntrada = argv[1]; // Nome de arquivo inserido na execução do programa
    int numeroDoAlgoritmo = atoi(argv[2]); // Valor inserido na execução do programa (1 a 4)

    FILE *entrada = fopen(nomeDaEntrada, "r");
    if(argc != 3 || entrada == NULL) {
        imprimeErro("Argumentos com formatação incorreta");
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
                resultado = forcaBruta(musica, possivelPlagio); // Força Bruta
                break;
            case 2:
                resultado = KMP(musica, possivelPlagio); // Força Bruta
                break;
            case 3:
                resultado = BMH(musica, possivelPlagio);
                break;
            case 4:
                // a fazer
                break;
            default:
                imprimeErro("Opção de algoritmo inválida (deve ser de 1 a 4)");
                return 0;
        }

        geraSaida(saida, resultado); // Impressão no arquivo e no terminal

        destroiMusica(musica);
        destroiMusica(possivelPlagio);

    }

    fclose(entrada);
    fclose(saida);
    imprimeRelogio(comeco, fim, usoCPU); // Para análise de complexidade
    return 0;
}