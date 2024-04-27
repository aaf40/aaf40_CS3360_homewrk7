// compile with: gcc -fopenmp -o omp_test omp_test.c
// run with: ./omp_test
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>

#define ARRAY_SIZE 1000000
#define NUM_ITERATIONS 1000

int main() {
    int *data = malloc(ARRAY_SIZE * sizeof(int));
    struct timeval start, end;
    double times[5];

    for (int i = 0; i < ARRAY_SIZE; i++) {
        data[i] = rand();
    }

    int cpus[] = {1, 2, 4, 8, 16};
    for (int idx = 0; idx < 5; idx++) {
        int num_cpus = cpus[idx];
        double total_time = 0.0;

        for (int run = 0; run < 5; run++) {
            gettimeofday(&start, NULL);
            omp_set_num_threads(num_cpus);
            #pragma omp parallel for
            for (int i = 0; i < ARRAY_SIZE; i++) {
                int temp;
                for (int j = 1; j <= NUM_ITERATIONS; j++) {
                    temp = data[i] % j;
                }
            }
            gettimeofday(&end, NULL);
            double elapsed_time = (end.tv_sec - start.tv_sec) * 1000.0;
            elapsed_time += (end.tv_usec - start.tv_usec) / 1000.0;
            total_time += elapsed_time;
        }

        times[idx] = total_time / 5.0;
        printf("Average time with %d CPUs: %f ms\n", num_cpus, times[idx]);
    }

    free(data);
    return 0;
}
