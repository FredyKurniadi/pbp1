#include <stdio.h>
#include <stdlib.h>

void allocateMemory() {
    // Mengalokasikan memori sebesar 1 KB
    char *ptr = (char *)malloc(1024);
    if (ptr == NULL) {
        printf("Gagal mengalokasikan memori\n");
        return;
    }
    printf("Berhasil mengalokasikan 1 KB memori\n");

    // Simulasi penggunaan memori
    for (int i = 0; i < 1024; i++) {
        ptr[i] = 'A';
    }

    // Intentionally not freeing memory to simulate memory leak
    // free(ptr);  // Uncomment this line to free memory
}

int main() {
    int iterations = 0;

    // Simulasi alokasi memori berkali-kali
    while (iterations < 10000) {
        allocateMemory(); // Alokasi memori di setiap iterasi
        iterations++;
        printf("Iterasi ke-%d\n", iterations);
    }

    printf("Program selesai\n");
    return 0;
}
