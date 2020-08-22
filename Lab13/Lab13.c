#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

typedef struct cstruct{
	double* a; double* sum;
	int    N, size, tid;
	sem_t*     mutex;
} CUSTOM;

void *compute(void *arg) {
	int myStart, myEnd, myN, i;
	//long tid = (long)arg;
	CUSTOM* cur = (CUSTOM*)arg;

	// determine start and end of computation for the current thread
	myN = cur->N/cur->size;
	myStart = cur->tid*myN;
	myEnd = myStart + myN;
	if (cur->tid == (cur->size-1)) myEnd = cur->N;

	// compute partial sum
	double mysum = 0.0;
	for (i=myStart; i<myEnd; i++){
		mysum += cur->a[i];
	}
	// grab the lock, update global sum, and release lock
	sem_wait(cur->mutex);
	*cur->sum += mysum;
	//printf("%d: Added mysum (%f) to existing sum (%f) = %f\n", cur->tid, mysum,*cur->sum - mysum, *cur->sum);
	sem_post(cur->mutex);

	return NULL;
}

int main(int argc, char **argv) {
	long i;
	int N, size;
	double sum = 0.0;
	double* a;
	sem_t mutex;
	pthread_t *tid;

	if (argc != 3) {
		printf("Usage: %s <# of elements> <# of threads>\n",argv[0]);
		exit(-1);
	}

	N = atoi(argv[1]); // no. of elements
	size = atoi(argv[2]); // no. of threads

	// allocate vector and initialize
	tid = (pthread_t *)malloc(sizeof(pthread_t)*size);
	sem_init(&mutex, 0, 1);
	CUSTOM* list = (CUSTOM*)malloc(sizeof(CUSTOM) * size);
	
	a = (double *)malloc(sizeof(double)*N); 
	for (i=0; i<N; i++)
	a[i] = (double)(i + 1);

	// create threads
	for ( i = 0; i < size; i++){
		list[i].sum = &sum;
		list[i].N = N;
		list[i].size = size;
		list[i].a = a;
		list[i].tid = i;
		list[i].mutex = &mutex;
		pthread_create(&tid[i], NULL, compute, (void *)&list[i]);
	}
	
	// wait for them to complete
	for ( i = 0; i < size; i++){
		pthread_join(tid[i], NULL);
		//printf("%f+%f=%f\n",sum, fp->sum, sum + fp->sum);
		//sum += fp->sum;
	}
	
	printf("The total is %g, it should be equal to %g\n", 
	sum, ((double)N*(N+1))/2);
	sem_destroy(&mutex);
	return 0;
}

