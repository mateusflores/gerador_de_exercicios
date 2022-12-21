#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

// Funcao fgets(), mas sem a quebra de linha no final da string
char* newFgets(char frase[], int tam) {
    fgets(frase, tam, stdin);
    for (int i=0; i<tam; i++) {
        if (frase[i] == '\n')
            frase[i] = '\0';
    }
    return frase;
}

void removeQuabraLinha(char frase[], int tam) {
    for (int i=0; i<tam; i++) {
        if (frase[i] == '\n')
            frase[i] = '\0';
    }
}

FILE* novoArquivo() {
    char nome[20];
    puts("CUIDADO! Inserir o nome de um arquivo ja existente vai apagar todo o seu conteudo!!!");
    puts("Insira o nome do arquivo a ser criado (EX: 'exemplo.bin')");
    printf("Resposta: "); 
    getchar();   
    newFgets(nome, 20);

    FILE *fp = fopen(nome, "wb");
    if (fp == NULL) {
        puts("ERRO: Nao foi possivel criar o arquivo.");
        return NULL;
    }
    printf("Arquivo '%s' criado com sucesso!\n\n", nome);
    fclose(fp);

    fp = fopen(nome, "rb+");
    if (fp == NULL) {
        puts("Erro ao abrir o arquivo.");
        exit(4);
    }
    return fp;
}

FILE* abrirArquivo() {
    char nome[20];
    puts("Insira o nome do arquivo a ser aberto (EX: 'exemplo.bin')");
    printf("Resposta: ");  
    getchar();  
    newFgets(nome, 20);

    FILE *fp = fopen(nome, "rb+");
    if (fp == NULL) {
        puts("ERRO: Nao foi possivel abrir o arquivo.");
        return NULL;
    }
    printf("Arquivo '%s' aberto com sucesso!\n\n", nome);

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
        fgets(sent.falsa, 150, stdin);
        removeQuabraLinha(sent.falsa, 150);
    } else {
        puts("Insira a sentenca com a lacuna: ");
        getchar();
        fgets(sent.lacuna, 150, stdin);
        removeQuabraLinha(sent.lacuna, 150);

        puts("Insira a resposta da lacuna: ");
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
        fgets(sent.falsa, 150, stdin);
        removeQuabraLinha(sent.falsa, 150);
    } else {
        puts("Insira a sentenca com a lacuna: ");
        getchar();
        fgets(sent.lacuna, 150, stdin);
        removeQuabraLinha(sent.lacuna, 150);

        puts("Insira a resposta da lacuna: ");
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

    fseek(fp, sizeof(SENTENCA)*(id-1), SEEK_SET);
    fwrite(&sent, sizeof(SENTENCA), 1, fp);


}

int main() {
    int resp;

    FILE *fp;
    
    puts("+------- INSESOR DE SENTENCAS -------+");
    puts("1. Criar novo arquivo de sentencas.");
    puts("2. Abrir arquivo de sentencas ja existente.");
    scanf("%d", &resp);

    do {
        switch (resp) {
            case 1:
                fp = novoArquivo();
                break;
            case 2:
                fp = abrirArquivo();
                break;
            default:
                puts("Insira uma opcao valida.");
                break;
        }
    } while (resp<1 || resp>2);

    // controle do numero de registros já inseridos no arquivo em questão
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
            resp = SAIR;
            puts("Fechando o programa.");
            break;
        default:
            puts("Insira uma opcao valida.");
            break;
        }

    } while (resp != SAIR);


    fclose(fp);
}