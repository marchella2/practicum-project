#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100 // Maksimum jumlah buku yang bisa disimpan

// Struktur untuk menyimpan data buku
typedef struct {
    char nama[100];
    char jenis[50];
    int harga;
} Buku;

// Struktur untuk menyimpan data history
typedef struct {
    char nama[100];
    int jumlah;
    int total;
} History;


Buku daftarBuku[MAX]; // Array untuk menyimpan daftar buku
History daftarHistory[MAX]; // Array untuk menyimpan daftar history buku
int jumlahBuku = 0;   // Counter jumlah buku yang tersimpan saat ini
int jumlahHistory = 0; // Counter jumlah history yang tersimpan saat ini

// Fungsi untuk menyimpan semua data buku ke file databuku.txt
void simpanKeFile() {
    FILE *file = fopen("databuku.txt", "w"); // Membuka file untuk ditulis ulang (overwrite)
    if (file == NULL) {
        printf("Gagal membuka file untuk menyimpan.\n");
        return;
    }

    // Menuliskan seluruh data buku dari array ke file
    for (int i = 0; i < jumlahBuku; i++) {
        fprintf(file, "%-30s %-15s %d\n",
                daftarBuku[i].nama,
                daftarBuku[i].jenis,
                daftarBuku[i].harga);
    }

    fclose(file); // Menutup file
}

// Fungsi untuk menambahkan buku baru ke array
void inputBuku() {
    if (jumlahBuku >= MAX) {
        printf("Kapasitas buku penuh.\n");
        return;
    }

    getchar(); // Membersihkan newline dari input sebelumnya

    // Input nama buku
    printf("Masukkan nama buku  : ");
    fgets(daftarBuku[jumlahBuku].nama, sizeof(daftarBuku[jumlahBuku].nama), stdin);
    daftarBuku[jumlahBuku].nama[strcspn(daftarBuku[jumlahBuku].nama, "\n")] = '\0'; // Hapus newline

    // Input jenis buku
    printf("Masukkan jenis buku : ");
    fgets(daftarBuku[jumlahBuku].jenis, sizeof(daftarBuku[jumlahBuku].jenis), stdin);
    daftarBuku[jumlahBuku].jenis[strcspn(daftarBuku[jumlahBuku].jenis, "\n")] = '\0';

    // Input harga buku
    printf("Masukkan harga buku : ");
    scanf("%d", &daftarBuku[jumlahBuku].harga);

    jumlahBuku++; // Tambahkan counter jumlah buku

    printf("Buku berhasil ditambahkan!\n");
}


void tampilkanHistory() {
    if (jumlahHistory == 0) {
        printf("Tidak ada history transaksi.\n");
        return;
    }

    printf("\nHistory Transaksi:\n");
    printf("Index %-30s %-10s %-10s\n", "Nama Buku", "Jumlah", "Total");
    printf("--------------------------------------------------------\n");
    for (int i = 0; i < jumlahHistory; i++) {
        printf("%5d %-30s %-10d %d\n",
               i + 1,
               daftarHistory[i].nama,
               daftarHistory[i].jumlah,
               daftarHistory[i].total);
    }
}


// Fungsi untuk membaca data buku dari file databuku.txt ke array
void loadBuku() {
    FILE *file = fopen("databuku.txt", "r"); // Buka file untuk dibaca
    if (file == NULL) {
        // Jika file belum ada, tidak perlu error
        return;
    }

    // Membaca file per baris sampai EOF
    while (fscanf(file, "%30[^\n] %15s %d\n",
                  daftarBuku[jumlahBuku].nama,
                  daftarBuku[jumlahBuku].jenis,
                  &daftarBuku[jumlahBuku].harga) != EOF) {
        jumlahBuku++; // Tambah jumlah data yang berhasil dibaca
        if (jumlahBuku >= MAX) break;
    }

    fclose(file); // Tutup file
}

// Fungsi untuk menampilkan semua data buku
void tampilkanDataBuku() {
    if (jumlahBuku == 0) {
        printf("Tidak ada data buku.\n");
        return;
    }

    // Header tampilan tabel buku
    printf("\nDaftar Buku:\n");
    printf("Index %-30s %-15s %-10s\n", "Nama", "Jenis", "Harga");
    printf("-------------------------------------------------------------------\n");

    // Menampilkan data dengan format tabel
    for (int i = 0; i < jumlahBuku; i++) {
        printf("%5d %-30s %-15s %d\n",
               i + 1, // Menampilkan index mulai dari 1
               daftarBuku[i].nama,
               daftarBuku[i].jenis,
               daftarBuku[i].harga);
    }
}

void transaksi() {
    if (jumlahBuku == 0) {
        printf("Tidak ada buku untuk ditransaksikan.\n");
        return;
    }

    tampilkanDataBuku();

    int index, jumlah;
    printf("Masukkan index buku yang ingin dibeli: ");
    scanf("%d", &index);

    if (index < 1 || index > jumlahBuku) {
        printf("Index tidak valid.\n");
        return;
    }

    printf("Masukkan jumlah buku yang ingin dibeli: ");
    scanf("%d", &jumlah);

    if (jumlah <= 0) {
        printf("Jumlah tidak valid.\n");
        return;
    }

    // Simpan ke history
    strcpy(daftarHistory[jumlahHistory].nama, daftarBuku[index - 1].nama);
    daftarHistory[jumlahHistory].jumlah = jumlah;
    daftarHistory[jumlahHistory].total = jumlah * daftarBuku[index - 1].harga;
    jumlahHistory++;

    printf("Transaksi berhasil disimpan!\n");
}


void deleteHistory() {
    tampilkanHistory();
    int index;
    printf("Masukkan index history yang ingin dihapus: ");
    scanf("%d", &index);
    if (index < 1 || index > jumlahHistory) {
        printf("Index tidak valid.\n");
        return;
    }
    for (int i = index - 1; i < jumlahHistory - 1; i++) {
        daftarHistory[i] = daftarHistory[i + 1];
    }
    jumlahHistory--;
    printf("Data history berhasil dihapus.\n");
}




// Fungsi untuk menghapus buku berdasarkan index
void hapusBuku() {
    if (jumlahBuku == 0) {
        printf("Tidak ada data buku untuk dihapus.\n");
        return;
    }

    tampilkanDataBuku(); // Tampilkan semua data dulu

    int index;
    printf("Masukkan index buku yang ingin dihapus: ");
    scanf("%d", &index);

    // Validasi index (harus di antara 1 dan jumlahBuku)
    if (index < 1 || index > jumlahBuku) {
        printf("Index tidak valid.\n");
        return;
    }

    // Geser elemen setelah index ke posisi sebelumnya (overwrite)
    for (int i = index - 1; i < jumlahBuku - 1; i++) {
        daftarBuku[i] = daftarBuku[i + 1];
    }

    jumlahBuku--; // Kurangi jumlah data buku

    printf("Data berhasil dihapus.\n");
}

// Fungsi utama program (menu utama)
int main() {
    int pilihan;
    loadBuku(); // Muat data buku dari file saat program mulai

    // Loop menu utama
    do {
        printf("\n===== MENU =====\n");
        printf("1. Input Buku\n");
        printf("2. View History \n");
        printf("3. View Buku\n");
        printf("4. Delete History\n");
        printf("5. Delete Buku\n");
        printf("6. Exit\n");
        printf("7. Transaksi\n");
        printf("Pilihan Anda: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                inputBuku(); // Tambah buku baru
                break;
            case 2:
                tampilkanHistory(); // Tampilkan history
                break;
            case 3:
                tampilkanDataBuku(); // Tampilkan daftar buku
                break;
            case 4:
                deleteHistory(); //Hapus history
                break;
            case 5:
                hapusBuku(); // Hapus buku berdasarkan index
                break;
            case 6:
                simpanKeFile(); // Simpan semua data ke file sebelum keluar
                printf("Data disimpan. Terima kasih!\n");
                break;
             case 7:
                transaksi(); // Simpan semua data ke file sebelum keluar
                break;
            default:
                printf("Pilihan tidak tersedia.\n");
        }

    } while (pilihan != 6); // Ulangi menu sampai user memilih exit

    return 0;
}
