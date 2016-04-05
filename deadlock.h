#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

struct VARS{
int E[4], A[4];
int F[10][4], R[10][4];
};


struct VARS2{
pthread_mutex_t *mutex;
pthread_barrier_t *barrier;
int *vet;
};

typedef struct VARS deadlock_t;
typedef struct VARS2 deadlock_info_t;
typedef pthread_mutex_t deadlock_mutex_t;
typedef pthread_barrier_t deadlock_barrier_t;

deadlock_info_t var_coltrol;
deadlock_t *var_info;
int NuProcess = 5;
int NuServ = 4;
int randomic = 1;
pthread_t thread[10];
void *recurso(void *ptr);
void deadlock_pre_init();
int deadlock_init(deadlock_mutex_t *mutex, deadlock_barrier_t *barrier, deadlock_t *matriz_deadlock, int *vet);
void deadlock_init_var();
void printMatrizRequisicao();




//Função que será executada pelos processos(threads)
void *recurso(void *ptr)
{
	int a = 20;
	while(1!=a){
		int *thread_info;
		int i,j;
		thread_info = (int *) ptr;
		pthread_mutex_lock( var_coltrol.mutex );
		printf("processo %d: esta requisitando serviços.\n", thread_info[0]);
		if(randomic == 1)
			for(i=1; i < 5; i++)
			{
				j = (rand()%2);
				if(thread_info[i] == 1 && j == 1)
					(*var_info).R[0][1] += 1;
				printf("%d\n", j);
			}		
		printMatrizRequisicao();
		pthread_mutex_unlock( var_coltrol.mutex );
		pthread_barrier_wait( var_coltrol.barrier );
		printf("barreira %d\n",thread_info[0]);
		sleep(1);
		a--;
	}
    return NULL;
}

void deadlock_pre_init()
{
	
}

int deadlock_init(deadlock_mutex_t *mutex, deadlock_barrier_t *barrier, deadlock_t *matriz_deadlock, int *vet){
	int i, j;
	var_coltrol.mutex = mutex;
	var_coltrol.barrier = barrier;
	var_coltrol.vet = vet;
	var_info = matriz_deadlock;
	deadlock_init_var();
	for(i = 1; i <= NuProcess; i++){
		j = i*5;
		pthread_create( &thread[i-1], NULL, recurso, (void*) &var_coltrol.vet[j-5]);
		
	}
	
	return 1;
}

//Função que inicializa a variavel de controle de serviços
void deadlock_init_var()
{
	int i, j;
	for(i=0; i < 10; i++)
		for(j=0; j < 4; j++)
			(*var_info).R[i][j] = 0;
}

//Função que imprime a matris de requisição "somente pra teste"
void printMatrizRequisicao()
{
	int i, j, k;
	for(i=0; i < NuProcess; i++)
	{
		for(j=0; j < 4; j++)
			printf("%d ", (*var_info).R[i][j]);
		printf("  ");
		for(k=0; k < 4; k++)
			printf("%d ", (*var_info).F[i][k]);
		printf("\n");	
	}
	printf("\n");
}
