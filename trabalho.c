#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <wiringPi.h>


pid_t scanner;
#define LedPin 0
#define Rele   2
 


void mataDsreader();
void le_strings(char *matriz_string);
void extraiCodigo(char *str, char *codigo);
int validaCodigo(char *codigos);
int verificaCodigo(char *codigo);
//int getPIDdsreader();

int main(){
  char codigo[10][100];
  char codigoReal[10][100];
  int sent=1;
wiringPiSetup();
pinMode(LedPin,OUTPUT);
pinMode(Rele,OUTPUT);
  signal(SIGALRM, mataDsreader);
  scanner=fork();

  if(scanner==0){
    system("./dsreader > cadastro.txt");
  }else{
    while(sent){
    
    puts("Posicione o código de barras/QR CODE");
    alarm(15);
    pause();
    le_strings(codigo[0]);
    extraiCodigo(codigo[0], codigoReal[0]);
    sent=validaCodigo(codigoReal[0]);
    if(sent){
      puts("Porta fechada");
      digitalWrite(LedPin,LOW);
      digitalWrite(Rele,LOW);
      sleep(5);
     
      exit(1);
}
    }

    if(verificaCodigo(codigoReal[0])){
      puts("Porta fechada");
      digitalWrite(LedPin,LOW);
      digitalWrite(Rele,LOW);
      sleep(5);
    }else{
      puts("Porta aberta");
      digitalWrite(LedPin,HIGH);
      digitalWrite(Rele,HIGH);
	delay(5000);
      digitalWrite(LedPin,LOW);
      delay(15000);
      digitalWrite(Rele,LOW);

    }
  }

  exit(1);
}
// Objetivo: Procedimento para fechar Dsreader quando tempo de execução acabar
// Parâmetro:
// Retorno:
void mataDsreader(){
  //pid_t pidDsreader;

  //system("ps -a | grep dsreader > tmp.txt");
  //pidDsreader=getPIDdsreader();
  //kill(pidDsreader, SIGINT);
  kill(scanner, SIGKILL);
 // waitpid(scanner, NULL, 0);
  //system("rm tmp.txt");
}


// Objetivo: Extrai apenas código da string vinda do arquivo
// Parâmetro: string do arquivo, ponteiro para string do código
// Retorno: código
void extraiCodigo(char *str, char *codigo){
  int linha, i, j;

  for(linha=0; linha<10; linha++){
    for(i=0; *(str + linha*100 + i)!=':' && *(str + linha*100 + i)!='\0'; i++);

    for(i=i+2, j=0; *(str + linha*100 + i)!='(' && *(str + linha*100 + i)!='\0'; i++, j++){
      *(codigo + linha*100 + j)=*(str + linha*100 + i);
    }
    *(codigo + linha*100 + j -1)='\0';
  }


}

// Objetivo: Lê 10 linhas do arquivo
// Parâmetro: ponteiro para strings
// Retorno: strings
void le_strings(char *matriz_string){
  FILE *cadastro;
  int i=0;

  cadastro=fopen("cadastro.txt", "r");

  while(!feof(cadastro) && i<10){
      fgets(matriz_string+100*i, 100, cadastro);
      i++;
  }

  fclose(cadastro);

  return;
}

// Objetivo: Compara 10 códigos para testar se eles são iguais
// Parâmetro: strings dos códigos
// Retorno: 0 quando for igual, 1 se for diferente
int validaCodigo(char *codigos){
  int i;
  int resultado=0;

  for(i=0; i<10; i++){
    if(strcmp(codigos, codigos+i*100)!=0){
      resultado=1;
    }
  }

  return resultado;
}

// Objetivo: Procura um código na base de dados
// Parâmetro: código
// Retorno: 0 para sucesso, 1 quando não encontrar
int verificaCodigo(char *codigo){
  FILE *dados;
  int i=0;
  char aux[100];
  int resultado=1;

  dados=fopen("codigo.txt", "r");

  while(!feof(dados)){
      fgets(aux, 100, dados);
      aux[strlen(aux)-1]='\0';
      if(strcmp(aux, codigo)==0){
        resultado=0;
      }
  }

  fclose(dados);

  return resultado;
}
/*int getPIDdsreader(){
  FILE *arq;
  char pidString[10];
  char aux=' ';
  int i=0;
  pid_t pid;

  arq=fopen("tmp.txt", "r");
  if(arq==NULL){
    fprintf(stderr, "Erro ao abrir tmp.txt");
    exit(-1);
  }
  
  while(aux==' '){
    aux=fgetc(arq);
  }

  
  while(aux!=' ' && !feof(arq)){
    aux=fgetc(arq);
    pidString[i]=aux;
    i++;
  }
  pidString[i-1]=0;

  pid=atoi(pidString);
  fclose(arq);

  return pid;
}
*/
