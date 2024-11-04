#include <stdio.h>

#define N 1024
#define MIN_SIZE 64

int dot_product (int *A, int *B, int n) { 
    int result = 0;
    for (int i = 0; i < n; i++)
        result += A[i] * B[i];
    return result;
}

int rec_dot_product(int *A, int *B, int n) {
    if (n > MIN_SIZE) {
        int n2 = n / 2;
        return rec_dot_product(A, B, n2) + rec_dot_product(A + n2, B + n2, n - n2);
    } else {
        return dot_product(A, B, n);
    }
}

int main() { 
    int a[N], b[N];

    // Inisialisasi array contoh (misalnya, dengan nilai 1 untuk pengujian)
    for (int i = 0; i < N; i++) {
        a[i] = 1;
        b[i] = 1;
    }

    int result = rec_dot_product(a, b, N);
    printf("Hasil dot product: %d\n", result);

    return 0;
}
