#include <stdio.h>
#include <pthread.h>

enum
{
    NTHREADS = 3
};

int shared = 0;

void *
thread_func(void *arg)
{
    int local = 3;
    printf("Нить номер %ld с ID '%lx', shared = %d, local = %d\n", (long) arg, pthread_self(), shared++, local++);
    return NULL;
}

int
main(void)
{
    pthread_t threads[NTHREADS];
    for (long i = 0; i < NTHREADS; ++i) {
        pthread_create(&threads[i], NULL, thread_func, (void *) i);
        printf("Создана нить №%ld\n", i);
    }
    for (int i = 0; i < NTHREADS; ++i) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}
