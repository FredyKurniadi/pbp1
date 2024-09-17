#include <stdio.h>

unsigned long long factorial(int n) {
    // Basis kasus
    if (n == 0 || n == 1)
        return 1;
    // Rekursi
    return n * factorial(n - 1);
}

int main() {
    int num = 50000;  // Nilai yang sangat besar untuk memicu stack overflow
    printf("Factorial of %d is %llu\n", num, factorial(num));
    return 0;
}

