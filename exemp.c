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
int NuServicos = 5;
deadlock_info_t var_coltrol;

void escalonador();
void servir(int i);
int verificaServir(int *SD, int *MR);
int verificaDeadlock();

int main()
{
	char StrEntrada;
	int k, aux;
	int vet[4]={NuProcessos,NuServicos,1,1};
	deadlock_barrier_init(&barrier, NuProcessos+1);
	scanf("%c", &StrEntrada);
	
	//Iniciando os vetores de serviços existentes e disponíveis***
	for(k = 0; k < NuServicos; k++)
	{
		aux = rand()%20;
		matriz_deadlock.SE[k]=9;
		matriz_deadlock.SD[k]=9;
	}
	//************************************************************
	
	//Iniciando as variáveis opcionais de deadlock****************
	deadlock_pre_init(vet);
	//************************************************************
	
	
	//Iniciando o ambiente de deadlock****************************
	deadlock_init(&mutex, &barrier, &matriz_deadlock);
	//************************************************************
	
	//Chamando o escalonador de serviço pra gerenciar*************
	escalonador();
	//************************************************************
	
	return 0;
}

void escalonador()
{
	int a = 1, i;
	while(a<10)
	{			
		deadlock_barrier_wait(&barrier);
		deadlock_mutex_lock( var_coltrol.mutex );
			
			for(i = 0; i < NuProcessos; i++)
			{	
				if(verificaServir(matriz_deadlock.SD, matriz_deadlock.MR[i]) == 1)
					servir(i);
			}
			printMatrizRequisicao();
			if(verificaDeadlock() == 1)
				printf("DEADLOCK: ***********************************************************************\n");
			
		deadlock_mutex_unlock( var_coltrol.mutex );
		printf("VALOR DE a: %d\n", a);
		a++;
	}
	
}
//Função que serve ao processo(basicamente ela verifica se o processo pode ser servido
//se sim ele serve somando a linha do processo da matriz de requisição, na matriz de serviços alocados)
void servir(int i)
{
	
	int j;
	printf("servindo*****************************************\n");
	for(j = 0; j < NuServicos; j++)
	{
		matriz_deadlock.MA[i][j] += matriz_deadlock.MR[i][j];
		matriz_deadlock.SD[j] -= matriz_deadlock.MR[i][j];
		matriz_deadlock.MR[i][j] = 0;
	}
	matriz_deadlock.MR[i][NuServicos] = 0;	
}

//Verifica se o vetor SD pode servir à requisição MR
int verificaServir(int *SD, int *MR)
{
	int j;
	for(j = 0; j < NuServicos; j++)
	{
		if(SD[j] < MR[j])
			return 0;
	}
	return 1;
	
}

//verifica se gerou deadlock
int verificaDeadlock()
{
	
	int i, j;
	int vet[NuServicos];
	printf("verificando deadlock***********************************\n");
	for(i = 0; i < NuServicos; i++)
		vet[i] = 0;
	for(i = 0; i < NuProcessos; i++)
	{
		if(matriz_deadlock.MR[i][NuServicos] == 0)
		{
			for(j = 0; j < NuServicos; j++)
				vet[j] += matriz_deadlock.MA[i][j];
		}
	}
	for(j = 0; j < NuServicos; j++)
		vet[j] += matriz_deadlock.SD[j];
	
	//verifica se os recursos dos processos que n tem mais requisição somados aos restantes pode servir aos que estão esperando
	//se sim: não deu deadlock
	//se não: deu deadlock
	for(i = 0; i < NuProcessos; i++)
		if(matriz_deadlock.MR[i][NuServicos] == 1 && verificaServir(vet, matriz_deadlock.MR[i]) == 0){
			return 1;
		}
	for(i = 0; i < NuProcessos; i++)
		if(matriz_deadlock.MR[i][NuServicos] == 0){
			return 0;
		}
	return 1;
}
