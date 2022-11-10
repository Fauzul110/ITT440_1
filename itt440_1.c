#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>
#include<signal.h>
#include<string.h>

int main(void){

	void sigint_handler(int sig);

	char s[200];
	int c;
	int pipefds[2];

	printf("\nHow much money do u want?\n");
	scanf("%d\n",&c);

	if(signal(SIGINT,sigint_handler)==SIG_ERR)
	{
		perror("Signal");
		exit(1);
	}


	if(pipe(pipefds) == -1)
	{
		perror("ERROR");
		exit(EXIT_FAILURE);
	}

	printf("Giving the money to child...\n");
	write(pipefds[1], &c, sizeof(c));
	printf("Done.\n\n");

	printf("Child receiving money from parent...\n");
	read(pipefds[0],&c, sizeof(c));
	printf("Done.\n\n");

	printf("Money received : %d\n ",c);

	//fork looping
	for(int i=0; i<("%d",c); i++)
	{
		pid_t pid = fork();

		if(pid==0)
		{
			printf("Child received %d from parent\n",c);
			exit(0);
		}
		else
		{
			printf("Waiting for process to finish...\n");
			close(pipefds[1]);
			close(pipefds[0]);
			printf("Process finished.\n");
		}

	}
}
void sigint_handler(int sig)
{
	printf("Dah2 Ler Tu");
}
