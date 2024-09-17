Nama    : Carissa Amanda Chrisanty Lesmana
NIM     : 231524003

# "Stack Overflow"

# 1. Identifikasi Problem
Masalah: Stack overflow adalah kondisi di mana stack, yaitu area memori yang digunakan oleh program untuk menyimpan variabel lokal, parameter fungsi, dan informasi lain yang diperlukan oleh proses eksekusi, kehabisan ruang. Salah satu penyebab umum stack overflow adalah penggunaan rekursi yang terlalu dalam atau alokasi memori yang terlalu besar untuk variabel lokal. Ketika stack overflow terjadi, program bisa mengalami crash atau menunjukkan perilaku yang tak terduga.

# 2. Deskripsi Problem
Stack overflow terjadi karena stack memiliki ukuran yang terbatas. Ketika sebuah program menggunakan rekursi dalam yang tidak terkendali atau mengalokasikan memori dalam jumlah besar di dalam stack, maka ukuran stack bisa melampaui batas yang diizinkan oleh sistem. Akibatnya, program tidak dapat melanjutkan eksekusi dan bisa berhenti secara mendadak (crash) atau memberikan hasil yang tidak diinginkan.

Dalam eksperimen ini, kita akan membuat sebuah program yang menggunakan rekursi untuk menghitung faktorial dari sebuah angka, tetapi dengan sengaja membuat rekursi yang terlalu dalam untuk memicu stack overflow. Program ini akan memberikan wawasan tentang bagaimana stack overflow dapat terjadi dan efeknya terhadap program.

# 3. Metodologi Eksperimen
Alat dan Bahan: Komputer dengan sistem operasi yang mendukung pemrograman C/C++, Python, atau Java.
Pendekatan:
Membuat program yang menggunakan rekursi untuk menghitung faktorial.
Menjalankan program dengan nilai input yang cukup besar untuk memicu stack overflow.
Mencatat gejala dan hasil yang muncul setelah terjadinya stack overflow.

# 4. Pelaksanaan Eksperimen
Program C dengan Stack Overflow:
```
#include <stdio.h>

// Fungsi rekursif untuk menghitung faktorial
unsigned long long factorial(int n) {
    // Basis kasus untuk menghentikan rekursi
    if (n == 0 || n == 1)
        return 1;
    else
        return n * factorial(n - 1); // Rekursi
}

int main() {
    int num = 50000;  // Memasukkan nilai yang sangat besar untuk memicu stack overflow

    // Mencetak hasil faktorial
    printf("Menghitung faktorial dari %d\n", num);
    unsigned long long result = factorial(num);  // Panggilan rekursif
    printf("Factorial of %d is %llu\n", num, result);

    return 0;
}
```

Penjelasan Program:
1. Fungsi factorial():
- Fungsi ini secara rekursif menghitung faktorial dari suatu angka 𝑛.
- Jika 𝑛=0 atau 𝑛=1 fungsi akan mengembalikan 1 (basis kasus).
- Jika 𝑛>1 fungsi akan memanggil dirinya sendiri dengan nilai 𝑛−1, yang menyebabkan rekursi.

2. Pemicu Stack Overflow:
- Ketika kita mencoba menghitung faktorial dari angka besar seperti 50000, setiap pemanggilan rekursif menyimpan informasi pada stack.
- Karena ada batasan ukuran stack, setelah kedalaman rekursi tertentu, stack akan penuh, yang menyebabkan stack overflow.

3. Output
- Program ini tidak akan menyelesaikan perhitungan untuk 𝑛=50000. Sebaliknya, program akan mengalami crash, dan pada sistem berbasis Unix/Linux akan menampilkan error seperti segmentation fault.

4. Stack Overflow
- Terjadi karena setiap kali rekursi dipanggil, memori disimpan si stack, dan nilai 𝑛=50000 akan memicu terlalu banyak pemanggilan rekursif hingga stack kehabisan memori.

# Solusi untuk Mencegah Stack Overflow:
Untuk menghindari stack overflow, kita bisa mengubah algoritma menjadi versi iteratif yang tidak menggunakan rekursi, sehingga tidak bergantung pada kedalaman stack.

Program Faktorial Versi Iteratif (Tanpa Stack Overflow):
```
#include <stdio.h>

// Fungsi iteratif untuk menghitung faktorial
unsigned long long factorial_iterative(int n) {
    unsigned long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;  // Kalikan hasil dengan i
    }
    return result;
}

int main() {
    int num = 20;  // Menggunakan nilai yang lebih kecil agar perhitungan lebih cepat

    // Mencetak hasil faktorial
    printf("Factorial of %d is %llu\n", num, factorial_iterative(num));

    return 0;
}
```

Pada solusi iteratif ini, kita menghitung faktorial menggunakan perulangan for, yang tidak menambahkan frame baru ke stack. Program ini tidak akan mengalami stack overflow bahkan untuk nilai yang lebih besar.