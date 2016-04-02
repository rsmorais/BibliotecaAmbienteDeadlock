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
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;


int main(int argc, char **argv)
{
	char StrEntrada;
	int NuProcessos, NuServicos, i, j;
	pthread_t thread[10];
	int thread_info[60];
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


void *recurso(void *ptr)
{
     int *thread_id;
     int i;
     thread_id = (int *) ptr;
	pthread_mutex_lock( &mutex1 );
	for(i = 0; i < 2; i++) {
	     printf("oi %d \n", thread_id[0]);
	     sleep(1);
     }
	pthread_mutex_unlock( &mutex1 );
     return NULL;
}
