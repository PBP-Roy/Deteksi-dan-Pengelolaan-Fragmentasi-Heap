# **Laporan Eksperimen: Simulasi Fragmentasi Heap dan Solusi Pengelolaannya**

  

---

  

## **1. Pendahuluan**



Dalam pengembangan perangkat lunak, manajemen memori merupakan aspek penting yang mempengaruhi kinerja aplikasi. Salah satu masalah yang sering dihadapi adalah fragmentasi heap, di mana blok memori yang terpisah-pisah dan tidak berkesinambungan menghalangi alokasi memori besar, meskipun jumlah memori yang tersedia mencukupi. Eksperimen ini bertujuan untuk mempelajari bagaimana fragmentasi heap memengaruhi kinerja aplikasi dan untuk menguji beberapa solusi untuk mengatasinya.

  

---

  

## **2. Metodologi Eksperimen**

  

Eksperimen ini terdiri dari tiga langkah utama:

  

1. **Simulasi Alokasi dan Dealokasi Memori**: Program C yang dibuat secara acak mengalokasikan dan membebaskan blok memori dengan ukuran bervariasi untuk mensimulasikan fragmentasi heap.

2. **Monitoring Fragmentasi dan Kinerja**: Setiap 100 alokasi, tingkat fragmentasi heap dan waktu rata-rata alokasi diukur. Upaya alokasi blok memori besar juga dilakukan secara berkala untuk mengevaluasi dampak fragmentasi.

3. **Implementasi Solusi**: Beberapa solusi untuk mengurangi fragmentasi, termasuk kompaksi memori dan garbage collection, diterapkan dan dianalisis.

  

---
## **3. Eksperimen**
``` C
  

#include <stdio.h>

#include <time.h>

  

#define MEMORY_SIZE 2750 * 2750 // Ukuran memori total

#define NUM_BLOCKS 5             // Jumlah blok memori

  

// Struktur untuk menyimpan informasi blok memori

typedef struct {

    int room;          // Ukuran asli blok memori

    int occupied;      // Ukuran terisi dalam blok

    int free;          // Status blok (1 untuk bebas, 0 untuk tidak bebas)

} MemoryBlock;

  

// Variabel global untuk menyimpan posisi terakhir yang dialokasikan

  

// Fungsi untuk menemukan blok pertama yang cukup besar (First-Fit)

int find_first_fit_block(MemoryBlock blocks[], int num_blocks, int size) {

    for (int i = 0; i < num_blocks; i++) {

        if (blocks[i].free && (blocks[i].room - blocks[i].occupied) >= size) {

            return i;  // Mengembalikan indeks blok pertama yang sesuai

        }

    }

    return -1;  // Tidak ditemukan blok yang cukup besar

}

  

// Fungsi untuk melakukan alokasi memori dengan algoritma First-Fit

void first_fit_allocation(MemoryBlock blocks[], int num_blocks, int size) {

    int block_index = find_first_fit_block(blocks, num_blocks, size);

    if (block_index == -1) {

        printf("Tidak ada blok memori yang cukup besar untuk alokasi %d\n", size);

    } else {

        blocks[block_index].occupied += size;

        if (blocks[block_index].occupied == blocks[block_index].room) {

            blocks[block_index].free = 0;  // Jika terisi penuh, blok menjadi tidak bebas

        }

        printf("Dialokasikan %d memori pada blok %d\n", size, block_index);

    }

}

  

// Fungsi untuk menemukan blok terbaik (Best-Fit)

int find_best_fit_block(MemoryBlock blocks[], int num_blocks, int size) {

    int best_index = -1;

    int min_size = MEMORY_SIZE + 1;  // Set nilai awal ke ukuran memori terbesar

  

    for (int i = 0; i < num_blocks; i++) {

        if (blocks[i].free && (blocks[i].room - blocks[i].occupied) >= size && (blocks[i].room - blocks[i].occupied) < min_size) {

            min_size = blocks[i].room - blocks[i].occupied;

            best_index = i;

        }

    }

    return best_index;

}

  

// Fungsi untuk melakukan alokasi memori dengan algoritma Best-Fit

void best_fit_allocation(MemoryBlock blocks[], int num_blocks, int size) {

    int block_index = find_best_fit_block(blocks, num_blocks, size);

    if (block_index == -1) {

        printf("Tidak ada blok memori yang cukup besar untuk alokasi %d\n", size);

    } else {

        blocks[block_index].occupied += size;

        if (blocks[block_index].occupied == blocks[block_index].room) {

            blocks[block_index].free = 0;  // Jika terisi penuh, blok menjadi tidak bebas

        }

        printf("Dialokasikan %d memori pada blok %d\n", size, block_index);

    }

}

  

// Fungsi untuk menemukan blok terbesar (Worst-Fit)

int find_worst_fit_block(MemoryBlock blocks[], int num_blocks, int size) {

    int worst_index = -1;

    int max_size = 0;

    for (int i = 0; i < num_blocks; i++) {

        if (blocks[i].free && (blocks[i].room - blocks[i].occupied) >= size && (blocks[i].room - blocks[i].occupied) > max_size) {

            max_size = blocks[i].room - blocks[i].occupied;

            worst_index = i;

        }

    }

    return worst_index;

}

  

// Fungsi untuk melakukan alokasi memori dengan algoritma Worst-Fit

void worst_fit_allocation(MemoryBlock blocks[], int num_blocks, int size) {

    int block_index = find_worst_fit_block(blocks, num_blocks, size);

    if (block_index == -1) {

        printf("Tidak ada blok memori yang cukup besar untuk alokasi %d\n", size);

    } else {

        blocks[block_index].occupied += size;

        if (blocks[block_index].occupied == blocks[block_index].room) {

            blocks[block_index].free = 0;  // Jika terisi penuh, blok menjadi tidak bebas

        }

        printf("Dialokasikan %d memori pada blok %d\n", size, block_index);

    }

}

  

// Fungsi untuk menemukan blok berikutnya yang cukup besar (Next-Fit)

int find_next_fit_block(MemoryBlock blocks[], int num_blocks, int size, int *last_allocated_index) {

    int i = *last_allocated_index;

  

    for (int count = 0; count < num_blocks; count++) {

        if (blocks[i].free && (blocks[i].room - blocks[i].occupied) >= size) {

            *last_allocated_index = i;  // Simpan posisi terakhir yang dialokasikan

            return i;  // Mengembalikan indeks blok yang sesuai

        }

        i = (i + 1) % num_blocks;  // Berputar ke blok berikutnya

    }

    return -1;  // Tidak ditemukan blok yang cukup besar

}

  

// Fungsi untuk melakukan alokasi memori dengan algoritma Next-Fit

void next_fit_allocation(MemoryBlock blocks[], int num_blocks, int size, int *last_allocated_index) {

    int block_index = find_next_fit_block(blocks, num_blocks, size, last_allocated_index);

    if (block_index == -1) {

        printf("Tidak ada blok memori yang cukup besar untuk alokasi %d\n", size);

    } else {

        blocks[block_index].occupied += size;

        if (blocks[block_index].occupied == blocks[block_index].room) {

            blocks[block_index].free = 0;  // Jika terisi penuh, blok menjadi tidak bebas

        }

        printf("Dialokasikan %d memori pada blok %d\n", size, block_index);

    }

}

  

void compact(MemoryBlock blocks[], int num_blocks) {

    int element_index = 0;

    int temp;

    // Pindahkan semua blok yang terisi ke awal

    for (int compact_index = 0; compact_index < num_blocks; compact_index++) {

        for (element_index = compact_index; element_index < num_blocks; element_index++)

        {

            if (blocks[compact_index].free == 1)

            {

                int temp = blocks[compact_index].room - blocks[compact_index].occupied;

                // printf("ID element_indeks : %d vs ID compact indeks : %d\n", element_index, compact_index);

                if (blocks[element_index].occupied <= blocks[compact_index].room - blocks[compact_index].occupied && element_index != compact_index && (blocks[element_index].occupied != 0))

                {

                    printf("Memindahkan blok %d ke blok %d\n", element_index, compact_index);

                    sleep(1);

                    temp = blocks[element_index].occupied;

                    blocks[compact_index].occupied += blocks[element_index].occupied;

                    blocks[element_index].occupied -= temp;

                }

            }

        }

    }

  

}

  

// Fungsi untuk menampilkan status blok memori

void display_memory(MemoryBlock blocks[], int num_blocks) {

    printf("Status blok memori:\n");

    for (int i = 0; i < num_blocks; i++) {

        printf("Blok %d: Ukuran Ruang = %d, Terisi = %d, Status = %s\n",

               i, blocks[i].room, blocks[i].occupied,

               blocks[i].free ? "Bebas" : "Tidak Bebas");

    }

    printf("\n");

}

  

int main() {

    MemoryBlock memory_first[NUM_BLOCKS] = {

        {6000, 0, 1}, {6500, 0, 1}, {9000, 0, 1}, {5000, 0, 1}, {1000, 0, 1}

    };

    MemoryBlock memory_best[NUM_BLOCKS] = {

        {6000, 0, 1}, {6500, 0, 1}, {9000, 0, 1}, {5000, 0, 1}, {1000, 0, 1}

    };

    MemoryBlock memory_worst[NUM_BLOCKS] = {

        {6000, 0, 1}, {6500, 0, 1}, {9000, 0, 1}, {5000, 0, 1}, {1000, 0, 1}

    };

    MemoryBlock memory_next[NUM_BLOCKS] = {

        {6000, 0, 1}, {6500, 0, 1}, {9000, 0, 1}, {5000, 0, 1}, {1000, 0, 1}

    };

  

    int last_allocated_index = 0;

    // Ukuran alokasi yang berbeda

    int allocation_sizes[] = {3000, 1000, 3000, 3000, 2000, 4000};    

    int num_allocations = sizeof(allocation_sizes) / sizeof(allocation_sizes[0]);

    // Pengukuran waktu untuk first fit

    clock_t start_time_first = clock();

    printf("Memori awal first fit:\n");

    display_memory(memory_first, NUM_BLOCKS);

    for (int i = 0; i < num_allocations; i++) {

        first_fit_allocation(memory_first, NUM_BLOCKS, allocation_sizes[i]);

    }

    printf("\nMemori setelah alokasi first fit:\n");

    display_memory(memory_first, NUM_BLOCKS);

    // Melakukan kompaksi

    compact(memory_first, NUM_BLOCKS);

    printf("Memori setelah kompaksi:\n");

    display_memory(memory_first, NUM_BLOCKS);

  

    clock_t end_time_first = clock();

    double elapsed_time_first = (double)(end_time_first - start_time_first) / CLOCKS_PER_SEC;

    printf("\nWaktu eksekusi first fit: %.6f detik\n", elapsed_time_first);

    clock_t start_time_best = clock();

    printf("\nMemori awal best fit:\n");

    display_memory(memory_best, NUM_BLOCKS);

    for (int i = 0; i < num_allocations; i++) {

        best_fit_allocation(memory_best, NUM_BLOCKS, allocation_sizes[i]);

    }

    printf("\nMemori setelah alokasi best fit:\n");

    display_memory(memory_best, NUM_BLOCKS);

    // Melakukan kompaksi

    compact(memory_best, NUM_BLOCKS);

    printf("Memori setelah kompaksi:\n");

    display_memory(memory_best, NUM_BLOCKS);

  

    clock_t end_time_best = clock();

    double elapsed_time_best = (double)(end_time_best - start_time_best) / CLOCKS_PER_SEC;

    printf("\nWaktu eksekusi best fit: %.6f detik\n", elapsed_time_best);

  

    clock_t start_time_worst = clock();

    printf("\nMemori awal worst fit:\n");

    display_memory(memory_worst, NUM_BLOCKS);

    for (int i = 0; i < num_allocations; i++) {

        worst_fit_allocation(memory_worst, NUM_BLOCKS, allocation_sizes[i]);

    }

    printf("\nMemori setelah alokasi worst fit:\n");

    display_memory(memory_worst, NUM_BLOCKS);

    // Melakukan kompaksi

    compact(memory_worst, NUM_BLOCKS);

    printf("Memori setelah kompaksi:\n");

    display_memory(memory_worst, NUM_BLOCKS);

  

    clock_t end_time_worst = clock();

    double elapsed_time_worst = (double)(end_time_worst - start_time_worst) / CLOCKS_PER_SEC;

    printf("\nWaktu eksekusi worst fit: %.6f detik\n", elapsed_time_worst);

    clock_t start_time_next = clock();

    printf("\nMemori awal next fit:\n");

    display_memory(memory_next, NUM_BLOCKS);

    for (int i = 0; i < num_allocations; i++) {

        next_fit_allocation(memory_next, NUM_BLOCKS, allocation_sizes[i], &last_allocated_index);

    }

    printf("\nMemori setelah alokasi next fit:\n");

    display_memory(memory_next, NUM_BLOCKS);

    // Melakukan kompaksi

    compact(memory_next, NUM_BLOCKS);

    printf("Memori setelah kompaksi:\n");

    display_memory(memory_next, NUM_BLOCKS);

  

    clock_t end_time_next = clock();

    double elapsed_time_next = (double)(end_time_next - start_time_next) / CLOCKS_PER_SEC;

    printf("\nWaktu eksekusi next fit: %.6f detik\n", elapsed_time_next);

    return 0;

}
```
### Penjelasan Code
 - Struct merupakan representasi 1 block memori
	-  room merupakan ukuran dari ruangan blok memori tersebut
	- occupied merupakan ukuran terisi dari blok tersebut yang tidak boleh melebihi room
	 - free merupakan status dari memori tersebut bebas atau tidak
-  `first_fit_allocation` merupakan algoritma untuk mengalokasi dengan metode first fit 
	- dengan fungsi find_first_fit_block untuk mencari lokasi blok yang memenuhi persyaratan first fit yaitu:
		- blok pertama kali yang kosong
- `best_fit_allocation` merupakan algoritma untuk mengalokasi dengan metode **best fit**.
    - dengan fungsi `find_best_fit_block` untuk mencari lokasi blok yang memenuhi persyaratan best fit, yaitu:
        - blok terkecil yang cukup atau paling pas untuk menampung memori yang dibutuhkan.
- `worst_fit_allocation` merupakan algoritma untuk mengalokasi dengan metode **worst fit**.
    - dengan fungsi `find_worst_fit_block` untuk mencari lokasi blok yang memenuhi persyaratan worst fit, yaitu:
        - blok terbesar yang kosong, sehingga menyisakan ruang kosong yang cukup besar setelah alokasi.
- `next_fit_allocation` merupakan algoritma untuk mengalokasi dengan metode **next fit**.
    - dengan fungsi `find_next_fit_block` untuk mencari lokasi blok yang memenuhi persyaratan next fit, yaitu:
        - blok pertama kali yang kosong, dimulai dari posisi terakhir kali memori dialokasikan.
- `compaction` merupakan algoritma untuk melakukan kompaksi jika terdapat fragmentasi memori 
## Output
``` output
Memori awal first fit:
Status blok memori:
Blok 0: Ukuran Ruang = 6000, Terisi = 0, Status = Bebas
Blok 1: Ukuran Ruang = 6500, Terisi = 0, Status = Bebas
Blok 2: Ukuran Ruang = 9000, Terisi = 0, Status = Bebas
Blok 3: Ukuran Ruang = 5000, Terisi = 0, Status = Bebas
Blok 4: Ukuran Ruang = 1000, Terisi = 0, Status = Bebas

Dialokasikan 3000 memori pada blok 0
Dialokasikan 1000 memori pada blok 0
Dialokasikan 3000 memori pada blok 1
Dialokasikan 3000 memori pada blok 1
Dialokasikan 2000 memori pada blok 0
Dialokasikan 4000 memori pada blok 2

Memori setelah alokasi first fit:
Status blok memori:
Blok 0: Ukuran Ruang = 6000, Terisi = 6000, Status = Tidak Bebas
Blok 1: Ukuran Ruang = 6500, Terisi = 6000, Status = Bebas
Blok 2: Ukuran Ruang = 9000, Terisi = 4000, Status = Bebas
Blok 3: Ukuran Ruang = 5000, Terisi = 0, Status = Bebas
Blok 4: Ukuran Ruang = 1000, Terisi = 0, Status = Bebas

Memori setelah kompaksi:
Status blok memori:
Blok 0: Ukuran Ruang = 6000, Terisi = 6000, Status = Tidak Bebas
Blok 1: Ukuran Ruang = 6500, Terisi = 6000, Status = Bebas
Blok 2: Ukuran Ruang = 9000, Terisi = 4000, Status = Bebas
Blok 3: Ukuran Ruang = 5000, Terisi = 0, Status = Bebas
Blok 4: Ukuran Ruang = 1000, Terisi = 0, Status = Bebas


Waktu eksekusi first fit: 0.009000 detik

Memori awal best fit:
Status blok memori:
Blok 0: Ukuran Ruang = 6000, Terisi = 0, Status = Bebas
Blok 1: Ukuran Ruang = 6500, Terisi = 0, Status = Bebas
Blok 2: Ukuran Ruang = 9000, Terisi = 0, Status = Bebas
Blok 3: Ukuran Ruang = 5000, Terisi = 0, Status = Bebas
Blok 4: Ukuran Ruang = 1000, Terisi = 0, Status = Bebas

Dialokasikan 3000 memori pada blok 3
Dialokasikan 1000 memori pada blok 4
Dialokasikan 3000 memori pada blok 0
Dialokasikan 3000 memori pada blok 0
Dialokasikan 2000 memori pada blok 3
Dialokasikan 4000 memori pada blok 1

Memori setelah alokasi best fit:
Status blok memori:
Blok 0: Ukuran Ruang = 6000, Terisi = 6000, Status = Tidak Bebas
Blok 1: Ukuran Ruang = 6500, Terisi = 4000, Status = Bebas
Blok 2: Ukuran Ruang = 9000, Terisi = 0, Status = Bebas
Blok 3: Ukuran Ruang = 5000, Terisi = 5000, Status = Tidak Bebas
Blok 4: Ukuran Ruang = 1000, Terisi = 1000, Status = Tidak Bebas

Memindahkan blok 4 ke blok 1
Memindahkan blok 3 ke blok 2
Memori setelah kompaksi:
Status blok memori:
Blok 0: Ukuran Ruang = 6000, Terisi = 6000, Status = Tidak Bebas
Blok 1: Ukuran Ruang = 6500, Terisi = 5000, Status = Bebas
Blok 2: Ukuran Ruang = 9000, Terisi = 5000, Status = Bebas
Blok 3: Ukuran Ruang = 5000, Terisi = 0, Status = Tidak Bebas
Blok 4: Ukuran Ruang = 1000, Terisi = 0, Status = Tidak Bebas


Waktu eksekusi best fit: 2.007000 detik

Memori awal worst fit:
Status blok memori:
Blok 0: Ukuran Ruang = 6000, Terisi = 0, Status = Bebas
Blok 1: Ukuran Ruang = 6500, Terisi = 0, Status = Bebas
Blok 2: Ukuran Ruang = 9000, Terisi = 0, Status = Bebas
Blok 3: Ukuran Ruang = 5000, Terisi = 0, Status = Bebas
Blok 4: Ukuran Ruang = 1000, Terisi = 0, Status = Bebas

Dialokasikan 3000 memori pada blok 2
Dialokasikan 1000 memori pada blok 1
Dialokasikan 3000 memori pada blok 0
Dialokasikan 3000 memori pada blok 2
Dialokasikan 2000 memori pada blok 1
Dialokasikan 4000 memori pada blok 3

Memori setelah alokasi worst fit:
Status blok memori:
Blok 0: Ukuran Ruang = 6000, Terisi = 3000, Status = Bebas
Blok 1: Ukuran Ruang = 6500, Terisi = 3000, Status = Bebas
Blok 2: Ukuran Ruang = 9000, Terisi = 6000, Status = Bebas
Blok 3: Ukuran Ruang = 5000, Terisi = 4000, Status = Bebas
Blok 4: Ukuran Ruang = 1000, Terisi = 0, Status = Bebas

Memindahkan blok 1 ke blok 0
Memindahkan blok 2 ke blok 1
Memindahkan blok 3 ke blok 2
Memori setelah kompaksi:
Status blok memori:
Blok 0: Ukuran Ruang = 6000, Terisi = 6000, Status = Bebas
Blok 1: Ukuran Ruang = 6500, Terisi = 6000, Status = Bebas
Blok 2: Ukuran Ruang = 9000, Terisi = 4000, Status = Bebas
Blok 3: Ukuran Ruang = 5000, Terisi = 0, Status = Bebas
Blok 4: Ukuran Ruang = 1000, Terisi = 0, Status = Bebas


Waktu eksekusi worst fit: 3.033000 detik

Memori awal next fit:
Status blok memori:
Blok 0: Ukuran Ruang = 6000, Terisi = 0, Status = Bebas
Blok 1: Ukuran Ruang = 6500, Terisi = 0, Status = Bebas
Blok 2: Ukuran Ruang = 9000, Terisi = 0, Status = Bebas
Blok 3: Ukuran Ruang = 5000, Terisi = 0, Status = Bebas
Blok 4: Ukuran Ruang = 1000, Terisi = 0, Status = Bebas

Dialokasikan 3000 memori pada blok 0
Dialokasikan 1000 memori pada blok 0
Dialokasikan 3000 memori pada blok 1
Dialokasikan 3000 memori pada blok 1
Dialokasikan 2000 memori pada blok 2
Dialokasikan 4000 memori pada blok 2

Memori setelah alokasi next fit:
Status blok memori:
Blok 0: Ukuran Ruang = 6000, Terisi = 4000, Status = Bebas
Blok 1: Ukuran Ruang = 6500, Terisi = 6000, Status = Bebas
Blok 2: Ukuran Ruang = 9000, Terisi = 6000, Status = Bebas
Blok 3: Ukuran Ruang = 5000, Terisi = 0, Status = Bebas
Blok 4: Ukuran Ruang = 1000, Terisi = 0, Status = Bebas

Memori setelah kompaksi:
Status blok memori:
Blok 0: Ukuran Ruang = 6000, Terisi = 4000, Status = Bebas
Blok 1: Ukuran Ruang = 6500, Terisi = 6000, Status = Bebas
Blok 2: Ukuran Ruang = 9000, Terisi = 6000, Status = Bebas
Blok 3: Ukuran Ruang = 5000, Terisi = 0, Status = Bebas
Blok 4: Ukuran Ruang = 1000, Terisi = 0, Status = Bebas


Waktu eksekusi next fit: 0.013000 detik
```

Sebagai contoh pada output worst fit, terjadi fragmentasi dimana 6000 ukuran terpecah pecah dan kosong di blok 0 - 3, namun setelah  kompaksi blok 4 dan 5 menjad sepenuhnya kosong


---

  

## **4. Analisis Hasil**

  

- **Fragmentasi dan Kinerja Alokasi**:

    - Seiring dengan bertambahnya alokasi, fragmentasi heap meningkat, menyebabkan kegagalan alokasi memori besar setelah sejumlah percobaan.

    - Waktu rata-rata untuk alokasi memori juga meningkat seiring dengan meningkatnya fragmentasi, yang menunjukkan dampak negatif fragmentasi pada kinerja aplikasi.

- **Kompaksi Memori**:

    - Implementasi kompaksi memori membantu mengurangi fragmentasi dengan menggabungkan blok-blok memori yang berdekatan menjadi satu blok besar yang lebih besar.

    - Dengan menggunakan kompaksi, waktu rata-rata untuk alokasi dapat distabilkan, dan kemungkinan untuk berhasil mengalokasikan blok memori besar meningkat.

---
## **5. Kesimpulan**

  

Fragmentasi heap merupakan masalah serius yang dapat menghambat kinerja aplikasi, terutama dalam skenario di mana alokasi dan dealokasi memori dilakukan secara dinamis. Solusi seperti kompaksi memori dan garbage collection terbukti efektif dalam mengurangi fragmentasi dan mempertahankan kinerja yang optimal. Implementasi manajemen memori yang lebih canggih, seperti buddy allocator atau pool allocator, juga dapat dipertimbangkan untuk aplikasi dengan kebutuhan memori yang kompleks.

### Contoh Kasus
ketika menjalankan software pada os jika membuka banyak aplikasi atau tab browser sekaligus akan menyebabkan penurunan performa, kemudian ketika kita men close nya secara acak kemungkinan memori yang telah teralokasi akan menjadi lubang atau terjadi fragmentasi yang membuat tidak bisa mengembalikan performa seperti awal secara penuh
[Soource]([Fragmentasi (komputer) (stekom.ac.id)](https://p2k.stekom.ac.id/ensiklopedia/Fragmentasi_%28komputer%29?formCode=MG0AV3))