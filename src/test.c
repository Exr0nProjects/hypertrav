// based off of https://stackoverflow.com/a/43993821/10372825
#include <stdio.h>
#include <threads.h>
#include <stdatomic.h>

atomic_int acnt;

const int max = 493;
int rmax = 0;

int f(void* thr_data)
{
	for (int i=1; i<=100; ++i) {
		if (++acnt <= max) {
			printf("got %5d\n", acnt);
			if (acnt > rmax) rmax = acnt;
		}
		--acnt;
	}
    return 0;
}

#define num_threads 1000
int main(void)
{
    thrd_t thr[num_threads];
    for(int n = 0; n < num_threads; ++n)
        thrd_create(&thr[n], f, &n);
    for(int n = 0; n < num_threads; ++n)
        thrd_join(thr[n], NULL);

    printf("The atomic counter is %u\n", acnt);
    printf("the max was %d\n", rmax);
}
