Nama    : Carissa Amanda Chrisanty Lesmana
NIM     : 231524003

# Kesalahan Alokasi Dinamis Dengan New"'

# 1. Identifikasi Problem
Ketika menggunakan alokasi dinamis dengan kata kunci new dalam bahasa pemrograman seperti C++, jika alokasi memori gagal dan tidak ada mekanisme penanganan kesalahan, maka akan terjadi kebocoran memori. Ini terjadi karena memori yang dialokasikan tidak akan pernah dibebaskan kembali jika program tidak menangani pengecualian yang terjadi saat alokasi memori gagal. Akibatnya, penggunaan memori meningkat tanpa batas, yang dapat menyebabkan sistem kehabisan memori dan program crash.

# 2. Deskripsi Problem
Dalam bahasa C++, new digunakan untuk mengalokasikan memori secara dinamis di heap. Namun, jika alokasi memori gagal (misalnya, karena kekurangan memori), new akan melemparkan pengecualian std::bad_alloc. Jika pengecualian ini tidak ditangani dengan benar, memori yang sebelumnya telah dialokasikan dapat terlepas begitu saja tanpa dibebaskan, menyebabkan kebocoran memori.

Kebocoran memori ini bisa sangat berbahaya, terutama dalam aplikasi yang berjalan dalam waktu lama atau yang membutuhkan alokasi memori yang besar dan sering. Ini akan menyebabkan program menggunakan lebih banyak memori dari yang seharusnya, hingga akhirnya sistem menjadi tidak stabil.

# 3. Metodologi Eksperimen
Eksperimen ini akan dilakukan dengan langkah-langkah sebagai berikut:

Membuat program sederhana yang menggunakan alokasi dinamis dengan new tanpa penanganan pengecualian.
Menjalankan program untuk melihat apa yang terjadi ketika alokasi memori gagal.
Membuat versi kedua dari program yang sama, namun kali ini dengan penanganan pengecualian untuk menangani kegagalan alokasi memori.
Mengamati perbedaan hasil antara kedua program tersebut.

# 4. Pelaksanaan Eksperimen
Contoh Program C++: Kesalahan Alokasi Dinamis dengan new
Skenario 1: Tanpa Penanganan Pengecualian
```
#include <iostream>

int main() {
    // Mencoba mengalokasikan memori dalam jumlah besar tanpa penanganan pengecualian
    int* arr = new int[1000000000]; // Mencoba mengalokasikan array dengan 1 miliar elemen
    std::cout << "Memori berhasil dialokasikan!" << std::endl;

    // Membebaskan memori yang dialokasikan
    delete[] arr;

    return 0;
}
```

# Penjelasan:
1. Pada program di atas, kita mencoba mengalokasikan memori yang sangat besar dengan new. Jika alokasi memori gagal, program bisa crash karena tidak ada penanganan kesalahan (std::bad_alloc).
2. Ketika memori yang dialokasikan tidak mencukupi, program akan berhenti atau crash tanpa pesan kesalahan.

Skenario 2: Dengan Penanganan Pengecualian (std::bad_alloc)
```
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
```

# Penjelasan:
1. Di sini, kita menggunakan try-catch untuk menangkap pengecualian std::bad_alloc, yang akan dilemparkan ketika alokasi memori dengan new gagal.
2. Jika alokasi memori gagal, program tidak akan crash, dan kita akan mendapatkan pesan kesalahan yang jelas (Alokasi memori gagal: bad allocation), yang menunjukkan kegagalan alokasi.

# Perbedaan Output:
1. Tanpa Penanganan Pengecualian:
-Jika sistem tidak memiliki cukup memori, program akan crash atau berhenti tanpa memberikan pesan kesalahan.
2. Dengan Penanganan Pengecualian:
-Jika alokasi memori gagal, program akan menangkap pengecualian std::bad_alloc dan menampilkan pesan kesalahan:
```
Alokasi memori gagal: std::bad_alloc
```
# Kesimpulan:
- Tanpa Penanganan Pengecualian: Program akan crash jika alokasi memori gagal.
- Dengan Penanganan Pengecualian: Program bisa menangani kegagalan memori dengan aman, memberikan pesan kesalahan yang jelas tanpa menyebabkan crash.

Program ini menunjukkan pentingnya menangani pengecualian std::bad_alloc ketika menggunakan alokasi memori dinamis dengan new di C++.