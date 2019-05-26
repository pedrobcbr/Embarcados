#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>//para fork
#include <string.h>
#include <sys/wait.h>

int main()
{
	int pid;
	int fd[2];
	int filapai=0,fila=0;
	// Cria o pipe
	pipe(fd);
	// Cria o processo
	pid = fork();
	// Codigo do filho
	if(fila==0)	
	{
		if(pid == 0)
		{
			char buffer_filho[100], msg_filho[100] = "FILHO: Pai, qual � a verdadeira ess�ncia da sabedoria?";
			if (write(fd[1], msg_filho, sizeof(msg_filho)) < 0)
				printf("Erro na escrita\n");
			if(read(fd[0], buffer_filho, 100) < 0) 
				printf("Erro na leitura do pipe\n");
			else
				printf("%s\n", buffer_filho);
			
			
			
		}
		else
		{
			char buffer_pai[100], msg_pai[100] = "PAI: N�o fa�ais nada violento, praticai somente aquilo que � justo e equilibrado.";
			sleep(1);
			if (write(fd[1], msg_pai, sizeof(msg_pai)) < 0)
				printf("Erro na escrita do pipe\n");
			wait(NULL);
			if(read(fd[0], buffer_pai, 100) < 0) 
				printf("Erro na leitura do pipe\n");
			else
				printf("%s\n", buffer_pai);

	    }
    }
    fila++;
    if(fila==1)	
	{
		if(pid == 0)
		{   sleep(1);
			char buffer_filho[100], msg_filho[100] = "FILHO: Mas at� uma crian�a de tr�s anos sabe disso!";
			if (write(fd[1], msg_filho, sizeof(msg_filho)) < 0)
				printf("Erro na escrita\n");
			if(read(fd[0], buffer_filho, 100) < 0) 
				printf("Erro na leitura do pipe\n");
			else
				printf("%s\n", buffer_filho);
			
			
			
		}
		else
		{
			char buffer_pai[100], msg_pai[100] = "PAI: Sim, mas � uma coisa dif�cil de ser praticada at� mesmo por um velho como eu...";
			sleep(1);
			if (write(fd[1], msg_pai, sizeof(msg_pai)) < 0)
				printf("Erro na escrita do pipe\n");
			wait(NULL);
			if(read(fd[0], buffer_pai, 100) < 0) 
				printf("Erro na leitura do pipe\n");
			else
				printf("%s\n", buffer_pai);

	    }
    }
		
	
	return 0;
}
