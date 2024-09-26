import time

# Struktur untuk menyimpan informasi blok memori
class MemoryBlock:
    def __init__(self, room):
        self.room = room  # Ukuran asli blok memori
        self.occupied = 0  # Ukuran terisi dalam blok
        self.free = True  # Status blok (True untuk bebas, False untuk tidak bebas)

# Variabel global untuk menyimpan posisi terakhir yang dialokasikan
last_allocated_index = 0

# Fungsi untuk menemukan blok pertama yang cukup besar (First-Fit)
def find_first_fit_block(blocks, size):
    for i, block in enumerate(blocks):
        if block.free and (block.room - block.occupied) >= size:
            return i  # Mengembalikan indeks blok pertama yang sesuai
    return -1  # Tidak ditemukan blok yang cukup besar

# Fungsi untuk melakukan alokasi memori dengan algoritma First-Fit
def first_fit_allocation(blocks, size):
    block_index = find_first_fit_block(blocks, size)
    
    if block_index == -1:
        print(f"Tidak ada blok memori yang cukup besar untuk alokasi {size}")
    else:
        blocks[block_index].occupied += size
        if blocks[block_index].occupied == blocks[block_index].room:
            blocks[block_index].free = False  # Jika terisi penuh, blok menjadi tidak bebas
        print(f"Dialokasikan {size} memori pada blok {block_index}")

# Fungsi untuk menemukan blok terbaik (Best-Fit)
def find_best_fit_block(blocks, size):
    best_index = -1
    min_size = float('inf')  # Set nilai awal ke ukuran memori terbesar

    for i, block in enumerate(blocks):
        if block.free and (block.room - block.occupied) >= size and (block.room - block.occupied) < min_size:
            min_size = block.room - block.occupied
            best_index = i
    
    return best_index

# Fungsi untuk melakukan alokasi memori dengan algoritma Best-Fit
def best_fit_allocation(blocks, size):
    block_index = find_best_fit_block(blocks, size)
    
    if block_index == -1:
        print(f"Tidak ada blok memori yang cukup besar untuk alokasi {size}")
    else:
        blocks[block_index].occupied += size
        if blocks[block_index].occupied == blocks[block_index].room:
            blocks[block_index].free = False  # Jika terisi penuh, blok menjadi tidak bebas
        print(f"Dialokasikan {size} memori pada blok {block_index}")

# Fungsi untuk menemukan blok terbesar (Worst-Fit)
def find_worst_fit_block(blocks, size):
    worst_index = -1
    max_size = 0
    
    for i, block in enumerate(blocks):
        if block.free and (block.room - block.occupied) >= size and (block.room - block.occupied) > max_size:
            max_size = block.room - block.occupied
            worst_index = i
    
    return worst_index

# Fungsi untuk melakukan alokasi memori dengan algoritma Worst-Fit
def worst_fit_allocation(blocks, size):
    block_index = find_worst_fit_block(blocks, size)
    
    if block_index == -1:
        print(f"Tidak ada blok memori yang cukup besar untuk alokasi {size}")
    else:
        blocks[block_index].occupied += size
        if blocks[block_index].occupied == blocks[block_index].room:
            blocks[block_index].free = False  # Jika terisi penuh, blok menjadi tidak bebas
        print(f"Dialokasikan {size} memori pada blok {block_index}")

# Fungsi untuk menemukan blok berikutnya yang cukup besar (Next-Fit)
def find_next_fit_block(blocks, size):
    global last_allocated_index
    i = last_allocated_index

    for _ in range(len(blocks)):
        if blocks[i].free and (blocks[i].room - blocks[i].occupied) >= size:
            last_allocated_index = i  # Simpan posisi terakhir yang dialokasikan
            return i  # Mengembalikan indeks blok yang sesuai
        i = (i + 1) % len(blocks)  # Berputar ke blok berikutnya
    
    return -1  # Tidak ditemukan blok yang cukup besar

# Fungsi untuk melakukan alokasi memori dengan algoritma Next-Fit
def next_fit_allocation(blocks, size):
    block_index = find_next_fit_block(blocks, size)
    
    if block_index == -1:
        print(f"Tidak ada blok memori yang cukup besar untuk alokasi {size}")
    else:
        blocks[block_index].occupied += size
        if blocks[block_index].occupied == blocks[block_index].room:
            blocks[block_index].free = False  # Jika terisi penuh, blok menjadi tidak bebas
        print(f"Dialokasikan {size} memori pada blok {block_index}")

# Fungsi untuk melakukan kompaksi memori
def compact(blocks):
    for i in range(len(blocks)):
        if blocks[i].free:
            temp = blocks[i].room - blocks[i].occupied  # Ruang kosong di blok i
            j = i + 1
            while j < len(blocks):
                # print(f"Memeriksa blok {j}...")
                if blocks[j].occupied > 0:
                    # Pindahkan sebanyak mungkin dari blok j ke blok i
                    move_amount = min(temp, blocks[j].occupied)

                    # Pindahkan isi dari blok j ke blok i
                    blocks[i].occupied += move_amount
                    blocks[j].occupied -= move_amount
                    temp -= move_amount  # Perbarui sisa ruang di blok i

                    print(f"Memindahkan {move_amount} dari blok {j} ke blok {i}")
                    # print(f"Blok i {i} sekarang = {blocks[i].occupied} {blocks[i].room} {blocks[i].free}")
                    # print(f"Blok j {j} sekarang = {blocks[j].occupied} {blocks[j].room} {blocks[j].free}")

                    # Jika blok i sudah penuh, hentikan pemindahan
                    if blocks[i].occupied == blocks[i].room:
                        blocks[i].free = False
                    # print(f"Memeriksa blok {j}...")
                    if blocks[j].occupied <= blocks[j].room:
                        blocks[j].free = 1  # Tandai blok j sebagai bebas jika kosong
                        break

                j += 1

            # Jika blok j sudah kosong, tandai sebagai bebas

        


                
# Fungsi untuk menampilkan status blok memori
def display_memory(blocks):
    print("Status blok memori:")
    for i, block in enumerate(blocks):
        print(f"Blok {i}: Ukuran Ruang = {block.room}, Ukuran Terisi = {block.occupied}, Status = {'Bebas' if block.free else 'Tidak Bebas'}")
    print()

def main():
    memory_first = [MemoryBlock(6000), MemoryBlock(6500), MemoryBlock(9000), MemoryBlock(5000), MemoryBlock(1000)]
    memory_best = [MemoryBlock(6000), MemoryBlock(6500), MemoryBlock(9000), MemoryBlock(5000), MemoryBlock(1000)]
    memory_worst = [MemoryBlock(6000), MemoryBlock(6500), MemoryBlock(9000), MemoryBlock(5000), MemoryBlock(1000)]
    memory_next = [MemoryBlock(6000), MemoryBlock(6500), MemoryBlock(9000), MemoryBlock(5000), MemoryBlock(1000)]
    
    allocation_sizes = [5000, 3000, 3000, 9000, 5000, 2000]

    # First-Fit Allocation
    start_time_first = time.time()
    print("Memori awal first fit:")
    display_memory(memory_first)
    
    for size in allocation_sizes:
        first_fit_allocation(memory_first, size)
    
    print("\nMemori setelah alokasi first fit:")
    display_memory(memory_first)

    compact(memory_first)
    print("Memori setelah kompaksi:")
    display_memory(memory_first)

    elapsed_time_first = time.time() - start_time_first
    print(f"\nWaktu eksekusi first fit: {elapsed_time_first:.6f} detik\n")
    
    # Best-Fit Allocation
    start_time_best = time.time()
    print("\nMemori awal best fit:")
    display_memory(memory_best)
    
    for size in allocation_sizes:
        best_fit_allocation(memory_best, size)
    
    print("\nMemori setelah alokasi best fit:")
    display_memory(memory_best)

    compact(memory_best)
    print("Memori setelah kompaksi:")
    display_memory(memory_best)

    elapsed_time_best = time.time() - start_time_best
    print(f"\nWaktu eksekusi best fit: {elapsed_time_best:.6f} detik\n")
    
    # Worst-Fit Allocation
    start_time_worst = time.time()
    print("\nMemori awal worst fit:")
    display_memory(memory_worst)
    
    for size in allocation_sizes:
        worst_fit_allocation(memory_worst, size)
    
    print("\nMemori setelah alokasi worst fit:")
    display_memory(memory_worst)

    compact(memory_worst)
    print("Memori setelah kompaksi:")
    display_memory(memory_worst)

    elapsed_time_worst = time.time() - start_time_worst
    print(f"\nWaktu eksekusi worst fit: {elapsed_time_worst:.6f} detik\n")
    
    # Next-Fit Allocation
    start_time_next = time.time()
    print("\nMemori awal next fit:")
    display_memory(memory_next)
    
    for size in allocation_sizes:
        next_fit_allocation(memory_next, size)
    
    print("\nMemori setelah alokasi next fit:")
    display_memory(memory_next)

    compact(memory_next)
    print("Memori setelah kompaksi:")
    display_memory(memory_next)

    elapsed_time_next = time.time() - start_time_next
    print(f"\nWaktu eksekusi next fit: {elapsed_time_next:.6f} detik\n")

if __name__ == "__main__":
    main()
