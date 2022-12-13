/* WARNING: This code is buggy */
#include "csapp.h"
#define N 4

void *thread(void *vargp);

int main()
{
	pthread_t tid[N];
	int myid[N];
	int i;

	for(i = 0; i < N; i++)
	{
		myid[i] = i;
		Pthread_create(&tid[i], NULL, thread, &myid[i]);
	}
	for(i = 0; i < N; i++)
		Pthread_join(tid[i], NULL);

	exit(0);
}

/* Thread routine */
void * thread(void *vargp)
{
	int myid = *((int *)vargp);
	printf("Hello from thread %d\n", myid);
	return NULL;
}
