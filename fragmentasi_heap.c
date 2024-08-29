#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // Untuk sleep()

#define HEAP_SIZE 1024 * 1024 // 1 MB heap
#define MAX_ALLOC_SIZE 1024   // Ukuran alokasi maksimum 1 KB
#define ALLOC_ATTEMPTS 10000  // Jumlah percobaan alokasi

typedef struct Block
{
    size_t size;
    int is_free;
    struct Block *next;
} Block;

Block *heap_start = NULL;

void init_heap()
{
    heap_start = (Block *)malloc(HEAP_SIZE);
    heap_start->size = HEAP_SIZE - sizeof(Block);
    heap_start->is_free = 1;
    heap_start->next = NULL;
}

void *my_malloc(size_t size)
{
    Block *current = heap_start;
    while (current != NULL)
    {
        if (current->is_free && current->size >= size)
        {
            if (current->size > size + sizeof(Block))
            {
                Block *new_block = (Block *)((char *)current + sizeof(Block) + size);
                new_block->size = current->size - size - sizeof(Block);
                new_block->is_free = 1;
                new_block->next = current->next;
                current->next = new_block;
            }
            current->size = size;
            current->is_free = 0;
            return (char *)current + sizeof(Block);
        }
        current = current->next;
    }
    return NULL;
}

void my_free(void *ptr)
{
    if (ptr == NULL)
        return;
    Block *block = (Block *)((char *)ptr - sizeof(Block));
    block->is_free = 1;
}

size_t calculate_fragmentation()
{
    Block *current = heap_start;
    size_t free_space = 0;
    size_t largest_free_block = 0;

    while (current != NULL)
    {
        if (current->is_free)
        {
            free_space += current->size;
            if (current->size > largest_free_block)
            {
                largest_free_block = current->size;
            }
        }
        current = current->next;
    }

    return free_space - largest_free_block;
}

void print_heap_state()
{
    Block *current = heap_start;
    printf("Heap State:\n");
    while (current != NULL)
    {
        printf("Block at %p: size=%zu, is_free=%d\n",
               (void *)current, current->size, current->is_free);
        current = current->next;
    }
}

void compact_heap() {
    Block *current = heap_start;
    Block *last_free = NULL;

    while (current != NULL) {
        if (current->is_free) {
            if (last_free != NULL) {
                // Gabungkan blok yang sedang bebas dengan blok sebelumnya
                last_free->size += current->size + sizeof(Block);
                last_free->next = current->next;
            } else {
                last_free = current;
            }
        } else {
            last_free = NULL;
        }
        current = current->next;
    }
}

void perform_experiment()
{
    void *allocated_blocks[ALLOC_ATTEMPTS] = {0};
    clock_t start, end;
    double total_allocation_time = 0;

    for (int i = 0; i < ALLOC_ATTEMPTS; i++)
    {
        size_t size = rand() % MAX_ALLOC_SIZE + 1;

        start = clock();
        allocated_blocks[i] = my_malloc(size);
        end = clock();

        double allocation_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        total_allocation_time += allocation_time;

        if (allocated_blocks[i] == NULL && i > 3900)
        {
            printf("Allocation failed at attempt %d. Analyzing heap state...\n", i);
            print_heap_state();
            sleep(1); // Tambahkan delay
            break;
        }

        if (i % 100 == 0)
        {
            printf("Iteration %d\n", i);
            for (size_t i = 0; i < 100; i++)
            {
                printf("=");
            }
            printf("\n");
            size_t frag = calculate_fragmentation();
            printf("Fragmentation after %d allocations: %zu bytes\n", i, frag);
            printf("Average allocation time after %d allocations: %f seconds\n\n", i, total_allocation_time / (i + 1));

            // compact_heap(); // Kompakkan heap setiap 100 alokasi

            size_t frag_after = calculate_fragmentation();
            printf("Fragmentation after compaction after %d allocations: %zu bytes\n", i, frag_after);
            printf("Average allocation time after %d allocations: %f seconds\n", i, total_allocation_time / (i + 1));
            for (size_t i = 0; i < 100; i++)
            {
                printf("=");
            }
            printf("\n\n");

            // Tambahkan delay untuk visualisasi eksperimen
            sleep(1);
        }

        // Mengalokasikan dan membebaskan blok secara acak untuk meningkatkan fragmentasi
        if (rand() % 2 == 0 && allocated_blocks[i])
        {
            my_free(allocated_blocks[i]);
            allocated_blocks[i] = NULL;
        }
    }
}

int main()
{
    srand(time(NULL));
    init_heap();
    perform_experiment();
    return 0;
}
