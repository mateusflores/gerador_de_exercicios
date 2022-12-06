#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAMANHO_SENTENCA 1000
#define TIPO_SUBTIPO 100
#define VERDADEIRO_FALSO 1
#define PREENCHER_LACUNAS 2



// finalizado

typedef struct {
 char enunciado[TIPO_SUBTIPO];
 char questoes[TAMANHO_SENTENCA];
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
  scanf("%d",&tipo_de_questao);
  puts("Informe o Tipo (apenas letras minusculas e sem espaco) :");
  scanf("%s",sentenca->tipo);
  puts("Informe o subtipo (apenas letras minusculas e sem espaco) :");
  scanf("%s",sentenca->subtipo);
  puts("Informe o Peso :");
  scanf("%hd",&sentenca->peso);
  puts("Informe o Nivel de dificuldade :");
  scanf("%hd",&sentenca->nivel_de_dificuldade);
  puts("Informe a sentencia (quando terminar, digite '$') :");
  
  for(i = 0; (caractere = fgetc(stdin)) != '$'; i++){
        sentenca->questoes[i] = caractere;
  }
  sentenca->questoes[i] = '\0';
  if(tipo_de_questao == VERDADEIRO_FALSO){
    strcpy(sentenca->enunciado,"Indique se as seguintes sentenças são falsas ou verdadeiras.");
  fprintf(ponteiro,"\n\nTipo : %s\nSubtipo : %s\nPeso: %hd\nNivel de dificuldade : %hd\nquestao : %s\n%s",sentenca->tipo,sentenca->subtipo,sentenca->peso,sentenca->nivel_de_dificuldade,sentenca->enunciado,sentenca->questoes);

  }else if(tipo_de_questao == PREENCHER_LACUNAS){

    strcpy(sentenca->enunciado,"Preencha os espaços em cada uma das sentenças:");
  fprintf(ponteiro,"\n\nTipo : %s\nSubtipo : %s\nPeso: %hd\nNivel de dificuldade : %hd\nquestao : %s\n%s",sentenca->tipo,sentenca->subtipo,sentenca->peso,sentenca->nivel_de_dificuldade,sentenca->enunciado,sentenca->questoes);


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