#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define VERDADEIRO_FALSO 1
#define PREENCHER_LACUNAS 2

typedef struct
{
  int tipo;
  unsigned short int dificuldade;
  char assuntoPrincipal[20];
  char assuntoSecundario[200];
  unsigned short int peso;
  char frase[1000];
  char resposta[100]; // a probabilidade do sorteio eh proporcional ao peso
  // em comparacao as sentencas
} INSERIR_SENTENCA;

void inserindo_sentencas(FILE * ponteiro)
{
  INSERIR_SENTENCA *sentenca = (INSERIR_SENTENCA *)malloc(sizeof(INSERIR_SENTENCA));
  bool ha_sentenca = false;
  sentenca->dificuldade = 0;
  puts("+--------------------------------------------------------------------------------+");
  puts("|Informe o tipo de questao : 1 para VERDADEIRO/FALSO e 2 para PREENCHER_LACUNAS :|");
  printf(" Resposta :");
  scanf("%d",&sentenca->tipo);
  setbuf(stdin, NULL);
  puts("|Informe o Nivel de dificuldade (1 - 3) :                                        |");
  printf(" Resposta :");
  scanf("%hd", &sentenca->dificuldade);
  setbuf(stdin, NULL);
  puts("|Informe o Assunto principal :                                                   |");
  printf(" Resposta :");
  scanf("%[^\n]", sentenca->tipo);
  setbuf(stdin, NULL);
  puts("|Informe o Assunto secundario :                                                  |");
  printf(" Resposta :");
  scanf("%[^\n]", sentenca->assuntoSecundario);
  setbuf(stdin, NULL);
  puts("|Informe o Peso (1 - 3) :                                                        |");
  printf(" Resposta :");
  scanf("%hd", &sentenca->peso);
  setbuf(stdin,NULL);
  

  if (sentenca->tipo == VERDADEIRO_FALSO) {
    
    puts("|Informe a sentencia correta :                                                   |");
    printf(" Resposta :");
    scanf("%[^\n]", sentenca->frase);
    setbuf(stdin, NULL);
    puts("|Insera a sentencia falsa :                                                      |");
    printf(" Resposta :");
    scanf("%[^\n]",sentenca->resposta);
    puts("+--------------------------------------------------------------------------------+");
    setbuf(stdin,NULL);
    fwrite(sentenca,sizeof(INSERIR_SENTENCA),1,ponteiro);

  }
  else if (sentenca->tipo== PREENCHER_LACUNAS) {
    puts("|Informe a sentencia :                                                           |");
    printf(" Resposta :");
    scanf("%[^\n]", sentenca->frase);
    setbuf(stdin, NULL);
    puts("|Informe a resposta correta :                                                    |");
    printf(" Resposta :");
    scanf("%[^\n]", sentenca->resposta);
    puts("+--------------------------------------------------------------------------------+");
    setbuf(stdin, NULL);
    fwrite(sentenca,sizeof(INSERIR_SENTENCA),1,ponteiro);
    

  }
  free(sentenca);
  return;
}

int sorteador(int i,char assunto_principal[],int tipo,int anterior){
  bool eh_diferente = false;
  int sorteio;
  srand(time(NULL));
  while(eh_diferente == false){
     sorteio = rand() % i;
    if(sorteio != anterior){
      eh_diferente = true;
    }
  }
  
  FILE * fp1 = fopen("sentencas.bin","rb");
  FILE * fp2 = fopen("prova.txt","a");
  FILE * fp3 = fopen("gabarito.txt","a");
  int contador = 0;
  INSERIR_SENTENCA p;
  while(contador != sorteio){
    fread(&p,sizeof(INSERIR_SENTENCA),1,fp1);
    if(strcmp(assunto_principal,p.assuntoPrincipal) == 0 && p.tipo == tipo)
        contador++;

       if(contador == sorteio){
        fprintf(fp2,"%s",p.frase);
        fputc('\n',fp2);
        fprintf(fp3,"%s",p.resposta);
        fputc('\n',fp3);


      }
  }
  fclose(fp1);
  fclose(fp2);
  fclose(fp3);
  return anterior;

}

int conta_questoes(char assunto_principal[], int tipo){
    FILE * fp = fopen("sentencas.bin","rb");
    int contador = 0;
    INSERIR_SENTENCA p;
    while(fread(&p,sizeof(INSERIR_SENTENCA),1,fp) == 1){

        if(strcmp(assunto_principal,p.assuntoPrincipal) == 0 && p.tipo == tipo)
        contador++;
    }
    fclose(fp);
    return contador;

}

int main(int argc, char **argv)
{
  int n_sentencas = 0;
  FILE * fp = fopen("sentencas.bin","ab");

  while(n_sentencas != 2){
    puts("1 para inserir sentenca\n2 para encerrar");
    scanf("%d", &n_sentencas);
    switch (n_sentencas)
    {
    case 1:
      inserindo_sentencas(fp);
      break;
    
    default:
      break;
    }


  }
 
  

  return 0;
}
