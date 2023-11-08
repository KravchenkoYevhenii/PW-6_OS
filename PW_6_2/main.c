#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct ThreadParams {
    char *name;
    char *str;
    int num;
};

void *threadFunction(void *params) {
    struct ThreadParams *threadParams = (struct ThreadParams *)params;

    for (int i = 1; i <= threadParams->num; ++i) {
        printf("Thread %s. %s %d\n", threadParams->name, threadParams->str, i);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[4];
    char *names[] = {"First", "Second", "Third", "Fourth"};
    char *str = "String value";
    int num = 5;

    struct ThreadParams threadParams[4];
    for (int i = 0; i < 4; ++i) {
        threadParams[i].name = names[i];
        threadParams[i].str = str;
        threadParams[i].num = num;
        pthread_create(&threads[i], NULL, threadFunction, (void *)&threadParams[i]);
    }
    for (int i = 0; i < 4; ++i) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
