**Memory leak** adalah kondisi di mana memori yang dialokasikan oleh program tidak dibebaskan kembali setelah digunakan, sehingga memori tersebut tidak dapat digunakan ulang. Hal ini dapat menyebabkan pemborosan memori dan pada akhirnya membuat program kekurangan memori, memperlambat kinerja, atau bahkan crash jika kebocoran memori berlangsung terus menerus.

### Penjelasan lebih lanjut:
Dalam banyak bahasa pemrograman (seperti C dan C++), program perlu secara eksplisit mengalokasikan dan membebaskan memori. Ketika sebuah program mengalokasikan memori dengan menggunakan fungsi seperti `malloc()` (untuk C) atau `new` (untuk C++), maka program bertanggung jawab untuk membebaskan memori tersebut dengan menggunakan fungsi seperti `free()` (untuk C) atau `delete` (untuk C++).

Jika setelah memori dialokasikan program tidak membebaskan memori tersebut, memori itu tetap dianggap terpakai oleh sistem, meskipun sebenarnya tidak lagi digunakan oleh program. Itulah yang disebut kebocoran memori. Seiring waktu, program akan terus mengalokasikan memori baru tanpa membebaskan yang lama, menyebabkan penggunaan memori terus bertambah dan akhirnya dapat menghabiskan memori yang tersedia.

### Contoh:
Contoh sederhana dalam C yang menyebabkan kebocoran memori:

```c
#include <stdio.h>
#include <stdlib.h>

void memory_leak_example() {
    int* ptr = (int*)malloc(sizeof(int) * 10);  // Alokasi memori untuk 10 integer
    if (ptr == NULL) {
        printf("Memori tidak dapat dialokasikan\n");
        return;
    }
    
    // Penggunaan memori yang dialokasikan
    for (int i = 0; i < 10; i++) {
        ptr[i] = i;
    }
    
    // Program tidak membebaskan memori dengan free(ptr), sehingga terjadi memory leak
}

int main() {
    memory_leak_example();
    // Memori yang dialokasikan dalam fungsi memory_leak_example() tidak pernah dibebaskan
    return 0;
}
```

Memori yang dialokasikan dan tidak dibebaskan (karena kebocoran memori) akan tetap terpakai **selama program tersebut berjalan**. Setelah program selesai atau dihentikan, sistem operasi biasanya akan membersihkan memori yang masih teralokasi. Jadi, memori tersebut hanya digunakan selama program aktif dan belum ditutup.

Berikut beberapa poin penting terkait penggunaan memori ini:

1. **Selama program berjalan**:
   - Memori yang dialokasikan dan tidak dibebaskan akan terus digunakan oleh program sampai program berakhir.
   - Setiap kali program mengalokasikan lebih banyak memori tanpa membebaskannya, memori yang tersedia di **RAM** (Random Access Memory) akan berkurang.

2. **Setelah program berakhir**:
   - Ketika program ditutup atau dihentikan, sistem operasi akan secara otomatis membebaskan semua memori yang dialokasikan oleh program tersebut, termasuk yang tidak dibebaskan secara eksplisit oleh programmer.
   
3. **Memori yang digunakan**:
   - **RAM** adalah tempat utama di mana memori dialokasikan oleh program. RAM digunakan karena aksesnya cepat dan efisien untuk operasi yang dilakukan oleh program. Jadi, saat sebuah program mengalokasikan memori (misalnya menggunakan `malloc()` di C atau `new` di C++), memori tersebut diambil dari RAM.
   - **Hard disk** biasanya tidak digunakan untuk alokasi memori program secara langsung, kecuali dalam kasus ketika RAM hampir habis, sistem operasi mungkin menggunakan **virtual memory** (yang melibatkan **paging** atau **swap memory**). Dalam hal ini, sebagian dari memori di RAM yang jarang digunakan dipindahkan sementara ke hard disk untuk memberi ruang di RAM. Ini akan menyebabkan penurunan kinerja karena kecepatan hard disk jauh lebih lambat dibanding RAM.
   
### Penjelasan Alur Penggunaan Memori:
1. Ketika program berjalan dan mengalokasikan memori, memori itu berasal dari RAM.
2. Jika memori tidak dibebaskan (terjadi memory leak), memori itu tetap dicadangkan di RAM hingga program ditutup.
3. Jika kebocoran memori besar dan terus terjadi, RAM bisa terisi penuh, dan kinerja sistem menurun karena memori yang tersedia semakin sedikit.
4. Jika RAM hampir habis, sistem operasi bisa mulai menggunakan swap (virtual memory) yang ada di hard disk, tetapi ini memperlambat kinerja aplikasi.

Jadi, selama program berjalan, kebocoran memori menghabiskan **RAM**, bukan hard disk (kecuali jika virtual memory digunakan saat RAM habis).

Ya, alokasi memori yang terus menerus tanpa dibebaskan dalam loop (seperti `while` loop) akan menyebabkan **memory leaks**. Setiap kali memori dialokasikan dan tidak dibebaskan, memori tersebut tetap terpakai selama program berjalan. Dalam kasus ini, program akan terus mengalokasikan memori tanpa henti, yang dapat menyebabkan kehabisan memori (RAM) dan mungkin membuat program atau sistem crash.

Berikut adalah contoh program dalam C yang menunjukkan bagaimana memory leak bisa terjadi dalam `while` loop:

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    while (1) {  // Loop terus menerus
        int* ptr = (int*)malloc(sizeof(int) * 1000);  // Alokasi memori untuk 1000 integer
        
        if (ptr == NULL) {
            printf("Memori tidak dapat dialokasikan\n");
            break;  // Jika memori tidak dapat dialokasikan, keluar dari loop
        }

        // Memori ini tidak pernah dibebaskan dengan free(ptr), menyebabkan memory leak
    }

    return 0;
}
```

### Penjelasan:
1. Program ini menggunakan loop `while (1)` yang berjalan tanpa henti.
2. Di dalam loop, memori sebesar 1000 integer dialokasikan menggunakan `malloc()`.
3. Memori yang dialokasikan tidak pernah dibebaskan menggunakan `free(ptr)`, sehingga menyebabkan kebocoran memori.
4. Karena program terus-menerus mengalokasikan memori, jumlah memori yang digunakan akan terus bertambah sampai memori sistem habis.

### Dampak:
- **Memory leak** akan terjadi karena alokasi memori yang berulang-ulang tanpa dibebaskan.
- Jika program ini terus berjalan, penggunaan RAM akan terus meningkat, dan jika memori habis, program mungkin crash atau sistem menjadi tidak responsif.


Mendeteksi **memory leaks** adalah langkah penting dalam memastikan bahwa program berjalan secara efisien dan tidak menghabiskan memori. Ada beberapa cara dan alat yang dapat digunakan untuk mendeteksi kebocoran memori, tergantung pada bahasa pemrograman yang digunakan. Berikut adalah beberapa metode umum:

### 1. **Menggunakan Debugger atau Profiling Tools**
   Alat-alat ini digunakan untuk menganalisis penggunaan memori selama eksekusi program dan mendeteksi kebocoran memori.

   - **Valgrind (untuk C/C++)**:
     Valgrind adalah alat populer untuk mendeteksi kebocoran memori di C dan C++. Ia memantau alokasi dan pembebasan memori, serta memberi laporan jika ada memori yang tidak dibebaskan.

     Cara penggunaannya:
     ```bash
     valgrind --leak-check=full ./nama_program
     ```

     Output dari Valgrind akan menunjukkan jika ada kebocoran memori beserta lokasi di mana memori dialokasikan tetapi tidak dibebaskan.

   - **AddressSanitizer (untuk C/C++)**:
     AddressSanitizer adalah alat yang digunakan dengan compiler untuk mendeteksi masalah alokasi memori. Anda dapat menggunakannya dengan menambahkan flag saat kompilasi:
     ```bash
     gcc -fsanitize=address -g -o nama_program nama_program.c
     ./nama_program
     ```

     Ini akan menghasilkan laporan saat program berjalan jika ada kebocoran memori.

   - **Dr. Memory**:
     Dr. Memory adalah alat deteksi kebocoran memori yang mirip dengan Valgrind, mendukung Windows dan Linux. Ini akan memberi laporan terperinci tentang penggunaan memori yang salah.

### 2. **Menggunakan Static Analysis Tools**
   Alat analisis statis dapat membantu mendeteksi potensi kebocoran memori tanpa perlu menjalankan program.

   - **Cppcheck (untuk C/C++)**:
     Cppcheck adalah alat analisis statis yang dapat digunakan untuk mendeteksi masalah kode, termasuk potensi kebocoran memori. Ini bekerja dengan menganalisis kode sumber Anda.

     Cara menjalankan:
     ```bash
     cppcheck --enable=all nama_program.c
     ```

### 3. **Menggunakan Tools di IDE**
   Banyak **Integrated Development Environments (IDE)** yang menyediakan alat deteksi kebocoran memori bawaan.

   - **Visual Studio (untuk C/C++)**:
     Visual Studio memiliki profiler memori bawaan yang dapat membantu mendeteksi kebocoran memori. Saat debugging, Anda dapat menggunakan fitur **Diagnostics Tools** untuk memantau penggunaan memori.
     1. Buka program di Visual Studio.
     2. Tekan `Ctrl + Alt + F2` untuk membuka **Diagnostics Tools**.
     3. Jalankan program dan periksa penggunaan memori dalam jendela diagnosa.

### 4. **Manual Checking dengan Logging**
   Anda juga dapat mendeteksi kebocoran memori dengan melakukan pelacakan manual terhadap setiap alokasi dan pembebasan memori.

   - **Menambahkan logging**:
     Dengan menambahkan pesan log setiap kali memori dialokasikan dan dibebaskan, Anda bisa memantau jika ada alokasi yang tidak diikuti oleh pembebasan.

     Contoh sederhana di C:
     ```c
     #include <stdio.h>
     #include <stdlib.h>

     void* my_malloc(size_t size) {
         void* ptr = malloc(size);
         if (ptr != NULL) {
             printf("Allocated %zu bytes at %p\n", size, ptr);
         }
         return ptr;
     }

     void my_free(void* ptr) {
         if (ptr != NULL) {
             printf("Freed memory at %p\n", ptr);
             free(ptr);
         }
     }

     int main() {
         int* arr = (int*)my_malloc(100 * sizeof(int));  // Alokasi memori
         my_free(arr);  // Membebaskan memori
         return 0;
     }
     ```

   Dalam contoh ini, setiap alokasi dan pembebasan memori dilacak melalui pesan log, yang bisa membantu memantau kebocoran memori.

### 5. **Menggunakan Monitoring Tools di Runtime**
   Anda bisa menggunakan alat monitoring memori selama runtime untuk memantau program Anda.

   - **top atau htop (Linux)**:
     Anda bisa memantau penggunaan memori program secara real-time dengan menggunakan `top` atau `htop`. Jika Anda melihat bahwa penggunaan memori terus bertambah secara signifikan tanpa batas, itu bisa menjadi indikasi kebocoran memori.

     Jalankan program Anda, lalu jalankan `top` atau `htop` di terminal:
     ```bash
     top
     ```

     Amati kolom `RES` dan `VIRT` yang menunjukkan memori yang digunakan oleh program.

### Rangkuman
- **Valgrind** dan **AddressSanitizer** adalah alat yang paling umum digunakan untuk mendeteksi kebocoran memori di C/C++.
- Analisis statis seperti **Cppcheck** dapat membantu menemukan masalah kode sebelum program dijalankan.
- IDE seperti **Visual Studio** dan alat runtime seperti **htop** bisa digunakan untuk memantau penggunaan memori secara real-time.
- Menambahkan logging manual dapat membantu melacak alokasi dan pembebasan memori.

Memahami dan menggunakan alat-alat ini bisa sangat membantu dalam menjaga kualitas dan performa program Anda dengan mencegah kebocoran memori.

**AddressSanitizer** (sering disingkat **ASan**) adalah alat deteksi bug memori dinamis yang dikembangkan oleh Google. Ini digunakan untuk mendeteksi berbagai jenis kesalahan terkait memori di C dan C++, termasuk:

- **Memory leaks** (kebocoran memori)
- **Buffer overflow** (akses memori di luar batas array)
- **Use-after-free** (mengakses memori setelah dibebaskan)
- **Double free** (membebaskan memori dua kali)
- **Stack buffer overflow** (akses di luar batas pada variabel lokal)
- **Dangling pointers** (pointer yang menunjuk ke memori yang telah dibebaskan)

### Cara Kerja AddressSanitizer
AddressSanitizer bekerja dengan menyisipkan kode tambahan ke dalam program yang dikompilasi. Ini memungkinkan deteksi penggunaan memori yang tidak sah selama runtime. Secara internal, ASan menggunakan area memori yang disebut **shadow memory**, yang menyimpan metadata tentang status blok memori program. Setiap kali ada akses ke memori, ASan memeriksa shadow memory untuk memastikan apakah akses tersebut sah.

### Kelebihan AddressSanitizer
1. **Cepat**: Meskipun AddressSanitizer menambahkan overhead performa, itu relatif cepat jika dibandingkan dengan alat deteksi memori lainnya seperti **Valgrind**.
2. **Mudah digunakan**: ASan terintegrasi dengan baik dengan GCC, Clang, dan banyak IDE modern, sehingga mudah digunakan.
3. **Laporan rinci**: Ketika AddressSanitizer mendeteksi masalah memori, ia memberikan laporan yang rinci tentang lokasi kesalahan, termasuk trace back dari fungsi yang menyebabkan kesalahan tersebut.
4. **Cross-platform**: ASan dapat digunakan di berbagai platform, termasuk Linux, macOS, dan Windows.

### Penggunaan AddressSanitizer
AddressSanitizer dapat digunakan dengan menambahkan flag kompilasi khusus saat mengompilasi program C atau C++. Berikut langkah-langkah menggunakan AddressSanitizer:

1. **Menggunakan AddressSanitizer dengan GCC atau Clang**:
   Anda dapat mengaktifkan AddressSanitizer dengan menambahkan flag `-fsanitize=address` ke compiler.

   Contoh dengan **GCC**:
   ```bash
   gcc -fsanitize=address -g -o nama_program nama_program.c
   ./nama_program
   ```

   Contoh dengan **Clang**:
   ```bash
   clang -fsanitize=address -g -o nama_program nama_program.c
   ./nama_program
   ```

   Flag `-g` menambahkan informasi debugging yang membantu untuk membuat pesan kesalahan lebih deskriptif.

2. **Menjalankan Program dengan AddressSanitizer**:
   Setelah program dikompilasi dengan AddressSanitizer, Anda menjalankan program seperti biasa. Jika AddressSanitizer mendeteksi masalah, ia akan memberikan pesan kesalahan dan laporan yang menunjukkan:
   - Jenis kesalahan (misalnya, **heap-buffer-overflow**, **use-after-free**, dll.).
   - Lokasi kode (fungsi dan baris kode) tempat kesalahan terjadi.
   - Stack trace yang berguna untuk debugging.

### Contoh Program yang Memicu AddressSanitizer

Berikut adalah contoh program C yang mengakses memori di luar batas (buffer overflow), dan AddressSanitizer akan mendeteksinya:

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arr = (int*)malloc(5 * sizeof(int));  // Alokasi memori untuk 5 integer

    // Akses di luar batas (buffer overflow)
    for (int i = 0; i <= 5; i++) {
        arr[i] = i * 10;  // Akses elemen ke-6 (out-of-bounds)
    }

    free(arr);  // Membebaskan memori
    return 0;
}
```

Saat dikompilasi dan dijalankan dengan AddressSanitizer:

```bash
gcc -fsanitize=address -g -o test test.c
./test
```

Output AddressSanitizer akan mendeteksi kesalahan:

```
=================================================================
==3152==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x602000000018 at pc 0x0000004009f1 bp 0x7fff5dbced70 sp 0x7fff5dbced68
WRITE of size 4 at 0x602000000018 thread T0
    #0 0x4009f0 in main test.c:8
    ...
0x602000000018 is located 0 bytes to the right of 20-byte region [0x602000000000,0x602000000014)
allocated by thread T0 here:
    #0 0x7f97b836f602 in malloc (/usr/lib/x86_64-linux-gnu/libasan.so.5+0x10f602)
    #1 0x4008d4 in main test.c:5
    ...
```

Laporan menunjukkan:
- **heap-buffer-overflow** terjadi saat program menulis ke memori di luar batas.
- Kesalahan terjadi pada baris ke-8 dalam kode (`arr[i] = i * 10;`).
- Memberikan stack trace yang membantu dalam debugging.

### Keterbatasan AddressSanitizer
1. **Overhead memori dan performa**: Meskipun AddressSanitizer lebih cepat daripada alat lain seperti Valgrind, penggunaan memori dan waktu eksekusi meningkat (biasanya sekitar 2-3 kali lebih banyak memori dan 2-5 kali lebih lambat).
2. **Terbatas untuk deteksi runtime**: AddressSanitizer bekerja pada saat program berjalan, jadi Anda perlu menjalankan program untuk menemukan masalah memori. Ini tidak menggantikan analisis statis seperti yang dilakukan oleh alat seperti **Cppcheck**.
3. **Tidak mendeteksi semua masalah memori**: Meskipun AddressSanitizer sangat efektif, ia tidak mendeteksi semua masalah memori, seperti race conditions dalam program multi-threaded. Untuk itu, alat lain seperti **ThreadSanitizer** mungkin diperlukan.

### Kesimpulan
AddressSanitizer adalah alat yang sangat kuat untuk mendeteksi masalah memori dinamis di C dan C++. Ini mudah digunakan, memberikan laporan yang mendetail, dan bekerja dengan baik pada runtime untuk menemukan berbagai jenis kesalahan memori. Bagi developer C dan C++, AddressSanitizer adalah salah satu alat debugging penting untuk memastikan program bebas dari kesalahan memori yang berpotensi merusak.

Dalam contoh ini, memori dialokasikan untuk menyimpan 10 integer, tetapi setelah penggunaannya, memori tersebut tidak dibebaskan dengan `free(ptr)`. Akibatnya, terjadi kebocoran memori. Jika fungsi ini dipanggil berulang kali dalam program yang lebih besar, maka akan terus terjadi kebocoran memori dan bisa menyebabkan kehabisan memori pada sistem.

### Contoh di kehidupan nyata:
Contoh kebocoran memori yang nyata bisa terjadi di aplikasi yang berjalan dalam waktu lama, seperti server web. Jika aplikasi server tidak secara benar membebaskan memori setelah setiap permintaan klien, kebocoran memori dapat terjadi dan membuat server crash setelah berjalan beberapa waktu.


# Memori Bersama (Shared Memory)

Dalam program paralel atau **concurrent programming**, memori bersama (**shared memory**) merujuk pada mekanisme di mana beberapa **thread** atau **proses** dapat mengakses memori yang sama untuk berbagi data. Ini memungkinkan komunikasi yang efisien antara unit-unit eksekusi (thread atau proses) dalam sebuah aplikasi. Namun, memori bersama juga membawa tantangan baru, terutama terkait dengan **race conditions** dan **deadlocks**.

## A. Mengapa Memori Bersama Penting
- **Efisiensi**: Memori bersama memungkinkan **pengaksesan data secara langsung** antara thread atau proses tanpa perlu mekanisme komunikasi yang mahal (seperti message passing).
- **Penghematan Waktu**: Karena semua thread dapat membaca atau menulis ke memori yang sama, tidak diperlukan salinan terpisah dari data. Ini menghemat waktu dan memori.
  
Namun, **akses paralel** ke memori bersama ini harus dikelola dengan hati-hati agar tidak menyebabkan masalah **konsistensi data**.

## B. Masalah Utama dalam Pengelolaan Memori Bersama
1. **Race Conditions**:
   - Race condition terjadi ketika dua atau lebih thread atau proses mengakses memori bersama secara bersamaan, dan hasil akhir bergantung pada urutan eksekusi.
   - Contoh race condition adalah ketika satu thread membaca nilai dari memori sementara thread lain menulis ke memori yang sama secara bersamaan, yang bisa menyebabkan hasil yang tidak diinginkan atau data korup.
   
2. **Deadlocks**:
   - Deadlock terjadi ketika dua atau lebih thread atau proses saling menunggu sumber daya yang dipegang oleh satu sama lain, sehingga tidak ada yang bisa melanjutkan eksekusi.
   - Dalam konteks memori bersama, deadlock bisa terjadi jika dua thread mencoba mengunci dua sumber daya berbeda, tetapi saling menunggu pelepasan kunci dari satu sama lain.

## C. Thread Safety dan Manajemen Akses Memori
Untuk menghindari race conditions dan deadlocks dalam memori bersama, penting untuk menerapkan teknik **thread safety**. Thread safety memastikan bahwa beberapa thread dapat mengakses memori bersama tanpa menyebabkan inkonsistensi data atau konflik.

Beberapa metode umum untuk memastikan thread safety dalam penggunaan memori bersama:

1. **Locks (Penguncian)**:
   - Penguncian adalah mekanisme untuk memastikan bahwa hanya satu thread yang dapat mengakses memori bersama pada suatu waktu.
   - **Mutex (Mutual Exclusion)**: Salah satu alat penguncian paling umum. Mutex memastikan bahwa hanya satu thread yang bisa mengunci dan mengakses memori bersama, sementara thread lain harus menunggu hingga kunci dibebaskan.
   
   Contoh penggunaan mutex di C (dengan pthreads):

   ```c
   pthread_mutex_t lock;  // Definisi mutex

   void* thread_function(void* arg) {
       pthread_mutex_lock(&lock);  // Mengunci
       // Akses memori bersama di sini
       pthread_mutex_unlock(&lock);  // Membuka kunci
       return NULL;
   }

   int main() {
       pthread_mutex_init(&lock, NULL);  // Inisialisasi mutex
       
       // Membuat dan menjalankan thread
       pthread_t thread1, thread2;
       pthread_create(&thread1, NULL, thread_function, NULL);
       pthread_create(&thread2, NULL, thread_function, NULL);
       
       // Bergabung dengan thread
       pthread_join(thread1, NULL);
       pthread_join(thread2, NULL);
       
       pthread_mutex_destroy(&lock);  // Menghancurkan mutex setelah digunakan
       return 0;
   }
   ```

2. **Semaphore**:
   - Semaphore mirip dengan mutex, tetapi bisa mengontrol akses oleh beberapa thread pada waktu yang sama. Sebuah semaphore memiliki hitungan (count), yang menunjukkan berapa banyak thread yang dapat mengakses memori bersama secara bersamaan.
   - Contoh penggunaan semaphore bisa ditemukan dalam manajemen akses ke sumber daya terbatas, seperti buffer berbatas dalam sistem produsen-konsumen.

3. **Atomic Operations**:
   - Operasi **atomik** adalah operasi yang tidak dapat dipecah-pecah atau diinterupsi oleh thread lain. Operasi ini memastikan bahwa tindakan seperti penambahan atau pengurangan variabel dilakukan dengan aman oleh beberapa thread tanpa menyebabkan race condition.
   - Dalam C++, header `<atomic>` menyediakan tipe data atomik yang aman digunakan dalam lingkungan multi-threading, seperti `std::atomic<int>`.

   Contoh:

   ```cpp
   #include <atomic>
   #include <thread>

   std::atomic<int> counter(0);

   void increment() {
       for (int i = 0; i < 1000; ++i) {
           counter++;
       }
   }

   int main() {
       std::thread t1(increment);
       std::thread t2(increment);

       t1.join();
       t2.join();

       std::cout << "Final counter value: " << counter << std::endl;
       return 0;
   }
   ```

4. **Read-Write Locks**:
   - **Read-Write locks** memungkinkan beberapa thread untuk membaca memori bersama secara bersamaan, tetapi membatasi akses tulis hanya untuk satu thread pada satu waktu. Ini berguna ketika ada lebih banyak pembacaan daripada penulisan di memori bersama.
   
   Dalam pthreads, ini bisa dilakukan dengan `pthread_rwlock_t`.

## D. Deadlock Prevention
Deadlocks dapat dicegah dengan beberapa strategi:
1. **Mengunci sumber daya dalam urutan yang konsisten**: Jika semua thread mengunci sumber daya dalam urutan yang sama, maka deadlock bisa dihindari.
2. **Menggunakan timeout pada penguncian**: Dengan menerapkan batas waktu untuk penguncian, thread bisa keluar dari kondisi deadlock jika kunci tidak bisa diperoleh dalam jangka waktu tertentu.
3. **Menggunakan algoritma deadlock detection**: Dalam beberapa kasus, sistem dapat mendeteksi kondisi deadlock dan mencoba menyelesaikannya dengan cara tertentu (misalnya, mematikan satu thread atau membebaskan sumber daya).

## Kesimpulan
Memori bersama adalah konsep penting dalam program paralel atau concurrent, tetapi harus dikelola dengan hati-hati untuk menghindari **race conditions** dan **deadlocks**. Penggunaan mekanisme seperti **mutex**, **semaphore**, **atomic operations**, dan **read-write locks** sangat penting dalam memastikan **thread safety** dan kinerja aplikasi yang andal dan efisien.
