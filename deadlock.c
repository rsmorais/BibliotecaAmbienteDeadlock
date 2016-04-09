#include "deadlock.h"
int NuProcess = 15;
int NuServ = 10;
int randomic = 1;
int dormir = 0;
int valueProcess = 1;
int vet_aux[165];
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
			if((*var_info).MR[thread_info[0]-1][j] > 0)
				count++;
		
		if(randomic == 1 && count == 0)
			for(i=0; i < NuServ; i++)
			{
					k = (rand()%2);
					if(thread_info[i+1] == 1 && k == 1)
						(*var_info).MR[thread_info[0]-1][i] += 1;			
			}
			(*var_info).MR[thread_info[0]-1][NuServ] = 1;
		//printMatrizRequisicao();
		pthread_mutex_unlock( var_coltrol.mutex );
		pthread_barrier_wait( var_coltrol.barrier );
		pthread_join(thread[thread_info[0]-1], NULL);
		sleep(dormir);
		a--;
	}
    return NULL;
}

void deadlock_pre_init(int *vet)
{
	NuProcess = vet[0];
	NuServ = vet[1];
	randomic = vet[2];
	dormir = vet[3];
}

int deadlock_init(deadlock_mutex_t *mutex, deadlock_barrier_t *barrier, deadlock_t *matriz_deadlock){
	int i, j;
	
	pthread_barrier_init(&barrier1, NULL, NuProcess);
	var_coltrol.mutex = mutex;
	var_coltrol.barrier = barrier;
	var_info = matriz_deadlock;
	deadlock_init_var();
	if(valueProcess != 1){
		for(i = 1; i <= NuProcess; i++){
			var_coltrol.vet[i-1] = i;
			for(j = 1; j <= NuServ; j++){
				scanf("%d", &var_coltrol.vet[j]);
				printf("%d", var_coltrol.vet[j]);
			}
			printf("\n");
		}
	}else{
		j=1;
		for(i = 0 ; i < (NuProcess*(NuServ+1)); i++)
		{
			if(i%(NuServ+1) == 0){
				printf("\n");
				var_coltrol.vet[i] = j;
				j++;
			}
			else
				var_coltrol.vet[i] = 1;
			printf("%d", var_coltrol.vet[i]);
			
			
		}
		
	}
	for(i = 0; i < NuProcess; i++){
		pthread_create( &thread[i], NULL, recurso, (void*) &var_coltrol.vet[i*(NuServ+1)]);
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
			(*var_info).MR[i][j] = 0;
			(*var_info).MA[i][j] = 0;
		}
}

//Função que imprime a matris de requisição "somente pra teste"
void printMatrizRequisicao()
{
	int i, j, k, l, m;
	printf("E = [");
	for(l = 0; l < NuServ; l++)
	{
		printf("%d ",(*var_info).SE[l]);
	}
	printf("]  A = [ ");
	for(m = 0; m < NuServ; m++)
	{
		printf("%d ",(*var_info).SD[m]);
	}
	printf("]\n\n");
	printf("req           aloc\n");
	for(i=0; i < NuProcess; i++)
	{
		for(j=0; j < NuServ+1; j++)
			printf("%d ", (*var_info).MR[i][j]);
		printf("  ");
		for(k=0; k < NuServ; k++)
			printf("%d ", (*var_info).MA[i][k]);
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
