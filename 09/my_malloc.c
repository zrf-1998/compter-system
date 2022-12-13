#include "csapp.h"

extern void mm_free(void *bp);
extern int mm_init(void);
extern void *mm_malloc(size_t size);
extern void mem_init(void);

void *heap_listp = NULL;

int main()
{
	mem_init();
	char *p = NULL;

	if(mm_init() < 0)
		exit(-1);
	
	p = (char *)mm_malloc(32);
	mm_free(p);

	return 0;
}
