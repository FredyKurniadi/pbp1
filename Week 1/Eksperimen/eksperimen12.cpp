#include <stdio.h>
#include <string.h>

// Fungsi rentan terhadap buffer overflow
void vulnerable_function(char* input) {
    char buffer[10]; // Buffer hanya sebesar 10 byte

    // Fungsi strcpy tidak melakukan pengecekan ukuran buffer
    strcpy(buffer, input);

    printf("Buffer berisi: %s\n", buffer);
}

int main() {
    // Input lebih besar dari ukuran buffer
    char large_input[25] = "This input is too long!";
    
    printf("Memanggil fungsi dengan input yang terlalu panjang...\n");
    vulnerable_function(large_input);

    return 0;
}

