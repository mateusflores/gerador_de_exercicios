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

typedef struct {
    unsigned short quantLacunas;
    unsigned short quantVF;
    char assuntos[30][30];
    int numAssuntos;
    int dificuldades[3];
    int numDific;
} ESPECIFICACAO_PROVA;

// Funcao fgets(), mas sem a quebra de linha no final da string
char* newFgets(char frase[], int tam) {
    fgets(frase, tam, stdin);
    for (int i=0; i<tam; i++) {
        if (frase[i] == '\n')
            frase[i] = '\0';
    }
    return frase;
}

void limpaBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
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

// Copia todas as sentencas do arquivo compilado para um array na Heap
SENTENCA* geraArray(FILE *fp, int tam) {
    SENTENCA sent;
    int lidos, i=0;
    SENTENCA *sentencas = (SENTENCA*) malloc(tam * sizeof(SENTENCA));

    while((lidos = fread(&sent, sizeof(SENTENCA), 1, fp)) > 0) {
        sentencas[i] = sent;
        i++;
    }
    return sentencas;
}

// Requisita as informações para gerar a prova e as armazena no arquivo "especificacao_questoes.bin"
void menuUsuario() {
    FILE *fp = fopen("especificacao_questoes.bin", "wb+");
    ESPECIFICACAO_PROVA espec;
    char frase[100];
    char dific[10];
    int i=0, j=0, n=0;
    espec.numAssuntos = 0, espec.numDific = 0;
    if (fp == NULL) {
        puts("Erro ao criar o arquivo 'especificacao_questoes.bin'!");
        exit(8);
    }

    puts("+---------------------------------------------------------------+");
    puts("| Insira quantas questoes do tipo PREENCHER LACUNAS voce deseja:|");
    printf("  RESPOSTA: ");
    scanf("%hd", &espec.quantLacunas);

    puts("|                                                               |");

    puts("| Insira quantas questoes do tipo VERDADEIRO/FALSO voce deseja: |");
    printf("  RESPOSTA: ");
    scanf("%hd", &espec.quantVF);

    puts("|                                                               |");
    limpaBuffer();

    puts("| Insira quais os assuntos desejados nas questoes:              |");
    puts("| (Apenas letras minusculas e assuntos separados por um espaco) |");
    printf("  RESPOSTA: ");
    newFgets(frase, 100);
    while(frase[n] != '\0') {
        if (frase[n] == ' ') {
            espec.assuntos[i][j] = '\0';
            i++;
            j=0;
        } else {
            espec.assuntos[i][j] = frase[n];
            j++;
        }
        n++;
    }
    espec.numAssuntos = i+1;

    puts("|                                                               |");

    n=0, i=0, j=0;
    puts("| Insira os niveis de dificuldade desejados:                    |");
    puts("| (1: facil; 2: intermediario; 3: dificil)                      |");
    puts("| (Insira apenas os numeros separados por espacos)              |");
    printf("  RESPOSTA: ");
    newFgets(dific, 10);
    while(dific[i] != '\0') {
        if (dific[i] != ' ') {
            espec.dificuldades[j] = (unsigned short) atoi(&dific[i]);
            j++;
        }
        i++;
    }
    espec.numDific = j;

    puts("+---------------------------------------------------------------+");

    
    fwrite(&espec, sizeof(ESPECIFICACAO_PROVA), 1, fp);
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
    SENTENCA *sentencas = geraArray(comp, quantSentencas);

    menuUsuario();


    fclose(comp);
    free(sentencas);
    

    // EXCLUIR DEPOIS -> Testando se o arquivo de compilado esta recebendo sentencas
    printf("\n\n%d sentencas\n\n", quantSentencas);
}