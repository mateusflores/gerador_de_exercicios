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
    char assuntoPrincipal[25];
    char assuntoSecundario[25];
    char lacuna[500];
    char resposta[25];
    char verdadeira[500];
    char falsa[500]; 
} SENTENCA;

typedef struct {
    unsigned short quantLacunas;
    unsigned short quantVF;
    char assuntos[30][30];
    int numAssuntos;
    int dificuldades[3];
    int numDific;
} ESPECIFICACAO_PROVA;

int geraDuasOpcoes () {
    srand(time(NULL));
    int r = rand() % 2;
    if (r == 0) 
        return 0; // Enunciado pede a alternativa FALSA
    else
        return 1; // Enunciado pede a alternativa CORRETA
}

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

// Gera a quantidade de sentenças que cada questão terá
int quantidadeSentencas (int tipo) {
    srand(time(NULL));
    int randomNum;
    int quantVF[6] = {3, 4, 5, 5, 5, 6};
    int quantSentenca[6] = {3, 4, 5, 6, 7, 8};

    if (tipo == VF) {
        randomNum = rand() % 6;
        return quantVF[randomNum];
    } else {
        randomNum = rand() % 6;
        return quantSentenca[randomNum];
    }
}

// Sorteia qual das sentenças vai ser a correta
int respostaCorreta (int sentencas) {
    srand(time(NULL));
    int r  = rand() % sentencas + 1;
    return r ;
}

SENTENCA geraSentencaAleatoria(SENTENCA sentencas[], unsigned short tipo) {
    SENTENCA sentAleatoria;
    ESPECIFICACAO_PROVA espec;
    FILE *fp = fopen("especificacao_questoes.bin", "rb");
    if (fp == NULL) {
        puts("Erro!");
        exit(10);
    }
    rewind(fp);
    fread(&espec, sizeof(ESPECIFICACAO_PROVA), 1, fp);

    FILE *sentencasElegiveis = fopen("sentencas_elegiveis.bin", "wb+");
    if (sentencasElegiveis == NULL) {
        puts("ERRO!");
        exit(11);
    }

    bool tipoConfere, assuntosConfere, dificuldadeConfere;
    int n = 0, quantQuestoesElegiveis = 0;

    do {
        if (sentencas[n].tipo == tipo) {
            tipoConfere = true;}
        else {    
            tipoConfere = false;
        }

        for (int i=0; i<espec.numAssuntos; i++) {
            if ((espec.assuntos[i] == sentencas[n].assuntoPrincipal) || (espec.assuntos[i] == sentencas[n].assuntoSecundario))
                assuntosConfere = true;
            else
                assuntosConfere = false;
        }

        for (int i=0; i<espec.numDific; i++) {
            if (espec.dificuldades[i] == sentencas[n].dificuldade)
                dificuldadeConfere = true;
            else    
                dificuldadeConfere = false;
        }

        if (tipoConfere && assuntosConfere && dificuldadeConfere){
            quantQuestoesElegiveis++;
            fwrite(&sentencas[n], sizeof(SENTENCA), 1, sentencasElegiveis);
        }
    } while(n<(sizeof(*sentencas)/sizeof(SENTENCA)));

    srand(time(NULL));
    int sentencaSorteada = rand() % quantQuestoesElegiveis;
    fseek(sentencasElegiveis, sizeof(SENTENCA)*(sentencaSorteada), SEEK_SET);
    fread(&sentAleatoria, sizeof(SENTENCA), 1, sentencasElegiveis);

    fclose(sentencasElegiveis);
    fclose(fp);
    return sentAleatoria;
}

// funcao verifica se o arquivo ja existe. Se sim, retorna True, se nao False
bool arquivo_existente(char * arquivo){

 FILE * arq = fopen(arquivo,"r");
 if(arq == NULL){
    return false;
 }
 else{
    fclose(arq);
    return true;
 }
}

// Funcao cria os arquivos prova.txt e gabarito.txt e retorna o numero
// qual o numero dessa prova e desse gabarito
int criar_prova(){
   char prova[20] = "prova1.txt";
   char gabarito[20] = "gabarito1.txt";
   int i = 1;
   bool criado_com_sucesso = false;
    
    while(criado_com_sucesso == false){
           
     criado_com_sucesso = arquivo_existente(prova);

     if(criado_com_sucesso == true){
        sprintf(prova,"prova%d.txt",i);
        sprintf(gabarito,"gabarito%d.txt",i);
        criado_com_sucesso = false;
        i++;

     }else if(criado_com_sucesso == false){
         sprintf(prova,"prova%d.txt",i);
         sprintf(gabarito,"gabarito%d.txt",i);
         criado_com_sucesso = true;
     }

      }
      FILE * fp1 = fopen(prova,"a");
      FILE * fp2 = fopen(gabarito,"a");
      fclose(fp1);
      fclose(fp2);

    return i;
}

void gerar_sentenca(FILE * fp1, FILE * fp2, int num_sentencas, SENTENCA *questao, bool true_false){
    if(num_sentencas <=0){
        return;
    } else{
       if(questao->tipo == 1 && true_false == true){
         fprintf(fp1,"%s\n",questao->verdadeira);
         fprintf(fp2,"%s\n",questao->verdadeira);

       } else if(questao->tipo == 1 && true_false == false){
         fprintf(fp1,"%s\n",questao->falsa);
         fprintf(fp2,"%s\n",questao->falsa);
       } else if(questao->tipo == 2){
         fprintf(fp1,"%s\n",questao->lacuna);
         fprintf(fp2,"%s\n",questao->resposta);
       }
       gerar_sentenca(fp1,fp2,num_sentencas-1,questao,0);
    }
}

void gerar_questao(char prova[], char gabarito[],int tipo,int indice, SENTENCA questao) {
    bool falso = false;
    indice++;
    FILE * fp1 = fopen(prova,"a");
    FILE * fp2 = fopen(gabarito,"a");
    if(tipo == LAC){
        fprintf(fp1,"%d-Preencha os espaços em cada uma das sentenças:\n",indice);
        fprintf(fp2,"%d\n",indice);
        gerar_sentenca(fp1,fp2, quantidadeSentencas(LAC),&questao, geraDuasOpcoes());

    }
    else if(tipo == VF){
        fprintf(fp1,"%d-Indique se as seguintes sentenças são falsas ou verdadeiras:\n",indice);
        fprintf(fp2,"%d\n",indice);
        gerar_sentenca(fp1,fp2, quantidadeSentencas(VF),&questao, geraDuasOpcoes());
    }
    fclose(fp1);
    fclose(fp2);
    
}

void gerar_prova_gabarito(SENTENCA sentencas[]) {
    int n = criar_prova();
    char prova[20];
    char gabarito[20];
    sprintf(prova,"prova%d.bin",n);
    sprintf(gabarito,"gabarito%d.bin",n);


    SENTENCA sent;
    ESPECIFICACAO_PROVA espec;
    FILE *e = fopen("especificacao_questoes.bin", "rb");
    if (e == NULL){
        puts("Erro!");
        exit(9);
    }
    fread(&espec, sizeof(ESPECIFICACAO_PROVA), 1, e);
    fclose(e); 
    int lacunas = espec.quantLacunas, vf = espec.quantVF;

    do {
        int tipo = geraDuasOpcoes();
        if (tipo == 0){
            tipo = VF;
            vf--;
        }
        else {   
            tipo = LAC;
            lacunas--;
        }

        sent = geraSentencaAleatoria(sentencas, tipo);
        gerar_questao(prova,gabarito, tipo, 0, sent); 
    } while (lacunas!=0 && vf!=0);
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
    gerar_prova_gabarito(sentencas);


    fclose(comp);
    free(sentencas);
    

    // EXCLUIR DEPOIS -> Testando se o arquivo de compilado esta recebendo sentencas
    printf("\n\n%d sentencas\n\n", quantSentencas);
}