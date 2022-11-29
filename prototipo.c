#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define MAX 10000
#define VERDADEIRO_OU_FALSO 1
#define PREENCHER_LACUNAS 2



/*
                            TRABALHO

    Geracao automatica de exercicios a partir de uma base de dados organizada como arquivos-texto
    2 tipos de exercicio - Verdadeiro e falso ou preencha as lacunas
    O programa deve partir de um arquivo que especifica: 

    - Quantas questoes devem ser geradas;
    - Quais os assuntos;
    - Quais os niveis de dificuldade;
    - Quais os tipos de questões;

    O programa cria o arquivo de questoes sorteando aleatoriamente, a partir da base de dados de
    fatos sobre o assunto, questoes que atendam a especificacao.



*/

typedef struct {

 char sentenca[MAX];
 int nivel_de_dificuldade;
 int peso;





}VERDADEIRO_FALSO;

typedef struct{

 char sentenca[MAX];
 int nivel_de_dificuldade;
 int peso; // a probabilidade do sorteio eh proporcional ao peso em comparacao as sentencias




}PREENCHER_ESPACOS;

void insere_verdadeirofalso(VERDADEIRO_FALSO * sentenca, FILE * ponteiro){

  sentenca->nivel_de_dificuldade;
  sentenca->peso;
  sentenca->sentenca;


  fwrite(sentenca,sizeof(sentenca),1,ponteiro);
  return;

}

void insere_preencherlacunas(PREENCHER_ESPACOS * sentenca, FILE * ponteiro){

    sentenca->nivel_de_dificuldade;
    sentenca->peso;
    sentenca->sentenca;
     


  fwrite(sentenca,sizeof(sentenca),1,ponteiro);

  return;

}


void insere_sentencas_arquivo(char * nome_do_programa, int n_sentencas){
    if(n_sentencas == 0){
        return;
    }
    else{
    int escolha = 0;
    puts("Informe qual eh o tipo da sentencia : 1 para VERDADEIRO/FALSO e 2 para PREENCHER COLUNA:");
    scanf("%d", &escolha);
    if(escolha == VERDADEIRO_OU_FALSO)
    {
      
      VERDADEIRO_FALSO * sentenca = (VERDADEIRO_FALSO *) malloc(sizeof(VERDADEIRO_FALSO));
       insere_verdadeirofalso(sentenca,nome_do_programa);
       free(sentenca);
      return insere_sentencas_arquivo(nome_do_programa,n_sentencas-1);
    }
    else if(escolha == PREENCHER_LACUNAS){
      PREENCHER_ESPACOS * sentenca = (PREENCHER_ESPACOS *) malloc(sizeof(PREENCHER_ESPACOS));
       insere_preencherlacunas(sentenca,nome_do_programa);
       free(sentenca);
       return insere_sentencas_arquivo(nome_do_programa,n_sentencas-1);

    }
    }



    
           


}






int main(int argc, char ** argv){
    int n_sentencas;
   char nome_do_arquivo[MAX];
   puts("Usuario : \n\n Informe o arquivo em que vc deseja inserir as sentencias :");
   scanf("%s",nome_do_arquivo);
   FILE * arquivo = fopen(nome_do_arquivo,"ab+"); // se o arquivo existe, escreve no
   puts("Informe o numero de sentencias :"); // final, caso nao, cria o arquivo
   scanf("%d", &n_sentencas);
   insere_sentencas_arquivo(nome_do_arquivo,n_sentencas);

   return 0;






    
}