#ifndef DEADLOCK_HEADER
#define DEADLOCK_HEADER

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

pthread_barrier_t barrier1;
deadlock_info_t var_coltrol;
deadlock_t *var_info;
pthread_t thread[10];
void *recurso(void *ptr);
void deadlock_pre_init();
int deadlock_init(deadlock_mutex_t *mutex, deadlock_barrier_t *barrier, deadlock_t *matriz_deadlock, int *vet);
void deadlock_init_var();
void printMatrizRequisicao();
void deadlock_exit();
int deadlock_mutex_unlock(deadlock_mutex_t *mutex);
int deadlock_mutex_lock(deadlock_mutex_t *mutex);
int deadlock_barrier_wait(deadlock_barrier_t *barrier);
int deadlock_barrier_init(deadlock_barrier_t *barrier, int i);

#endif
