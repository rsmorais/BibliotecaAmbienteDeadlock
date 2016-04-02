#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

struct VARS{
int E[4], A[4];
int F[10][4], R[10][4];
};
typedef struct VARS vars;
void *recurso( void *ptr );
void inicializa();
void printMatrizRequisicao();
void *recurso(void *ptr);

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexMatrizes = PTHREAD_MUTEX_INITIALIZER;
int aleatorio = 1;
int NuProcessos = 5;
vars global;

int main(int argc, char **argv)
{
	char StrEntrada;
	int NuServicos, i, j;
	pthread_t thread[10];
	int thread_info[60];
	inicializa();
	scanf("%c", &StrEntrada);
	switch (StrEntrada){
		case 'P':
			scanf("%d", &NuProcessos);
			for(i = 1; i <= NuProcessos; i++){
				j = i*5;
				thread_info[j-5] = i;
				scanf("%d%d%d%d", &thread_info[j-4], &thread_info[j-3], &thread_info[j-2], &thread_info[j-1]);
				printf("%d %d %d %d %d\n", thread_info[j-5], thread_info[j-4], thread_info[j-3], thread_info[j-2], thread_info[j-1]);
			}
			break;		
	}
	for(i = 1; i <= NuProcessos; i++){
		j = i*5;
		pthread_create( &thread[i-1], NULL, recurso, (void*) &thread_info[j-5]);
		pthread_join( thread[i-1], NULL);
	}

	return 0;
}

//~ void *escalonador (void *args)
//~ {
	//~ pthread_mutex_lock( &mutexMatrizes );
	//~ for(){
		
	
	
	//~ }	
	//~ pthread_mutex_lock( &mutexMatrizes );
//~ }

//~ void verificaDeadLock ()
//~ {
	
//~ }
//Função que inicializa a variavel de controle de serviços
void inicializa()
{
	int i, j;
	for(i=0; i < 10; i++)
		for(j=0; j < 4; j++)
			global.R[i][j] = 0;
	
}

//Função que imprime a matris de requisição "somente pra teste"
void printMatrizRequisicao()
{
	int i, j;
	for(i=0; i < NuProcessos; i++)
	{
		for(j=0; j < 4; j++)
			printf("%d ", global.R[i][j]);
		printf("\n");	
	}
	printf("\n");
}

//Função que será executada pelos processos(threads)
void *recurso(void *ptr)
{
	while(1==1){
		int *thread_info;
		int i,j;
		thread_info = (int *) ptr;
		pthread_mutex_lock( &mutexMatrizes );
		printf("processo %d: esta requisitando serviços.\n", thread_info[0]);
		if(aleatorio == 1)
			for(i=1; i < 5; i++)
			{
				j = (rand()%2);
				if(thread_info[i] == 1 && j == 1)
					global.R[thread_info[0]-1][i-1] += 1;
				printf("%d\n", j);
			}		
		printMatrizRequisicao();
		pthread_mutex_unlock( &mutexMatrizes );
		sleep(1);
		return NULL;
	}
    
}
