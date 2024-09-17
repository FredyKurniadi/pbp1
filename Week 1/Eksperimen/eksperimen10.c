#include <stdio.h>

// Segmen Data: Variabel yang diinisialisasi
int initialized_data = 100;

// Segmen BSS: Variabel yang tidak diinisialisasi
int uninitialized_data;

// Segmen Text: Fungsi untuk mengakses segmen memori
void print_memory_segments() {
    printf("Alamat Segmen Text (fungsi print_memory_segments): %p\n", (void *)print_memory_segments);
    printf("Alamat Segmen Data (initialized_data): %p\n", (void *)&initialized_data);
    printf("Alamat Segmen BSS (uninitialized_data): %p\n", (void *)&uninitialized_data);
}

int main() {
    // Segmen Stack: Variabel lokal
    int local_variable = 10;

    // Segmen Heap: Variabel yang dialokasikan secara dinamis
    int *heap_variable = (int *)malloc(sizeof(int));
    *heap_variable = 50;

    // Tampilkan informasi tentang segmen memori
    printf("Alamat Segmen Stack (local_variable): %p\n", (void *)&local_variable);
    printf("Alamat Segmen Heap (heap_variable): %p\n", (void *)heap_variable);

    // Panggil fungsi untuk menampilkan alamat segmen Text, Data, dan BSS
    print_memory_segments();

    // Tampilkan nilai variabel untuk memastikan konsistensi
    printf("\nNilai dari initialized_data (Segmen Data): %d\n", initialized_data);
    printf("Nilai dari uninitialized_data (Segmen BSS, seharusnya 0): %d\n", uninitialized_data);

    // Bebaskan memori heap
    free(heap_variable);

    return 0;
}
