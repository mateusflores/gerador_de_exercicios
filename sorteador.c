#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

// Informe os nomes dos arquivos contendo as questões na execucao do programa
int main(int argc, char *argv[]) {
    int i;

    // Garantindo que o arquivo 'compilado_de_questoes" sempre sera iniciado em branco
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
        
        char ch = fgetc(ftemp);
        while (ch != EOF) {
            fputc(ch, comp);
            ch = fgetc(ftemp);
        }

        fclose(ftemp);
        fclose(comp);
    }

    fclose(fp);
}