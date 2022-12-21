#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define VF 1
#define LAC 2
#define SAIR 99

typedef struct {
    unsigned short id;
    unsigned short tipo;
    unsigned short dificuldade;
    unsigned short peso;
    char assuntoPrincipal[10];
    char assuntoSecundario[10];
    char lacuna[150];
    char resposta[25];
    char verdadeira[150];
    char falsa[150]; 
} SENTENCA;

// EXCLUIR DEPOIS
void listar(FILE *fp) {
    fseek(fp, 0, SEEK_SET);
    SENTENCA sent;
    int lidos;
    puts("");
    printf("ID     TIPO    DIFIC    PESO    A. PRINCIPAL       A. SECUNDARIO             SENTENCA\n");
    while ((lidos = fread(&sent, sizeof(SENTENCA), 1, fp)) > 0) {
        if (sent.tipo == VF) {
            printf("%2hd      v/f        %hd      %hd      %-10s          %-10s       V: %s\n", sent.id, sent.dificuldade, sent.peso, sent.assuntoPrincipal, sent.assuntoSecundario, sent.verdadeira);
            printf("                                                                      F: %s\n\n", sent.falsa);
        } else {
            printf("%2hd      lac        %hd      %hd      %-10s          %-10s       %s\n", sent.id, sent.dificuldade, sent.peso, sent.assuntoPrincipal, sent.assuntoSecundario, sent.lacuna);
            printf("                                                                      Resposta: %s\n\n", sent.resposta);
        }
        puts("");
    }

}

int numSentencas(FILE* fp) {
    int lidos;
    SENTENCA sent;
    int quant=0;
    rewind(fp);
    while((lidos = fread(&sent, sizeof(SENTENCA), 1, fp)) > 0) {
        quant++;
    }

    return quant;
}

// Garante que o arquivo com o compilado de questoes sempre seja iniciado zerado
void criaCompilado() {
    FILE *fp = fopen("compilado_binario.bin", "wb");
    if (fp == NULL) {
        puts("Erro ao criar o arquivo com o compilado de sentencas!");
        exit(5);
    }
    fclose(fp);
}

int main(int argc, char *argv[]) {
    criaCompilado();
    int lidos;
    SENTENCA sent;

    for (int i=1; i<argc; i++) {
        FILE *temp = fopen(argv[i], "rb");
        FILE *comp = fopen("compilado_binario.bin", "ab");
        if (temp == NULL || comp == NULL) {
            printf("\nErro ao abrir o arquivo!\n\n");
            exit(3);
        }
        
        while((lidos = fread(&sent, sizeof(SENTENCA), 1, temp)) > 0) {
            fwrite(&sent, sizeof(SENTENCA), 1, comp);
        }
        fclose(comp);
        fclose(temp);
    }

    FILE* comp = fopen("compilado_binario.bin", "rb+");
    if (comp == NULL) {
        puts("Erro!");
        exit(3);
    }

    int quantSentencas = numSentencas(comp);





    fclose(comp);

    // EXCLUIR DEPOIS -> Testando se o arquivo de compilado esta recebendo sentencas
    listar(comp);
    printf("\n\n%d sentencas\n\n", quantSentencas);
}