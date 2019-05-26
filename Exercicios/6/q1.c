#include <stdio.h>
#include <unistd.h>

void main(){
  pid_t fih1;//DECLARANDO O PID DO FILHO 1
  pid_t fih2;//DECLARANDO O PID DO FILHO 2
  pid_t fih3;//DECLARANDO O PID DO FILHO 3

  fih1 = fork();////CRIANDO O 2� PROCESSO-FILHO
  if(fih1 == 0){
    printf("Processo filho A:\npid :%d\nppid:%d\n",getpid(),getppid());
  }

  if(fih1 > 0){
    fih2 = fork();//CRIANDO O 2� PROCESSO-FILHO
    if(fih2 == 0){
      sleep(0.2);
      printf("Processo filho B:\npid :%d\nppid:%d\n",getpid(),getppid());
    }

    if(fih2 > 0){
      fih3= fork();//CRIANDO O 3� PROCESSO-FILHO
      if(fih3 == 0){
        sleep(0.3);
        printf("Processo filho C:\npid :%d\nppid:%d\n",getpid(),getppid());
      }
      else if(fih1 > 0){
      printf("\nProcesso Pai:\npid:%d\nppid :%d\n",getpid(),getppid());
      }
    }
  }
}