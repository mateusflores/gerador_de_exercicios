#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

void removeQuabraLinha(char frase[], int tam) {
    for (int i=0; i<tam; i++) {
        if (frase[i] == '\n')
            frase[i] = '\0';
    }
}

FILE* novoArquivo() {
    char nome[20];
    puts("Insira o nome do arquivo que vai receber as sentencas (EX: 'exemplo.bin')");
    printf("Resposta: ");    
    fgets(nome, 20, stdin);
    removeQuabraLinha(nome, 20);

    FILE *fp = fopen(nome, "ab+");
    if (fp == NULL) {
        puts("ERRO: Nao foi possivel criar/abrir o arquivo.");
        return NULL;
    }
    printf("Arquivo '%s' criado com sucesso!\n\n", nome);


    return fp;
}

// Retorna a quantidade de registros do tipo SENTENCA foram adicionados ao arquivo ate o momento
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


void inserir(FILE *fp) {
    SENTENCA sent = {0, 0, 0, 0, "---", "---", "---", "---", "---", "---"};
    sent.id = numSentencas(fp) + 1;
    fseek(fp, 0, SEEK_END);

    puts("Insira o tipo da sentenca (1: Verdadeiro/Falso ; 2: Lacuna)");
    do {
        scanf("%hd", &sent.tipo);
        if (sent.tipo<1 || sent.tipo>2)
            puts("Insira um valor valido.");
    } while (sent.tipo < 1 || sent.tipo > 2);

    if (sent.tipo == 1) {
        puts("Insira a sentenca VERDADEIRA: ");
        getchar();
        fgets(sent.verdadeira, 150, stdin);
        removeQuabraLinha(sent.verdadeira, 150);

        puts("Insira a sentenca FALSA: ");
        getchar();
        fgets(sent.falsa, 150, stdin);
        removeQuabraLinha(sent.falsa, 150);
    } else {
        puts("Insira a sentenca com a lacuna: ");
        getchar();
        fgets(sent.lacuna, 150, stdin);
        removeQuabraLinha(sent.lacuna, 150);

        puts("Insira a resposta da lacuna: ");
        getchar();
        fgets(sent.resposta, 25, stdin);
        removeQuabraLinha(sent.resposta, 25);
    }

    puts("Insira a dificuldade (1: Facil ; 2: Intermediaria ; 3: Dificil)");
    do {
        scanf("%hd", &sent.dificuldade);
        if (sent.dificuldade<1 || sent.dificuldade>3)
            puts("Insira um valor valido.");
    } while (sent.dificuldade < 1 || sent.dificuldade > 3);

    puts("Insira o peso (1 ~ 3)");
    do {
        scanf("%hd", &sent.peso);
        if (sent.peso<1 || sent.peso>3)
            puts("Insira um valor valido.");
    } while (sent.peso < 1 || sent.peso > 3);

    puts("Insira o assunto principal:");
    getchar();
    fgets(sent.assuntoPrincipal, 10, stdin);
    removeQuabraLinha(sent.assuntoPrincipal, 10);

    puts("Insira o assunto secundario:");
    fgets(sent.assuntoSecundario, 10, stdin);
    removeQuabraLinha(sent.assuntoSecundario, 10);

    fwrite(&sent, sizeof(SENTENCA), 1, fp);
}

void listar(FILE *fp) {
    fseek(fp, 0, SEEK_SET);
    SENTENCA sent;
    int lidos;
    puts("");
    printf("ID    TIPO    DIFIC    PESO    A. PRINCIPAL       A. SECUNDARIO             SENTENCA\n");
    while ((lidos = fread(&sent, sizeof(SENTENCA), 1, fp)) > 0) {
        printf("%2hd      %hd        %hd      %hd      %-10s          %-10s       %s", sent.id, sent.tipo, sent.dificuldade, sent.peso, sent.assuntoPrincipal, sent.assuntoSecundario, sent.verdadeira);
        puts("");
        puts("");
    }

}

void excluir(FILE *fp) {
    unsigned short id;
    int totalRegs = numSentencas(fp)+1;

    puts("Insira o ID da sentenca a ser excluida: ");
    printf("Resposta: ");

    scanf("%hd", &id);
    if (id>totalRegs || id<1) {
        puts("ID invalido, tente novamente.");
        return;
    }

    SENTENCA sentVazia = {id, 0, 0, 0, "---", "---", "---", "---", "---", "---"};
    fseek(fp, sizeof(SENTENCA)*(id-1), SEEK_SET);
    int val = fwrite(&sentVazia, sizeof(SENTENCA), 1, fp);

    if (val == 1) {
        printf("Sentenca %hd excluida com sucesso!\n", id);
    }

}

void alterar(FILE* fp) {
    unsigned short id;
    SENTENCA sent = {0, 0, 0, 0, "---", "---", "---", "---", "---", "---"};

    puts("Insira o ID da sentenca a ser alterada: ");
    scanf("%hd", &id);
    if (id<1 || id>(numSentencas(fp) + 1)) {
        puts("ID invalida.");
        return;
    }

    fseek(fp, sizeof(SENTENCA)*(id-1), SEEK_SET);

    sent.id = id;
    puts("Insira o tipo da sentenca (1: Verdadeiro/Falso ; 2: Lacuna)");
    do {
        scanf("%hd", &sent.tipo);
        if (sent.tipo<1 || sent.tipo>2)
            puts("Insira um valor valido.");
    } while (sent.tipo < 1 || sent.tipo > 2);

    if (sent.tipo == 1) {
        puts("Insira a sentenca VERDADEIRA: ");
        getchar();
        fgets(sent.verdadeira, 150, stdin);
        removeQuabraLinha(sent.verdadeira, 150);

        puts("Insira a sentenca FALSA: ");
        getchar();
        fgets(sent.falsa, 150, stdin);
        removeQuabraLinha(sent.falsa, 150);
    } else {
        puts("Insira a sentenca com a lacuna: ");
        getchar();
        fgets(sent.lacuna, 150, stdin);
        removeQuabraLinha(sent.lacuna, 150);

        puts("Insira a resposta da lacuna: ");
        getchar();
        fgets(sent.resposta, 25, stdin);
        removeQuabraLinha(sent.resposta, 25);
    }

    puts("Insira a dificuldade (1: Facil ; 2: Intermediaria ; 3: Dificil)");
    do {
        scanf("%hd", &sent.dificuldade);
        if (sent.dificuldade<1 || sent.dificuldade>3)
            puts("Insira um valor valido.");
    } while (sent.dificuldade < 1 || sent.dificuldade > 3);

    puts("Insira o peso (1 ~ 3)");
    do {
        scanf("%hd", &sent.peso);
        if (sent.peso<1 || sent.peso>3)
            puts("Insira um valor valido.");
    } while (sent.peso < 1 || sent.peso > 3);

    puts("Insira o assunto principal:");
    getchar();
    fgets(sent.assuntoPrincipal, 10, stdin);
    removeQuabraLinha(sent.assuntoPrincipal, 10);

    puts("Insira o assunto secundario:");
    fgets(sent.assuntoSecundario, 10, stdin);
    removeQuabraLinha(sent.assuntoSecundario, 10);

    fwrite(&sent, sizeof(SENTENCA), 1, fp);


}

int main() {
    int resp;
    
    FILE *fp = novoArquivo();
    printf("\n\n%d registros\n", numSentencas(fp));
    do {
        puts("");
        puts("*** INSERSOR DE SENTENCAS ***");
        puts("1. Adicionar nova sentenca.");
        puts("2. Excluir sentenca.");
        puts("3. Alterar sentenca.");
        puts("4. Listar as sentencas do arquivo.");
        puts("5. Sair");
        printf("Resposta: ");
        scanf("%d", &resp);
        
        switch (resp) {
        case 1:
            inserir(fp);
            break;
        case 2: 
            excluir(fp);
            break;  
        case 3:
            alterar(fp);
            break;
        case 4:
            listar(fp);
            break;          
        case 5:
            puts("Fechando o programa.");
            break;
        default:
            puts("Insira uma opcao valida.");
            break;
        }

    } while (resp != 5);


    fclose(fp);
}