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

void escalonador();

int main()
{
	char StrEntrada;
	int i, j;
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
	escalonador();

	return 0;
}

void escalonador()
{
	int a = 1;
	while(a<10)
	{			
		deadlock_barrier_wait(&barrier);
		pthread_mutex_lock( var_coltrol.mutex );
			
		pthread_mutex_unlock( var_coltrol.mutex );
		printf("VALOR DE a: %d\n", a);
		a++;
	}
	
}
