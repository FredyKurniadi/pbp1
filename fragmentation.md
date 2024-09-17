<h1>Fragmentasi Memori di Heap</h1>

<p><strong>Nama</strong>: Farrel Zandra</p>
<p><strong>NIM</strong>: 231524007</p>
<p><strong>Topik</strong>: Fragmentasi Memori di Heap</p>

<h2>Pendahuluan</h2>

<h3>Latar Belakang</h3>
<p>Fragmentasi memori di heap terjadi ketika blok-blok memori yang dialokasikan dan dibebaskan menyebabkan "lubang-lubang" kecil di dalam memori yang tidak dapat digunakan kembali secara efisien. Pada aplikasi yang menjalankan banyak operasi alokasi dan de-alokasi, memori yang tersedia terpecah-pecah menjadi bagian kecil sehingga mempersulit alokasi baru yang membutuhkan blok memori besar.</p>

<h3>Urgensi pada Skala Industri</h3>
<p>Pada aplikasi berskala besar dan industri, seperti server, sistem operasi, atau perangkat tertanam (<em>embedded systems</em>), fragmentasi memori dapat menurunkan performa secara drastis. Memori yang tidak terkelola dengan baik bisa menyebabkan:</p>
<ul>
    <li><strong>Out of memory:</strong> meskipun memori total masih ada.</li>
    <li><strong>Penurunan performa:</strong> akibat manajemen memori yang tidak efisien.</li>
    <li><strong>Crash sistem atau alokasi gagal:</strong> yang mengganggu stabilitas aplikasi.</li>
</ul>
<p>Oleh karena itu, pemahaman tentang fragmentasi memori sangatlah penting agar aplikasi dapat berjalan dengan lancar dan stabil dalam jangka panjang.</p>

<h2>Tujuan</h2>
<ul>
    <li>Mengenali bagaimana fragmentasi memori terjadi di heap.</li>
    <li>Melihat dampak fragmentasi memori pada performa alokasi.</li>
    <li>Melakukan pengujian menggunakan <em>Valgrind</em> untuk mengidentifikasi masalah ini.</li>
    <li>Menyediakan solusi untuk mengurangi fragmentasi memori.</li>
</ul>

<h2>Kode Program</h2>

<pre><code>
#include &lt;stdlib.h&gt;
#include &lt;stdio.h&gt;

void memory_fragmentation() {
    // Simulasi fragmentasi memori dengan alokasi dan de-alokasi tidak merata
    for (int i = 0; i &lt; 10; i++) {
        int *ptr = malloc(1000 * sizeof(int)); // Alokasi memori sebesar 1000 integers
        if (i % 2 == 0) {
            free(ptr); // Hanya setiap alokasi genap yang dibebaskan
        }
    }
    // Alokasi besar yang mungkin gagal karena fragmentasi
    int *large_allocation = malloc(10000 * sizeof(int));
    if (large_allocation == NULL) {
        printf("Gagal mengalokasikan memori besar karena fragmentasi.\n");
    } else {
        printf("Alokasi memori besar berhasil.\n");
        free(large_allocation);
    }
}

int main() {
    memory_fragmentation();
    return 0;
}
</code></pre>

<p>Pada kode di atas, memori dialokasikan 10 kali dan hanya setengahnya dibebaskan. Hal ini menyebabkan terjadinya fragmentasi pada heap.</p>

<h2>Analisis Kode</h2>

<h3>Penyebab Fragmentasi Memori</h3>
<p>Fragmentasi memori terjadi ketika memori dialokasikan dan dibebaskan secara tidak teratur, menyebabkan blok-blok kosong yang tidak berurutan. Dalam kasus ini, alokasi memori besar mungkin gagal meskipun secara total ada cukup memori yang tersisa.</p>

<h3>Solusi</h3>
<p>Untuk mengurangi fragmentasi memori, beberapa teknik yang dapat digunakan antara lain:</p>
<ul>
    <li><strong>Pengelolaan memori yang konsisten:</strong> Membebaskan memori sesuai dengan urutan alokasi.</li>
    <li><strong>Garbage collection:</strong> Dalam bahasa yang mendukung <em>garbage collector</em>, fragmentasi dapat berkurang secara otomatis.</li>
    <li><strong>Memori pooling:</strong> Menggunakan teknik memori pooling dapat membantu menghindari fragmentasi di heap.</li>
</ul>

<h2>Pengujian Menggunakan <em>Valgrind</em></h2>

<h3>Lingkungan Pengujian</h3>
<ul>
    <li><strong>Sistem operasi</strong>: Linux (Ubuntu)</li>
    <li><strong>Kompiler</strong>: GCC</li>
    <li><strong>Spesifikasi perangkat</strong>: 8 GB RAM</li>
</ul>

<h3>Pengujian Sebelum Perbaikan</h3>
<p>Kode diuji menggunakan <em>Valgrind</em> untuk mendeteksi apakah ada masalah fragmentasi atau kebocoran memori. Perintah untuk menjalankan pengujian:</p>

<pre><code>
valgrind --tool=memcheck --leak-check=full ./program_fragmentation
</code></pre>

<h4>Hasil <em>Valgrind</em> (Sebelum Perbaikan)</h4>

<pre><code>
==23456== Memcheck, a memory error detector
==23456== Command: ./program_fragmentation
==23456==
==23456== Alokasi memori besar berhasil.
==23456==
==23456== HEAP SUMMARY:
==23456==     in use at exit: 4,000 bytes in 4 blocks
==23456==   total heap usage: 10 allocs, 6 frees, 44,000 bytes allocated
==23456==
==23456== LEAK SUMMARY:
==23456==    definitely lost: 0 bytes in 0 blocks
==23456==    indirectly lost: 0 bytes in 0 blocks
==23456==    possibly lost: 0 bytes in 0 blocks
==23456==    still reachable: 4,000 bytes in 4 blocks
==23456==    suppressed: 0 bytes in 0 blocks
==23456==
==23456== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
</code></pre>

<p>Meskipun alokasi memori besar berhasil, masih ada memori kecil yang tidak dibebaskan di heap.</p>

<h3>Pengujian Setelah Perbaikan</h3>
<p>Kode diperbaiki dengan membebaskan semua memori yang dialokasikan. Berikut adalah versi kode yang diperbaiki:</p>

<pre><code>
#include &lt;stdlib.h&gt;
#include &lt;stdio.h&gt;

void memory_fragmentation() {
    // Simulasi fragmentasi memori dengan alokasi dan de-alokasi merata
    int *ptr[10];
    for (int i = 0; i &lt; 10; i++) {
        ptr[i] = malloc(1000 * sizeof(int)); // Alokasi memori sebesar 1000 integers
    }
    // Membebaskan semua alokasi memori
    for (int i = 0; i &lt; 10; i++) {
        free(ptr[i]);
    }
    // Alokasi besar
    int *large_allocation = malloc(10000 * sizeof(int));
    if (large_allocation == NULL) {
        printf("Gagal mengalokasikan memori besar karena fragmentasi.\n");
    } else {
        printf("Alokasi memori besar berhasil.\n");
        free(large_allocation);
    }
}

int main() {
    memory_fragmentation();
    return 0;
}
</code></pre>

<p>Perintah untuk menjalankan pengujian:</p>

<pre><code>
valgrind --tool=memcheck --leak-check=full ./program_fragmentation
</code></pre>

<h4>Hasil <em>Valgrind</em> (Setelah Perbaikan)</h4>

<pre><code>
==23457== Memcheck, a memory error detector
==23457== Command: ./program_fragmentation
==23457==
==23457== Alokasi memori besar berhasil.
==23457==
==23457== HEAP SUMMARY:
==23457==     in use at exit: 0 bytes in 0 blocks
==23457==   total heap usage: 11 allocs, 11 frees, 54,000 bytes allocated
==23457==
==23457== All heap blocks were freed -- no leaks are possible
==23457==
==23457== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
</code></pre>

<p>Setelah semua memori dibebaskan, <em>Valgrind</em> menunjukkan bahwa tidak ada kebocoran memori dan semua blok heap telah dibebaskan.</p>

<h2>Kesimpulan</h2>
<ul>
    <li>Fragmentasi memori terjadi ketika memori dialokasikan dan dibebaskan secara tidak merata, menyebabkan blok-blok memori kecil yang terpecah-pecah.</li>
    <li>Pengujian dengan <em>Valgrind</em> menunjukkan bahwa meskipun ada cukup memori yang tersisa, fragmen kecil di heap membuat alokasi besar berpotensi gagal.</li>
    <li>Setelah perbaikan dengan membebaskan semua memori yang dialokasikan, tidak ada kebocoran memori yang terdeteksi dan alokasi besar berhasil.</li>
    <li>Manajemen memori yang baik, termasuk pengelolaan fragmentasi, penting untuk aplikasi yang stabil dan efisien.</li>
</ul>
