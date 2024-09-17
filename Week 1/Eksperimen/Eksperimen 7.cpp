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

