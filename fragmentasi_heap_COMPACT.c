#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // Required for sleep()

#define HEAP_SIZE 1024 * 1024 // 1 MB heap
#define MAX_ALLOC_SIZE 1024 // Maximum allocation 1 KB
#define ALLOC_ATTEMPTS 10000 // Number of allocation attempts

typedef struct Block {
    int size;
    int is_free;
    struct Block *next;
} Block;

Block *heap_start = NULL;

void init_heap() {
    heap_start = (Block *)malloc(HEAP_SIZE);
    heap_start->size = HEAP_SIZE;
    heap_start->is_free = 1;
    heap_start->next = NULL;
}

void *my_malloc(int size) {
    Block *current = heap_start;
    while (current != NULL) {
        if (current->is_free && current->size >= size) {
            if (current->size > size + sizeof(Block)) {
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

void my_free(void *ptr) {
    if (ptr == NULL) return;
    Block *block = (Block *)((char *)ptr - sizeof(Block));
    block->is_free = 1;
    
    // Coalesce with next block if it's free
    if (block->next != NULL && block->next->is_free) {
        block->size += block->next->size + sizeof(Block);
        block->next = block->next->next;
    }
}

int calculate_fragmentation() {
    Block *current = heap_start;
    int free_space = 0;
    int largest_free_block = 0;
    
    while (current != NULL) {
        if (current->is_free) {
            free_space += current->size;
            if (current->size > largest_free_block) {
                largest_free_block = current->size;
            }
        }
        current = current->next;
    }
    
    return free_space - largest_free_block;
}

void print_heap_state() {
    Block *current = heap_start;
    printf("Heap State:\n");
    while (current != NULL) {
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

void perform_experiment() {
    void *allocated_blocks[ALLOC_ATTEMPTS] = {0};
    clock_t start, end;
    double total_allocation_time = 0;
    
    for (int i = 0; i < ALLOC_ATTEMPTS; i++) {
        int size = rand() % MAX_ALLOC_SIZE + 1;
        
        start = clock();
        allocated_blocks[i] = my_malloc(size);
        end = clock();
        
        double allocation_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        total_allocation_time += allocation_time;
        
        if (allocated_blocks[i] == NULL && i > 3900) {
            printf("Allocation failed at attempt %d. Analyzing heap state...\n", i);
            print_heap_state();
            sleep(1); // Add delay
            break;
        }
        
        if (i % 100 == 0) {
            int frag = calculate_fragmentation();
            printf("Fragmentation after %d allocations: %zu bytes\n", i, frag);
            printf("Average allocation time after %d allocations: %f seconds\n", i, total_allocation_time / (i + 1));
            
            compact_heap(); // Or garbage_collect();
            
            // Attempt large block allocation
            void *large_block = my_malloc(64 * 1024); // 64 KB
            if (large_block) {
                printf("Successfully allocated large block after %d allocations\n", i);
                my_free(large_block);
            } else {
                printf("Failed to allocate large block after %d allocations\n", i);
            }
            
            sleep(1); // Add delay
        }
        
        if (rand() % 2 == 0 && allocated_blocks[i]) {
            my_free(allocated_blocks[i]);
            allocated_blocks[i] = NULL;
        }
    }
}

int main() {
    srand(time(NULL));
    init_heap();
    perform_experiment();
    return 0;
}
