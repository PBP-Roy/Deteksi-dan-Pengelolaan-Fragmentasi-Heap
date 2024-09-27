Algoritma manajemen memori dalam sistem operasi (OS) digunakan untuk mengatur alokasi dan dealokasi memori fisik dan virtual, serta untuk mengoptimalkan penggunaan sumber daya memori. Berikut beberapa algoritma manajemen memori yang umum diterapkan dalam OS:

### 1. **Swapping**

- **Swapping** adalah proses memindahkan proses yang tidak aktif dari memori utama ke disk (memori sekunder) untuk membuat ruang bagi proses yang sedang aktif. Ketika proses tersebut kembali dibutuhkan, OS akan menukarnya kembali ke memori utama.

### 2. **Paging**

- **Paging** membagi memori fisik menjadi blok-blok kecil yang disebut _frames_ dan memori logis menjadi blok-blok kecil yang disebut _pages_. Ketika sebuah proses dijalankan, hanya halaman yang dibutuhkan yang dimuat ke dalam memori fisik. Ini memungkinkan OS untuk menjalankan proses yang lebih besar daripada memori fisik yang tersedia.

### 3. **Segmentation**

- **Segmentation** membagi memori menjadi segmen-segmen dengan ukuran yang berbeda sesuai dengan logika program, seperti segmen untuk kode, data, dan tumpukan (_stack_). Setiap segmen memiliki basis alamat dan panjangnya sendiri, sehingga mendukung pemrograman modular.

### 4. **Virtual Memory**

- **Virtual Memory** adalah teknik di mana OS membuat ilusi memori yang lebih besar dari memori fisik sebenarnya. Ini memungkinkan program untuk menggunakan lebih banyak memori daripada yang tersedia di RAM dengan memanfaatkan ruang penyimpanan pada disk. Konsep utama dalam memori virtual adalah penggunaan tabel halaman (_page table_) untuk memetakan alamat virtual ke alamat fisik.

### 5. **Memory Allocation Algorithms**

- **First Fit**: Mencari dan menggunakan blok memori pertama yang cukup besar untuk kebutuhan proses.
- **Best Fit**: Mencari blok memori terkecil yang cukup besar untuk alokasi, mengurangi fragmentasi eksternal.
- **Worst Fit**: Mencari blok memori terbesar yang tersedia, digunakan untuk menghindari fragmentasi dengan menggunakan blok besar.
- **Next Fit**: Mirip dengan First Fit, tetapi pencarian dilanjutkan dari posisi terakhir alokasi sebelumnya.

### 6. **Fragmentation Management**

- **Fragmentasi Eksternal**: Memori bebas tersebar dalam blok-blok kecil yang tidak berdekatan, membuatnya sulit untuk mengalokasikan memori besar.
- **Fragmentasi Internal**: Terjadi ketika blok memori yang dialokasikan lebih besar dari yang diperlukan, menyisakan ruang kosong yang tidak terpakai.
- Untuk mengatasi fragmentasi, teknik seperti **Compaction** digunakan untuk menggabungkan ruang memori bebas yang tersebar menjadi satu blok yang lebih besar.

### 7. **Garbage Collection**

- Digunakan dalam bahasa pemrograman tingkat tinggi seperti Java atau Python, di mana sistem secara otomatis mengelola alokasi dan dealokasi memori. Algoritma seperti _Mark-and-Sweep_ atau _Reference Counting_ digunakan untuk mengidentifikasi dan membebaskan memori yang tidak lagi digunakan.

### 8. **Buddy System**

- Algoritma alokasi memori yang membagi memori menjadi blok-blok berukuran pangkat dua. Saat memori diperlukan, blok terbesar yang lebih kecil dari atau sama dengan ukuran yang diminta dipilih. Jika diperlukan, blok tersebut dibagi menjadi dua bagian yang lebih kecil hingga ukuran yang sesuai ditemukan.
### Contoh Kasus
ketika menjalankan software pada os jika membuka banyak aplikasi atau tab browser sekaligus akan menyebabkan penurunan performa, kemudian ketika kita men close nya secara acak kemungkinan memori yang telah teralokasi akan menjadi lubang atau terjadi fragmentasi yang membuat tidak bisa mengembalikan performa seperti awal secara penuh
[Source]([Fragmentasi (komputer) (stekom.ac.id)](https://p2k.stekom.ac.id/ensiklopedia/Fragmentasi_%28komputer%29?formCode=MG0AV3))