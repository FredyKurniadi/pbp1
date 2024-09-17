#include <iostream>
#include <new>  // Untuk std::bad_alloc

int main() {
    try {
        // Mencoba mengalokasikan memori dalam jumlah besar dengan penanganan pengecualian
        int* arr = new int[1000000000]; // Mencoba mengalokasikan array dengan 1 miliar elemen
        std::cout << "Memori berhasil dialokasikan!" << std::endl;

        // Membebaskan memori yang dialokasikan
        delete[] arr;
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "Alokasi memori gagal: " << e.what() << std::endl;
    }

    return 0;
}

