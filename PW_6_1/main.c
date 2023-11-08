#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *childThread(void *arg) {
    int i;
    for (i = 1; i <= 10; ++i) {
        printf("Child Thread. Iteration: %d\n", i);
        sleep(rand() % 3);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t thread;
    int i;

    srand(time(NULL));

    for (i = 1; i <= 10; ++i) {
        printf("Main Thread. Iteration: %d\n", i);
        sleep(rand() % 3); //
    }

    pthread_create(&thread, NULL, childThread, NULL);

    pthread_join(thread, NULL);

    return 0;
}
