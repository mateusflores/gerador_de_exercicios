#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

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

// A funcao gerar_prova recebe os ponteiros dos arquivos prova e gabarito,
// Seguidos pelo numero de sentencas que serao inseridas,
// Seguidas pela struct SENTENCA que ira conter a sentenca a ser inserida,
// E uma booleana para o caso de sentenca verdadeira/falsa, para verificar
// quais das duas que serao inseridas na prova.
// Apos receber todos esses parametros, a funcao escreve a sentenca no
// arquivo prova, e escreve a resposta correta no arquivo gabarito


void gerar_sentenca(FILE * fp1, FILE * fp2, int num_sentencas,SENTENCA * texto, bool questao){
    if(num_sentencas <=0){
        return;
    } else{
       if(texto->tipo == 1 && questao == true){
         fprintf(fp1,"%s\n",texto->verdadeira);
         fprintf(fp2,"%s\n",texto->verdadeira);

       } else if(texto->tipo == 1 && questao == false){
         fprintf(fp1,"%s\n",texto->falsa);
         fprintf(fp2,"%s\n",texto->falsa);
       } else if(texto->tipo == 2){
         fprintf(fp1,"%s\n",texto->lacuna);
         fprintf(fp2,"%s\n",texto->resposta);
       }
       gerar_sentenca(fp1,fp2,num_sentencas-1,texto,0);


    }
}



int gerar_questao(char prova[], char gabarito[],int tipo,int indice){
    SENTENCA questao;
    bool falso = false;
    indice++;
    FILE * fp1 = fopen(prova,"a");
    FILE * fp2 = fopen(gabarito,"a");
    if(tipo == 2){
        fprintf(fp1,"%d-Preencha os espaços em cada uma das sentenças:\n",indice);
        fprintf(fp2,"%d\n",indice);
        gerar_sentenca(fp1,fp2,2,&questao,0);

    }
    else if(tipo == 1){
        fprintf(fp1,"%d-Indique se as seguintes sentenças são falsas ou verdadeiras:\n",indice);
        fprintf(fp2,"%d\n",indice);
        gerar_sentenca(fp1,fp2,2,&questao,falso);
    }



    fclose(fp1);
    fclose(fp2);
    return indice;



}

int main(){
    int n = criar_prova();
    char prova[20];
    char gabarito[20];
    sprintf(prova,"prova%d.bin",n);
    sprintf(gabarito,"gabarito%d.bin",n);
    gerar_indice(prova,gabarito,1,0);
   
}