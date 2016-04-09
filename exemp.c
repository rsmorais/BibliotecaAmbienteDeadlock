#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "deadlock.h"


pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexMatrizes = PTHREAD_MUTEX_INITIALIZER;
deadlock_mutex_t mutex;
deadlock_barrier_t barrier;
deadlock_t matriz_deadlock;
int aleatorio = 1;
int NuProcessos = 5;
int NuServicos = 4;
deadlock_info_t var_coltrol;

void escalonador();
void servir(int i);

int main()
{
	char StrEntrada;
	int i, j, k, aux;
	int thread_info[60];
	deadlock_barrier_init(&barrier, NuProcessos+1);
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
	for(k = 0; k < 4; k++)
	{
		aux = rand()%10;
		matriz_deadlock.E[k]=aux;
		matriz_deadlock.A[k]=aux;
	}
	
	deadlock_init(&mutex, &barrier, &matriz_deadlock, thread_info);
	escalonador();

	return 0;
}

void escalonador()
{
	int a = 1, i, j, count;
	while(a<10)
	{			
		deadlock_barrier_wait(&barrier);
		deadlock_mutex_lock( var_coltrol.mutex );
			
			for(i = 0; i < NuProcessos; i++)
			{	count=0;
				for(j = 0; j < NuServicos; j++)
				{
					if(matriz_deadlock.A[j] >= matriz_deadlock.R[i][j])
						count++;
				}
				if(count == NuServicos)
					servir(i);
			}
			printMatrizRequisicao();
		deadlock_mutex_unlock( var_coltrol.mutex );
		printf("VALOR DE a: %d\n", a);
		a++;
	}
	
}

void servir(int i)
{
	int j;
	for(j = 0; j < NuServicos; j++)
	{
		matriz_deadlock.F[i][j] += matriz_deadlock.R[i][j];
		matriz_deadlock.A[j] -= matriz_deadlock.R[i][j];
		matriz_deadlock.R[i][j] = 0;
	}	
}

void verificaDeadlock()
{
}
