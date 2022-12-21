#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define VERDADEIRO_FALSO 1
#define PREENCHER_LACUNAS 2

typedef struct
{
  unsigned short int id;
  unsigned short int tipo;
  unsigned short int dificuldade;
  unsigned short int peso;
  char assuntoPrincipal[10];
  char assuntoSecundario[10];
  char lacuna[150];
  char resposta[25];
  char verdadeira[150];
  char falsa[150]; // a probabilidade do sorteio eh proporcional ao peso
  // em comparacao as sentencas
} INSERIR_SENTENCA;

void inserindo_sentencas(FILE * ponteiro)
{
  INSERIR_SENTENCA * sentenca = (INSERIR_SENTENCA *)malloc(sizeof(INSERIR_SENTENCA));
  sentenca->id = 0;
  bool ha_sentenca = false;
  sentenca->dificuldade = 0;
  puts("+--------------------------------------------------------------------------------+");
  puts("|Informe o tipo de questao : 1 para VERDADEIRO/FALSO e 2 para PREENCHER_LACUNAS :|");
  printf(" Resposta :");
  scanf("%hd",&sentenca->tipo);
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
    scanf("%[^\n]", sentenca->verdadeira);
    setbuf(stdin, NULL);
    puts("|Insera a sentencia falsa :                                                      |");
    printf(" Resposta :");
    scanf("%[^\n]",sentenca->falsa);
    puts("+--------------------------------------------------------------------------------+");
    setbuf(stdin,NULL);
    fwrite(sentenca,sizeof(INSERIR_SENTENCA),1,ponteiro);

  }
  else if (sentenca->tipo== PREENCHER_LACUNAS) {
    puts("|Informe a sentencia :                                                           |");
    printf(" Resposta :");
    scanf("%[^\n]", sentenca->lacuna);
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
