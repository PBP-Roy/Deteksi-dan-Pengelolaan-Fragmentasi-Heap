
#include <stdio.h>
#include <time.h>

#define MEMORY_SIZE 2750 * 2750 // Ukuran memori total
#define NUM_BLOCKS 5             // Jumlah blok memori

// Struktur untuk menyimpan informasi blok memori
typedef struct {
    int room;          // Ukuran asli blok memori
    int occupied;      // Ukuran terisi dalam blok
    int free;          // Status blok (1 untuk bebas, 0 untuk tidak bebas)
} MemoryBlock;



// Fungsi untuk menemukan blok pertama yang cukup besar (First-Fit)
int find_first_fit_block(MemoryBlock blocks[], int num_blocks, int size) {
    for (int i = 0; i < num_blocks; i++) {
        if (blocks[i].free && (blocks[i].room - blocks[i].occupied) >= size) {
            return i;  // Mengembalikan indeks blok pertama yang sesuai
        }
    }
    return -1;  // Tidak ditemukan blok yang cukup besar
}

// Fungsi untuk melakukan alokasi memori dengan algoritma First-Fit
void first_fit_allocation(MemoryBlock blocks[], int num_blocks, int size) {
    int block_index = find_first_fit_block(blocks, num_blocks, size);
    
    if (block_index == -1) {
        printf("Tidak ada blok memori yang cukup besar untuk alokasi %d\n", size);
    } else {
        blocks[block_index].occupied += size;
        if (blocks[block_index].occupied == blocks[block_index].room) {
            blocks[block_index].free = 0;  // Jika terisi penuh, blok menjadi tidak bebas
        }
        printf("Dialokasikan %d memori pada blok %d\n", size, block_index);
    }
}

// Fungsi untuk menemukan blok terbaik (Best-Fit)
int find_best_fit_block(MemoryBlock blocks[], int num_blocks, int size) {
    int best_index = -1;
    int min_size = MEMORY_SIZE + 1;  // Set nilai awal ke ukuran memori terbesar

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
            blocks[block_index].free = 0;  // Jika terisi penuh, blok menjadi tidak bebas
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
            blocks[block_index].free = 0;  // Jika terisi penuh, blok menjadi tidak bebas
        }
        printf("Dialokasikan %d memori pada blok %d\n", size, block_index);
    }
}

// Fungsi untuk menemukan blok berikutnya yang cukup besar (Next-Fit)
int find_next_fit_block(MemoryBlock blocks[], int num_blocks, int size, int *last_allocated_index) {
    int i = *last_allocated_index;

    for (int count = 0; count < num_blocks; count++) {
        if (blocks[i].free && (blocks[i].room - blocks[i].occupied) >= size) {
            *last_allocated_index = i;  // Simpan posisi terakhir yang dialokasikan
            return i;  // Mengembalikan indeks blok yang sesuai
        }
        i = (i + 1) % num_blocks;  // Berputar ke blok berikutnya
    }
    
    return -1;  // Tidak ditemukan blok yang cukup besar
}

// Fungsi untuk melakukan alokasi memori dengan algoritma Next-Fit
void next_fit_allocation(MemoryBlock blocks[], int num_blocks, int size, int *last_allocated_index) {
    int block_index = find_next_fit_block(blocks, num_blocks, size, last_allocated_index);
    
    if (block_index == -1) {
        printf("Tidak ada blok memori yang cukup besar untuk alokasi %d\n", size);
    } else {
        blocks[block_index].occupied += size;
        if (blocks[block_index].occupied == blocks[block_index].room) {
            blocks[block_index].free = 0;  // Jika terisi penuh, blok menjadi tidak bebas
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
