#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void calculateCatalanNumbers(int *result, int n) {
    result[0] = 1;
    for (int i = 1; i <= n; ++i) {
        result[i] = 0;
        for (int j = 0; j < i; ++j) {
            result[i] += result[j] * result[i - j - 1];
        }
    }
}

int isPrime(int num) {
    if (num <= 1) {
        return 0;
    }
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}

void calculatePrimeNumbers(int *result, int n) {
    int count = 0;
    int num = 2;
    while (count < n) {
        if (isPrime(num)) {
            result[count] = num;
            ++count;
        }
        ++num;
    }
}

void *calculateCatalan(void *args) {
    int n = *((int *)args);
    int *catalanNumbers = malloc((n + 1) * sizeof(int));
    calculateCatalanNumbers(catalanNumbers, n);
    pthread_exit((void *)catalanNumbers);
}

void *calculatePrimes(void *args) {
    int n = *((int *)args);
    int *primeNumbers = malloc(n * sizeof(int));
    calculatePrimeNumbers(primeNumbers, n);
    pthread_exit((void *)primeNumbers);
}

int main() {
    pthread_t catalanThread, primesThread;
    int n = 10;

    pthread_create(&catalanThread, NULL, calculateCatalan, (void *)&n);
    pthread_create(&primesThread, NULL, calculatePrimes, (void *)&n);

    int *catalanNumbers;
    int *primeNumbers;

    pthread_join(catalanThread, (void **)&catalanNumbers);
    pthread_join(primesThread, (void **)&primeNumbers);

    printf("Catalan Numbers: ");
    for (int i = 0; i <= n; ++i) {
        printf("%d ", catalanNumbers[i]);
    }
    printf("\n");

    printf("Prime Numbers: ");
    for (int i = 0; i < n; ++i) {
        printf("%d ", primeNumbers[i]);
    }
    printf("\n");

    free(catalanNumbers);
    free(primeNumbers);

    return 0;
}
