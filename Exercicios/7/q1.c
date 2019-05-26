#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>//PARA wait

int main()
{
	int filho;	// PID do processo filho
	int fd[2];	// Descritores do pipe
	int i=0, mensagem[10] = {1,2,3,4,5,6,7,8,9,10};
	// Cria o pipe
	pipe(fd);
	// Cria o processo
	filho = fork();
	// Codigo do filho
	if(filho == 0)
	{
		printf("Filho vai ler o pipe\n");
		if(read(fd[0], mensagem,sizeof(mensagem)) < 0) 
			printf("Erro na leitura do pipe\n");
		else
			for(i=0;i<10;i++){
				printf("Filho leu: %d\n", mensagem[i]);
				sleep(1);
			}
	}
	// Codigo do pai
	else
	{
		printf("Pai vai escrever no pipe\n");
		if (write(fd[1], mensagem, sizeof(mensagem)) < 0)
			printf("Erro na escrita do pipe\n");
		printf("Pai terminou de escrever no pipe\n");
		wait(NULL);
	}
	return 0;
}