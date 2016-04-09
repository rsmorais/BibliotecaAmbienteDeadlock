#include "deadlock.h"
int NuProcess = 5;
int NuServ = 4;
int randomic = 1;
int dormir = 0;
//Função que será executada pelos processos(threads)
void *recurso(void *ptr)
{
	pthread_barrier_wait( &barrier1 );
	int a = 10;
	while(1!=a){
		int *thread_info;
		int i, j, k, count;
		thread_info = (int *) ptr;
		pthread_mutex_lock( var_coltrol.mutex );
		//printf("processo %d: esta requisitando serviços.\n", thread_info[0]);
		count = 0;
		for(j = 0; j < NuServ; j++)
			if((*var_info).R[thread_info[0]-1][j] > 0)
				count++;
		
		if(randomic == 1 && count <= 0)
			for(i=0; i < NuServ; i++)
			{
					k = (rand()%2);
					if(thread_info[i+1] == 1 && k == 1)
						(*var_info).R[thread_info[0]-1][i] += 1;			
			}		
		//printMatrizRequisicao();
		pthread_mutex_unlock( var_coltrol.mutex );
		pthread_barrier_wait( var_coltrol.barrier );
		pthread_join(thread[thread_info[0]-1], NULL);
		//sleep(1);
		a--;
	}
    return NULL;
}

void deadlock_pre_init()
{
	
}

int deadlock_init(deadlock_mutex_t *mutex, deadlock_barrier_t *barrier, deadlock_t *matriz_deadlock, int *vet){
	int i, j;
	pthread_barrier_init(&barrier1, NULL, NuProcess);
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
		{
			(*var_info).R[i][j] = 0;
			(*var_info).F[i][j] = 0;
		}
}

//Função que imprime a matris de requisição "somente pra teste"
void printMatrizRequisicao()
{
	int i, j, k, l, m;
	printf("E = [");
	for(l = 0; l < 4; l++)
	{
		printf("%d ",(*var_info).E[l]);
	}
	printf("]  A = [ ");
	for(m = 0; m < 4; m++)
	{
		printf("%d ",(*var_info).A[m]);
	}
	printf("]\n\n");
	printf("req           aloc\n");
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
void deadlock_exit()
{
}

int deadlock_barrier_wait(deadlock_barrier_t *barrier)
{
	return pthread_barrier_wait(barrier);
}

int deadlock_mutex_lock(deadlock_mutex_t *mutex)
{
	return pthread_mutex_lock( mutex );
}

int deadlock_mutex_unlock(deadlock_mutex_t *mutex)
{
	return pthread_mutex_unlock( mutex );
}
int deadlock_barrier_init(deadlock_barrier_t *barrier, int i)
{
	return pthread_barrier_init(barrier, NULL, i);
}
