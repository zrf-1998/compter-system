#include "csapp.h"
#include "sbuf.h"

/* Create an empty, bounded, shared FIFO buffer with n slots */
void sbuf_init(sbuf_t *sp, int n)
{
	sp->buf = Calloc(n, sizeof(int));		
	sp->n = n;													/* Buffer holds max of n items */
	sp->front = sp->rear = 0;						/* Empty buffer iff front == rear */
	Sem_init(&sp->mutex, 0, 1);					/* Binary semaphore for locking */
	Sem_init(&sp->slots, 0, n);					/* Initially, buf has n empty slots */
	Sem_init(&sp->items, 0, 0);					/* Initially, buf has zero data items */
}

/* Clean up buffer sp */
void sbuf_deinit(sbuf_t *sp)
{
	Free(sp->buf);
}

/* Insert item onto the rear of shared buffer sp */
void sbuf_insert(sbuf_t *sp, int item)
{
	P(&sp->slots);													/* Wait for available solt */						
	P(&sp->mutex);													/* Lock the buffer */
	sp->buf[(++sp->rear)%(sp->n)] = item;		/* Insert the item */
	printf("insert %d to buffer\n", item);
	V(&sp->mutex);													/* Unlock the buffer */
	V(&sp->items);													/* Announce available item */
}

/* Remove and return the first item from buffer sp */
int sbuf_remove(sbuf_t *sp)
{
	int item;
	P(&sp->items);													/* Wait for available item */
	P(&sp->mutex);													/* Lock the buffer */
	item = sp->buf[(++sp->front)%(sp->n)];	/* remove the item */
	printf("remove %d from buffer\n", item);
	V(&sp->mutex); 													/* Unlock the buffer */
	V(&sp->slots);													/* Announce available solt */
	return item;
}

#ifdef TEST
sbuf_t s;

void *thread(void *vargp)
{
	int item;
	sbuf_t *sp = (sbuf_t *)vargp;
	do
	{
		item = sbuf_remove(sp);
	}while(item > 0);
}

int main(int argc, char **argv)
{
	int item;
	pthread_t tid;
	char buf[MAXLINE];

	if(argc != 2)
	{
		fprintf(stderr, "usage: %s <maxsolts>\n", argv[0]);
		exit(0);
	}

	sbuf_init(&s, atoi(argv[1]));

	Pthread_create(&tid, NULL, thread, &s);
	while(Fgets(buf, MAXLINE, stdin))
	{
		item = atoi(buf);
		sbuf_insert(&s, item);
	}
	Pthread_join(tid, NULL);
	sbuf_deinit(&s);
	return 0;
}
#endif
