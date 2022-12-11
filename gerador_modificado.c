#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define TAMANHO_SENTENCA 200
#define TIPO_SUBTIPO 100
#define VERDADEIRO_FALSO 1
#define PREENCHER_LACUNAS 2

typedef struct
{
  char questoes[TAMANHO_SENTENCA];
  char respostas[TAMANHO_SENTENCA];
  unsigned short int nivel_de_dificuldade;
  unsigned short int peso; // a probabilidade do sorteio eh proporcional ao peso
  // em comparacao as sentencas
  char tipo[TIPO_SUBTIPO];
  char subtipo[TIPO_SUBTIPO];
} INSERIR_SENTENCA;

void inserindo_sentencas(INSERIR_SENTENCA *sentenca, FILE *ponteiro)
{
  bool ha_sentenca = false;
  char caractere;
  fseek(ponteiro,sizeof(char)*0,SEEK_END);
  fseek(ponteiro,sizeof(char)*-1,SEEK_END);
  caractere = fgetc(ponteiro);
  if(caractere >= 33 && caractere <= 126){
      ha_sentenca = true;
  }
  sentenca->nivel_de_dificuldade = 0;
  int tipo_de_questao = 0;
  puts("+--------------------------------------------------------------------------------+");
  puts("|Informe o tipo de questao : 1 para VERDADEIRO/FALSO e 2 para PREENCHER_LACUNAS :|");
  printf(" Resposta :");
  scanf("%d", &tipo_de_questao);
  setbuf(stdin, NULL);
  puts("|Informe o Assunto principal :                                                   |");
  printf(" Resposta :");
  scanf("%[^\n]", sentenca->tipo);
  setbuf(stdin, NULL);
  puts("|Informe o Assunto secundario :                                                  |");
  printf(" Resposta :");
  scanf("%[^\n]", sentenca->subtipo);
  setbuf(stdin, NULL);
  puts("|Informe o Peso (1 - 3) :                                                        |");
  printf(" Resposta :");
  scanf("%hd", &sentenca->peso);
  puts("|Informe o Nivel de dificuldade (1 - 3) :                                        |");
  printf(" Resposta :");
  scanf("%hd", &sentenca->nivel_de_dificuldade);
  setbuf(stdin, NULL);
  

  if (tipo_de_questao == VERDADEIRO_FALSO) {
    char sentenca_falsa[TAMANHO_SENTENCA];
    puts("|Informe a sentencia correta :                                                   |");
    printf(" Resposta :");
    scanf("%[^\n]", sentenca->questoes);
    setbuf(stdin, NULL);
    puts("|Insera a sentencia falsa :                                                      |");
    printf(" Resposta :");
    scanf("%[^\n]",sentenca_falsa);
    puts("+--------------------------------------------------------------------------------+");
    setbuf(stdin,NULL);
    if(ha_sentenca == true)
    fprintf(ponteiro, "\n\n%d\n%hd\n%s\n%s\n%hd\n%s\n%s", VERDADEIRO_FALSO, sentenca->nivel_de_dificuldade, sentenca->tipo, sentenca->subtipo, sentenca->peso, sentenca->questoes, sentenca_falsa);
    else
    fprintf(ponteiro, "%d\n%hd\n%s\n%s\n%hd\n%s\n%s", VERDADEIRO_FALSO, sentenca->nivel_de_dificuldade, sentenca->tipo, sentenca->subtipo, sentenca->peso, sentenca->questoes, sentenca_falsa);

  }
  else if (tipo_de_questao == PREENCHER_LACUNAS) {
    puts("|Informe a sentencia :                                                           |");
    printf(" Resposta :");
    scanf("%[^\n]", sentenca->questoes);
    setbuf(stdin, NULL);
    puts("|Informe a resposta correta :                                                    |");
    printf(" Resposta :");
    scanf("%[^\n]", sentenca->respostas);
    puts("+--------------------------------------------------------------------------------+");
    setbuf(stdin, NULL);
    fprintf(ponteiro, "%d\n%hd\n%s\n%s\n%hd\n%s\n%s", PREENCHER_LACUNAS, sentenca->nivel_de_dificuldade, sentenca->tipo, sentenca->subtipo, sentenca->peso, sentenca->questoes, sentenca->respostas);
  }
  return;
}

void insere_sentencas_arquivo(FILE *nome_do_programa, int n_sentencas)
{
  if (n_sentencas <= 0)
  {
    fclose(nome_do_programa);
    return;
  }
  else
  {
    INSERIR_SENTENCA *sentenca = (INSERIR_SENTENCA *)malloc(sizeof(INSERIR_SENTENCA));
    inserindo_sentencas(sentenca, nome_do_programa);
    free(sentenca);
    return insere_sentencas_arquivo(nome_do_programa, n_sentencas - 1);
  }
}

int main(int argc, char **argv)
{
  int n_sentencas;
  char nome_do_arquivo[TAMANHO_SENTENCA] = "compilado_de_questoes.txt";
  FILE * fp = fopen(nome_do_arquivo,"a+");
  puts("Informe o numero de sentencias a serem inseridas :");
  scanf("%d", &n_sentencas);
  insere_sentencas_arquivo(fp, n_sentencas);

  return 0;
}