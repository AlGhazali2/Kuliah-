#include <stdio.h>
#include <omp.h>

int main() {
    int number = 1;
    int sum = 0;

    #pragma omp parallel //Membuka sebuah wilayah paralel. Semua kode di dalamnya akan dijalankan secara paralel oleh beberapa thread.
    {
        // Task 1: Mencetak Nilai dari Value saat ini
        #pragma omp single
        {
            #pragma omp task shared(number)
            {
                printf("Initial number is: %d\n", number);
            }
        }

        // Task 2:  menaikkan nilai dari number dan melakukan reduksi dari sum
        #pragma omp single // Hanya satu thread yang membuat task ini untuk menghindari duplikasi.
        {
            #pragma omp task shared(number) //Tugas ini membaca dan mencetak nilai awal variabel number
            {
                int my_number = number;

                // Seksi kritis memastikan hanya satu thread yang bisa mengakses dan memodifikasi number secara aman pada satu waktu.
                #pragma omp critical
                {
                    my_number = number++;
                }

                // Operasi atomik menjamin bahwa penjumlahan ke variabel sum tidak mengalami race condition.
                #pragma omp atomic
                sum += my_number;

                printf("Updated number is: %d\n", my_number);
            }
        }

        // Task 3: Melakukan Operasi Lagi
        #pragma omp task shared(sum)
        {
            printf("Final sum after task updates: %d\n", sum);
        }
    }

    printf("Final value of number: %d\n", number); //Setelah wilayah paralel selesai, nilai akhir dari number dan sum dicetak di luar wilayah paralel.
    printf("Final computed sum: %d\n", sum);

    return 0;
}
