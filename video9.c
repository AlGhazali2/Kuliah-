#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 4 //menggunakan 4 threads 
static long num_steps = 1000000;
double step;

int main() {
    int i, id;
    double x, pi, sum = 0.0;

    step = 1.0 / (double) num_steps;
    omp_set_num_threads(NUM_THREADS);

    #pragma omp parallel private(x, i, id) reduction(+:sum)
    {
        id = omp_get_thread_num();
        double local_sum = 0.0; // Variabel lokal untuk setiap thread

        for (i = id + 1; i <= num_steps; i = i + NUM_THREADS) {
            x = (i - 0.5) * step;
            local_sum += 4.0 / (1.0 + x * x);
        }

        #pragma omp critical //disinilah kita menginisiasi critical directive
        sum += local_sum; //memastikan looping local sum hanya diakses oleh satu thread dalam satu waktu.
    }

    pi = sum * step;
    printf("Nilai pi: %.15f\n", pi);
    return 0;
}
