#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define VERDADEIRO_FALSO 1
#define PREENCHER_LACUNAS 2

typedef struct {
    int tipo;
    short int dificuldade;
    short int peso;
    char assuntoPrincipal[20];
    char assuntoSecundario[20];
    char frase[1000];
    char resposta[100];
} SENTENCA;

bool eh_linha_branca(char linha[]) {
    if (linha[0] == '\n')
        return true;
    else
        return false;
}

int quantidadeSentencas (int tipo) {
    srand(time(NULL));
    int randomNum;
    int quantVF[6] = {3, 4, 5, 5, 5, 6};
    int quantSentenca[6] = {3, 4, 5, 6, 7, 8};

    if (tipo == VERDADEIRO_FALSO) {
        randomNum = rand() % 6;
        return quantVF[randomNum];
    } else {
        randomNum = rand() % 6;
        return quantSentenca[randomNum];
    }
}

bool enunciadoMultEscolha () {
    srand(time(NULL));
    int r = rand() % 2;
    if (r == 0) 
        return false; // Enunciado pede a alternativa FALSA
    else
        return true; // Enunciado pede a alternativa CORRETA
}

int respostaCorreta (int sentencas) {
    srand(time(NULL));
    int r  = rand() % sentencas + 1;
    return r ;
}

// Informe os nomes dos arquivos contendo as questões na execucao do programa
int main(int argc, char *argv[]) {
    int i, quantSentencas = 0;
    char buff[1000];

    FILE *fp = fopen("compilado_de_questoes.txt", "w");
    if (fp == NULL) {
        puts("Ocorreu um erro.");
        exit(7);
    }

    for (i = 1; i<argc; i++) {
        FILE *ftemp = fopen(argv[i], "r");
        if (ftemp == NULL) {
            printf("Erro ao abrir o arquivo '%s'!\nO arquivo nao existe ou possui um nome diferente.\nTente novamente.\n", argv[i]);
            exit(9);
        }

        FILE *comp = fopen("compilado_de_questoes.txt", "a");
        if (comp == NULL) {
            exit(8);
        }

        if (i != 1){
            fputs("\n\n", comp);
        }
        
        while (fgets(buff, 1000, ftemp) != NULL) {
            if (eh_linha_branca(buff)) {
                quantSentencas++;
            }
            fputs(buff, comp);
        }
        
        quantSentencas++;

        fclose(ftemp);
        fclose(comp);
    }

    int sentencasVF = quantidadeSentencas(VERDADEIRO_FALSO);
    int sentencasLac = quantidadeSentencas(PREENCHER_LACUNAS);


    // Esse printf serve apenas para monitorar o resultado das variáveis
    printf("\n%d sentencas adicionadas no arquivo compilado. \n", quantSentencas);
    printf("Quantidade de sentenças do tipo lacunas: %d\n", sentencasLac);
    printf("Resposta correta: %d\n\n", respostaCorreta(sentencasLac));
    fclose(fp);
}