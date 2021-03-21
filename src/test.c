#include <stdio.h>
#include <pthread.h>

// stack

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
	pthread_t thread_id;
	puts("starting thread");
	pthread_create(&thread_id, NULL, threaded, NULL);
	int i=0; for (; i<15; ++i);
	puts("during execution");
	pthread_join(thread_id, NULL);
	puts("thread finished");
}
