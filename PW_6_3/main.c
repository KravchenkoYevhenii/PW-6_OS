#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


struct ThreadParams {
    int repetitions;
    int NumR;
    int Num;
};

void *printString(void *params) {
    int repetitions = ((struct ThreadParams *)params)->repetitions;
    for (int i = 0; i < repetitions; ++i) {
        printf("Child Thread. Iteration: %d\n", i + 1);
        sleep(rand() % 3);
    }
    pthread_exit(NULL);
}

void *generateRandomNumbers(void *params) {
    struct ThreadParams *threadParams = (struct ThreadParams *)params;
    int range = threadParams->NumR;
    int targetNumber = threadParams->Num;

    for (int i = 0; i < range; ++i) {
        int randomNumber = rand() % (range + 1);
        printf("Child Thread. Number: %d\n", randomNumber);

        if (randomNumber == targetNumber) {
            printf("Child Thread. Found: %d\n", targetNumber);
            pthread_exit(NULL);
        }

        sleep(rand() % 3);
    }

    printf("Child Thread. Not found: %d\n", targetNumber);
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;
    struct ThreadParams params1 = {10, 0, 0};
    struct ThreadParams params2 = {15, 50, 24};

    srand(time(NULL));

    pthread_create(&thread1, NULL, printString, (void *)&params1);
    pthread_create(&thread2, NULL, generateRandomNumbers, (void *)&params2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Main Thread. Have finished.\n");

    return 0;
}
