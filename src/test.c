#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

const size_t MAX_PATH_LEN = 4096;
size_t threads = 1;             // this shouldn't be changed once threads are allocated
char **bufs = NULL;

// stack
int * _Atomic stack_store;
int _Atomic stack_sz;        // number of elements on the stack
int _Atomic stack_opcnt;

void st_push()
{
	printf("%u\n", __atomic_load_n(&stack_sz, __ATOMIC_RELAXED));
	for (;;) {
	}
}
char *st_pop()
{
	printf("%u\n", __atomic_load_n(&stack_sz, __ATOMIC_RELAXED));
}

// thread functions
void *threaded(void *var)
{
	for (int i=1; i<=30; ++i)
		printf("print from threaded x%d\n", i);
	return NULL;
}

// main
int main()
{
	// set up datastructures
	const size_t input = 3;
	threads = input;
	stack_store = calloc(threads, sizeof(size_t));

	st_pop();

	// threading stuffs
	pthread_t thread_id;
	puts("starting thread");
	pthread_create(&thread_id, NULL, threaded, NULL);
	int i=0; for (; i<15; ++i);
	puts("during execution");
	pthread_join(thread_id, NULL);
	puts("thread finished");
}
