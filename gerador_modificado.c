#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAMANHO_SENTENCA 200
#define TIPO_SUBTIPO 100
#define VERDADEIRO_FALSO 1
#define PREENCHER_LACUNAS 2



// finalizado

typedef struct {
 char questoes[TAMANHO_SENTENCA];
 char respostas[TAMANHO_SENTENCA];
 unsigned short int nivel_de_dificuldade;
 unsigned short int peso; // a probabilidade do sorteio eh proporcional ao peso
 // em comparacao as sentencias
 char tipo[TIPO_SUBTIPO];
 char subtipo[TIPO_SUBTIPO];





}INSERIR_SENTENCA;

void insere_verdadeirofalso(INSERIR_SENTENCA * sentenca, FILE * ponteiro){
  
  int i;
  char caractere;
  int tipo_de_questao = 0;
  puts("Informe o tipo de questao : 1 para VERDADEIRO/FALSO e 2 para PREENCHER_LACUNAS :");
  scanf("%hd",&tipo_de_questao);
  puts("Informe o Tipo (apenas letras minusculas e sem espaco) :");
  scanf("%s",sentenca->tipo);
  puts("Informe o subtipo (apenas letras minusculas e sem espaco) :");
  scanf("%s",sentenca->subtipo);
  puts("Informe o Peso (1 a 3) :");
  scanf("%hd",&sentenca->peso);
  puts("Informe o Nivel de dificuldade (1 a 3) :");
  scanf("%hd",&sentenca->nivel_de_dificuldade);
  puts("Informe a sentencia (quando terminar, digite enter) :");
  
  for(i = 0; (caractere = fgetc(stdin)) != '\n'; i++){
        sentenca->questoes[i] = caractere;
  }
  sentenca->questoes[i] = '\0';

  puts("Informe a resposta correta : (digite enter para terminar)");
  for(i = 0; (caractere = fgetc(stdin)) != '\n'; i++){
      sentenca->respostas[i] = caractere;
  }

  if(tipo_de_questao == VERDADEIRO_FALSO){
  fprintf(ponteiro,"\n%d\nNivel de dificuldade : %hd\nTipo : %s\nSubtipo : %s\nPeso : %hd\nSentenca : %s\nRespostas  : %s",VERDADEIRO_FALSO,sentenca->nivel_de_dificuldade,sentenca->tipo,sentenca->subtipo,sentenca->peso,sentenca->questoes);
  }else if(tipo_de_questao == PREENCHER_LACUNAS){

   fprintf(ponteiro,"\n%d\nNivel de dificuldade : %hd\nTipo : %s\nSubtipo : %s\nPeso : %hd\nSentenca : %s\nRespostas  : %s",PREENCHER_LACUNAS,sentenca->nivel_de_dificuldade,sentenca->tipo,sentenca->subtipo,sentenca->peso,sentenca->questoes);


  }
  return;

}


// finalizado

void insere_sentencas_arquivo(FILE * nome_do_programa, int n_sentencas){
    if(n_sentencas <= 0){
        return;
    }
    else{
    int escolha = 0;
    
    INSERIR_SENTENCA * sentenca = (INSERIR_SENTENCA *) malloc(sizeof(INSERIR_SENTENCA));
    insere_verdadeirofalso(sentenca,nome_do_programa);
    free(sentenca);
    return insere_sentencas_arquivo(nome_do_programa,n_sentencas-1);
    
    }

}



int main(int argc, char ** argv){
   
  int n_sentencas;
  char nome_do_arquivo[TAMANHO_SENTENCA];



  puts("Usuario : \n\n Informe o arquivo em que vc deseja inserir as sentencias :");
  scanf("%s",nome_do_arquivo);



  FILE * arquivo = fopen(nome_do_arquivo,"a");
  // se o arquivo existe, escreve no final, caso nao, cria o arquivo



  puts("Informe o numero de sentencias :");
  scanf("%d", &n_sentencas);
  insere_sentencas_arquivo(arquivo,n_sentencas);
  fclose(arquivo);

  return 0;

}