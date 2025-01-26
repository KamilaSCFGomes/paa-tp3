#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include <unistd.h>
#include <sys/resource.h>
#include <sys/time.h>

#include "EntradaESaida.h"
#include "ForcaBruta.h"


void imprimeRelogio(struct timeval comeco, struct timeval fim, struct rusage usoCPU) { // Para análise de complexidade
    getrusage(RUSAGE_SELF, &usoCPU);
    gettimeofday(&fim, NULL);

    double tempoDeCPU = (((usoCPU.ru_utime.tv_sec) * 1000) +
                         ((double)usoCPU.ru_utime.tv_usec) / 1000) //em ms
                         / sysconf(_SC_NPROCESSORS_ONLN); //divide pela quant. núcleos
    
    double tempoDeExecucao = ((fim.tv_sec - comeco.tv_sec) * 1000) +
                             ((double)(fim.tv_usec - comeco.tv_usec)) / 1000;//em ms
    
    printf("\nAnálise de tempo:\n");
    printf("Tempo de Execução: %.6lf ms\n",tempoDeExecucao);
    printf("Tempo de CPU:      %.6lf ms\n",tempoDeCPU);
    printf("Programa finalizado\n");
    return;
}

void imprimeErro(char *texto) { // Padroniza impressão e facilita debugging
    printf("ERRO! %s\n", texto);
}

int notaParaInteiro(char nota[]) { // Retorna um valor padronizado em inteiro
    if(strcmp(nota, "A") == 0) return 1;
    if(strcmp(nota, "A#") == 0 || strcmp(nota, "Bb") == 0) return 2;
    if(strcmp(nota, "B") == 0 || strcmp(nota, "Cb") == 0) return 3;
    if(strcmp(nota, "C") == 0 || strcmp(nota, "B#") == 0 ) return 4;
    if(strcmp(nota, "C#") == 0 || strcmp(nota, "Db") == 0) return 5;
    if(strcmp(nota, "D") == 0) return 6;
    if(strcmp(nota, "D#") == 0 || strcmp(nota, "Eb") == 0) return 7;
    if(strcmp(nota, "E") == 0 || strcmp(nota, "Fb") == 0) return 8;
    if(strcmp(nota, "F") == 0 || strcmp(nota, "E#") == 0) return 9;
    if(strcmp(nota, "F#") == 0 || strcmp(nota, "Gb") == 0) return 10;
    if(strcmp(nota, "G") == 0) return 11;
    // if(strcmp(nota, "G#") == 0 || strcmp(nota, "Ab") == 0) Verificação irrelevante
    return 12;
}

int leMusicas(FILE *arquivoMusicas, Musica *musica, Musica *possivelPlagio) { // Leitura do arquivo
    int tamanhoMaxLinha = 300;
    char *linhaLida = (char*) malloc (sizeof(char) * tamanhoMaxLinha);

    fgets(linhaLida, tamanhoMaxLinha, arquivoMusicas);
    char *t = strtok(linhaLida, " ");
    if(t == NULL) {
        defineTamanhoMusica(musica, 1); // Evita desalocação de valor não inicializado
        defineTamanhoMusica(possivelPlagio, 1); // Evita desalocação de valor não inicializado
        free(linhaLida);
        imprimeErro("Formatação de arquivo incorreta");
        return 0;
    }
    if(linhaLida[0] == '0' && linhaLida[2] == '0') {
        defineTamanhoMusica(musica, 1); // Evita desalocação de valor não inicializado
        defineTamanhoMusica(possivelPlagio, 1); // Evita desalocação de valor não inicializado
        free(linhaLida);
        return 0; // Fim do arquivo
    }

    int tamMusica = atoi(t);
    t = strtok(NULL, " ");
    int tamPossivelPlagio = atoi(t);

    fgets(linhaLida, tamanhoMaxLinha, arquivoMusicas);
    t = strtok(linhaLida, " ");
    int *notas = (int*) malloc (tamMusica * sizeof(int));
    for(int i = 0; i < tamMusica - 1; i++) { // Armazena cada nota da música base
        notas[i] = notaParaInteiro(t);
        t = strtok(NULL, " ");
    }
    int casaAtual = 0;
    while(t[casaAtual] != '\n') casaAtual++; // Remove a quebra de linha
    t[casaAtual] = '\0';
    notas[tamMusica - 1] = notaParaInteiro(t);

    fgets(linhaLida, tamanhoMaxLinha, arquivoMusicas);
    t = strtok(linhaLida, " ");
    int *segundasNotas = (int*) malloc (tamPossivelPlagio * sizeof(int));
    for(int i = 0; i < tamPossivelPlagio - 1; i++) { // Armazena cada nota do trecho comparado
        segundasNotas[i] = notaParaInteiro(t);
        t = strtok(NULL, " ");
    }
    casaAtual = 0;
    while(t[casaAtual] != '\n') casaAtual++; // Remove a quebra de linha
    t[casaAtual] = '\0';
    segundasNotas[tamPossivelPlagio - 1] = notaParaInteiro(t);

    if(tamMusica < 2 || tamPossivelPlagio < 2) {
        defineTamanhoMusica(musica, 1); // Evita desalocação de valor não inicializado
        defineTamanhoMusica(possivelPlagio, 1); // Evita desalocação de valor não inicializado
        free(linhaLida);
        free(notas);
        free(segundasNotas);
        imprimeErro("Comparar trechos de apenas uma nota é irrelevante");
        return 0; // Não faz sentido comparar trechos de apenas uma nota
    }

    defineTamanhoMusica(musica, tamMusica);
    defineTamanhoMusica(possivelPlagio, tamPossivelPlagio);
    notaComoInteiroParaSequencia(musica, notas); // Aqui o vetor guarda a diferença até a próx pos
    notaComoInteiroParaSequencia(possivelPlagio, segundasNotas); // Aqui o vetor guarda a diferença até a próx pos

    free(linhaLida);
    free(notas);
    free(segundasNotas);
    return 1; // Sucesso
}

void geraSaida(FILE *saida, int resultado) { // Impressão no arquivo e no terminal
    if(resultado < 0) { // N = Não há plágio
        printf("N\n");
        fprintf(saida, "N\n");
    } else {
        printf("S %d\n", resultado);
        fprintf(saida, "S %d\n", resultado); // S = Há plágio
    }
}