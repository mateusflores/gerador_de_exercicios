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
  scanf("%d",&tipo_de_questao);
  setbuf(stdin,NULL);
  puts("Informe o Assunto principal:");
  scanf("%[^\n]",sentenca->tipo);
  setbuf(stdin,NULL);
  puts("Informe o Assunto secundario (apenas letras minusculas e sem espaco) :");
  scanf("%[^\n]",sentenca->subtipo);
  setbuf(stdin,NULL);
  puts("Informe o Peso (1 - 3) :");
  scanf("%hd",&sentenca->peso);
  puts("Informe o Nivel de dificuldade (1 - 3) :");
  scanf("%hd",&sentenca->nivel_de_dificuldade);
  setbuf(stdin,NULL);
  puts("Informe a sentencia (quando terminar, digite '$' e enter) :");
  scanf("%[^\n]",sentenca->questoes);
  setbuf(stdin,NULL);
  puts("Informe a resposta correta : (digite enter para terminar)");
  scanf("%[^\n]",sentenca->respostas);
  setbuf(stdin,NULL);

  if(tipo_de_questao == VERDADEIRO_FALSO){

  fprintf(ponteiro,"\n%d\nNivel de dificuldade : %hd\nAssunto principal : %s\nAssunto secundario : %s\nPeso : %hd\nSentenca : %s\nRespostas : %s",VERDADEIRO_FALSO,sentenca->nivel_de_dificuldade,sentenca->tipo,sentenca->subtipo,sentenca->peso,sentenca->questoes,sentenca->respostas);
  
  }else if(tipo_de_questao == PREENCHER_LACUNAS){

   fprintf(ponteiro,"\n%d\nNivel de dificuldade : %hd\nAssunto principal : %s\nAssunto secundario : %s\nPeso : %hd\nSentenca : %s\nRespostas : %s",PREENCHER_LACUNAS,sentenca->nivel_de_dificuldade,sentenca->tipo,sentenca->subtipo,sentenca->peso,sentenca->questoes,sentenca->respostas);

  }
  return;

}


// finalizado

void insere_sentencas_arquivo(FILE * nome_do_programa, int n_sentencas, char * nome_do_arquivo){
  int n;
    if(n_sentencas <= 0){
      fclose(nome_do_programa);
      return;
    }
    else{
      if(nome_do_programa == NULL){
        puts("Digite o nome do arquivo que vc deseja inserir os dados :");
        scanf("%s",nome_do_arquivo);
        nome_do_programa = fopen(nome_do_arquivo,"a");
      } else{
        printf("O arquivo %s esta sendo usado para escrever, deseja trocar?",nome_do_arquivo);
        puts("Se sim, digite 1, se nao, digite qualquer coisa:");
        scanf("%d",&n);
        if(n == 1){
          puts("Digite o nome do novo arquivo :");
          scanf("%s",nome_do_arquivo);
          fclose(nome_do_programa);
          nome_do_programa = fopen(nome_do_arquivo,"a");
        } 
        
      }
    int escolha = 0;
    
    INSERIR_SENTENCA * sentenca = (INSERIR_SENTENCA *) malloc(sizeof(INSERIR_SENTENCA));
    insere_verdadeirofalso(sentenca,nome_do_programa);
    free(sentenca);
    return insere_sentencas_arquivo(nome_do_programa,n_sentencas-1,nome_do_arquivo);
    
    }

}



int main(int argc, char ** argv){
   
  int n_sentencas;
  char nome_do_arquivo[TAMANHO_SENTENCA];

  puts("Informe o numero de sentencias :");
  scanf("%d", &n_sentencas);
  insere_sentencas_arquivo(NULL,n_sentencas,nome_do_arquivo);

  return 0;

}