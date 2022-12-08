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
        
        while (fgets(buff, 1000, ftemp) != NULL) {
            if (eh_linha_branca(buff))
                quantSentencas++;
            fputs(buff, comp);
        }
        quantSentencas++;

        fputc('\n', comp);
        fclose(ftemp);
        fclose(comp);
    }

    printf("\n%d sentenças adicionadas no arquivo compilado.\n", quantSentencas);
    fclose(fp);
}