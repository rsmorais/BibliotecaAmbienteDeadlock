#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "deadlock.h"


pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexMatrizes = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barrier;
deadlock_mutex_t mutex;
deadlock_barrier_t barrier;
deadlock_t matriz_deadlock;
int aleatorio = 1;
int NuProcessos = 5;
int NuServicos = 4;

void teste();

int main()
{
	char StrEntrada;
	int i, j;
	//pthread_t escalonador;
	int thread_info[60];
	pthread_barrier_init(&barrier, NULL, NuProcessos+1);
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
	deadlock_init(&mutex, &barrier, &matriz_deadlock, thread_info);
	teste();

	return 0;
}

//Função que inicializa a variavel de controle de serviços



//~ void *escalonador (void *ptr)
//~ {
	//~ int a = 20, i, j, count;
	//~ while(1!=a){
		//~ pthread_barrier_wait(&barrier);
		//~ pthread_mutex_lock( &mutexMatrizes );
			//~ for(i = 1; i <= NuProcessos; i++)
			//~ {
				//~ count=0;
				//~ for(j = 1; j <= NuServicos; j++)
				//~ {
					//~ if(global.A[j]-global.R[i][j] >= 0)
						//~ count++;
				//~ }
				//~ if(count == 4)
					//~ servirProcesso(i);
			//~ }
			//~ 
		//~ pthread_barrier_wait(&barrier);
		//~ printMatrizRequisicao();
	//~ }
	//~ return NULL;
//~ }

//~ void servirProcesso(int arg)
//~ {
	//~ int j;
	//~ for(j = 1; j <= NuServicos; j++)
	//~ {
		//~ global.F[arg][j] += global.R[arg][j];
	//~ }
//~ }

void teste()
{
	while(1==1)
	{	pthread_mutex_unlock( &mutex );
		pthread_barrier_wait(&barrier);
		printf("teste\n");
	}
	
}
