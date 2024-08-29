### **Laporan Eksperimen: Simulasi Fragmentasi Heap dan Solusi Pengelolaannya**

---

#### **1. Pendahuluan**

Dalam pengembangan perangkat lunak, manajemen memori merupakan aspek penting yang mempengaruhi kinerja aplikasi. Salah satu masalah yang sering dihadapi adalah fragmentasi heap, di mana blok memori yang terpisah-pisah dan tidak berkesinambungan menghalangi alokasi memori besar, meskipun jumlah memori yang tersedia mencukupi. Eksperimen ini bertujuan untuk mempelajari bagaimana fragmentasi heap memengaruhi kinerja aplikasi dan untuk menguji beberapa solusi untuk mengatasinya.

---

#### **2. Metodologi Eksperimen**

Eksperimen ini terdiri dari tiga langkah utama:

1. **Simulasi Alokasi dan Dealokasi Memori**: Program C yang dibuat secara acak mengalokasikan dan membebaskan blok memori dengan ukuran bervariasi untuk mensimulasikan fragmentasi heap.
2. **Monitoring Fragmentasi dan Kinerja**: Setiap 100 alokasi, tingkat fragmentasi heap dan waktu rata-rata alokasi diukur. Upaya alokasi blok memori besar juga dilakukan secara berkala untuk mengevaluasi dampak fragmentasi.
3. **Implementasi Solusi**: Beberapa solusi untuk mengurangi fragmentasi, termasuk kompaksi memori dan garbage collection, diterapkan dan dianalisis.

---


#### **3. Analisis Hasil**

- **Fragmentasi dan Kinerja Alokasi**:
    
    - Seiring dengan bertambahnya alokasi, fragmentasi heap meningkat, menyebabkan kegagalan alokasi memori besar setelah sejumlah percobaan.
    - Waktu rata-rata untuk alokasi memori juga meningkat seiring dengan meningkatnya fragmentasi, yang menunjukkan dampak negatif fragmentasi pada kinerja aplikasi.
- **Kompaksi Memori**:
    
    - Implementasi kompaksi memori membantu mengurangi fragmentasi dengan menggabungkan blok-blok memori yang berdekatan menjadi satu blok besar yang lebih besar.
    - Dengan menggunakan kompaksi, waktu rata-rata untuk alokasi dapat distabilkan, dan kemungkinan untuk berhasil mengalokasikan blok memori besar meningkat.
- **Garbage Collection**:
    
    - Garbage collection sederhana yang menggabungkan blok memori yang tidak digunakan dapat membantu mengurangi fragmentasi dan meningkatkan ketersediaan memori untuk alokasi baru.

---

#### **4. Kesimpulan**

Fragmentasi heap merupakan masalah serius yang dapat menghambat kinerja aplikasi, terutama dalam skenario di mana alokasi dan dealokasi memori dilakukan secara dinamis. Solusi seperti kompaksi memori dan garbage collection terbukti efektif dalam mengurangi fragmentasi dan mempertahankan kinerja yang optimal. Implementasi manajemen memori yang lebih canggih, seperti buddy allocator atau pool allocator, juga dapat dipertimbangkan untuk aplikasi dengan kebutuhan memori yang kompleks.