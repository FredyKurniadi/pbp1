#include <stdio.h>

unsigned long long factorial_iterative(int n) {
    unsigned long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    int num = 20;  // Menggunakan nilai yang lebih kecil
    printf("Factorial of %d is %llu\n", num, factorial_iterative(num));
    return 0;
}

