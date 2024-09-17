#include <iostream>

int main() {
    // Mencoba mengalokasikan memori dalam jumlah besar tanpa penanganan pengecualian
    int* arr = new int[1000000000]; // Mencoba mengalokasikan array dengan 1 miliar elemen
    std::cout << "Memori berhasil dialokasikan!" << std::endl;

    // Membebaskan memori yang dialokasikan
    delete[] arr;

    return 0;
}

