#include <stdio.h>

#define N 1024
#define MIN_SIZE 64

int dot_product(int *A, int *B, int n) {
    int tmp = 0;
    for (int i = 0; i < n; i++) {
        tmp += A[i] * B[i];
    }
    return tmp;
}

int rec_dot_product(int *A, int *B, int n) { 
    int tmp1 = 0, tmp2 = 0; 
    if (n > MIN_SIZE) { 
        int n2 = n / 2;
        tmp1 = rec_dot_product(A, B, n2); 
        tmp2 = rec_dot_product(A + n2, B + n2, n - n2); 
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

    int result = rec_dot_product(a, b, N);
    printf("Hasil dot product rekursif: %d\n", result);

    return 0;
}
