#include <stdio.h>
#include <omp.h>

#define N 1024
#define MIN_SIZE 64
#define CUTOFF 3

int dot_product(int *A, int *B, int n) {
    int tmp = 0;
    for (int i = 0; i < n; i++) {
        tmp += A[i] * B[i];
    }
    return tmp;
}

int rec_dot_product(int *A, int *B, int n, int depth) {
    int tmp1 = 0, tmp2 = 0;

    if (n > MIN_SIZE) {
        int n2 = n / 2;

        if (!omp_in_final()) {
            #pragma omp task shared(tmp1) final(depth >= CUTOFF)
            tmp1 = rec_dot_product(A, B, n2, depth + 1);

            #pragma omp task shared(tmp2) final(depth >= CUTOFF)
            tmp2 = rec_dot_product(A + n2, B + n2, n - n2, depth + 1);

            #pragma omp taskwait
        } else {
            tmp1 = rec_dot_product(A, B, n2, depth + 1);
            tmp2 = rec_dot_product(A + n2, B + n2, n - n2, depth + 1);
        }
    } else {
        tmp1 = dot_product(A, B, n);
    }
    
    return tmp1 + tmp2;
}

int main() {
    int a[N], b[N];

    // Inisialisasi array a dan b dengan nilai contoh
    for (int i = 0; i < N; i++) {
        a[i] = 1;
        b[i] = 1;
    }

    int result = 0;

    #pragma omp parallel
    {
        #pragma omp single
        result = rec_dot_product(a, b, N, 0);
    }

    printf("Hasil dot product rekursif: %d\n", result);
    return 0;
}
