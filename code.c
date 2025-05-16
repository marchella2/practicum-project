#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//DEFINE VARIABEL(INDAH KUSUMAWATI)
#define MAX 100

typedef struct {
    char kode[10];
    char nama[50];
    char jenis[30];
    int harga;
} Buku;

typedef struct {
    char kode[10];
    int jumlah;
} Transaksi;

Buku daftarBuku[MAX];
int jumlahBuku = 0;

//Membaca data dari databuku.txt (INDAH KUSUMAWATI)
void loadBuku() {
    FILE *file = fopen("databuku.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka databuku.txt\n");
        return;
    }

    while (fscanf(file, "%s %49[^\n] %s %d\n",
           daftarBuku[jumlahBuku].kode,
           daftarBuku[jumlahBuku].nama,
           daftarBuku[jumlahBuku].jenis,
           &daftarBuku[jumlahBuku].harga) != EOF) {
        jumlahBuku++;
    }

    fclose(file);
}


//Input Data Buku Baru
void inputBuku() {
    FILE *file = fopen("databuku.txt", "a");
    if (file == NULL) {
        printf("Gagal membuka databuku.txt untuk menulis\n");
        return;
    }

    Buku b;
    printf("Masukkan kode buku: ");
    scanf("%s", b.kode);
    getchar(); // clear buffer
    printf("Masukkan nama buku: ");
    fgets(b.nama, sizeof(b.nama), stdin);
    strtok(b.nama, "\n"); // hapus newline
    printf("Masukkan jenis buku: ");
    scanf("%s", b.jenis);
    printf("Masukkan harga buku: ");
    scanf("%d", &b.harga);

    fprintf(file, "%s %s %s %d\n", b.kode, b.nama, b.jenis, b.harga);
    fclose(file);
    printf("Buku berhasil ditambahkan!\n");
}

//Menampilkan Data Buku (INDAH KUSUMAWATI)
void TampilkanDataBuku() {
    if (jumlahBuku == 0) {
        printf("Tidak ada data buku.\n");
        return;
    }

    printf("\nDaftar Buku:\n");
    printf("Kode\tNama\t\t\tJenis\t\tHarga\n");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < jumlahBuku; i++) {
        printf("%s\t%-20s\t%-10s\t%d\n", daftarBuku[i].kode, daftarBuku[i].nama, daftarBuku[i].jenis, daftarBuku[i].harga);
    }
}

//Menghapus Data Buku


//Menu Program Dashboard (INDAH KUSUMAWATI)
int main() {
    int pilihan;
    loadBuku();

    do {
        printf("\nMenu:\n");
        printf("1. Input Buku\n");
        printf("2. View History\n");
        printf("3. View Buku\n");
        printf("4. Delete History\n");
        printf("5. Delete Buku\n");
        printf("6. Exit\n");
        printf("Pilih menu (1-6): ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                inputBuku(); //(INDAH KUSUMAWATI)
                break;
            case 2:
                printf("Fitur View History belum diimplementasikan.\n");
                break;
            case 3:
                TampilkanDataBuku();
                break;
            case 4:
                printf("Fitur Delete History belum diimplementasikan.\n");
                break;
            case 5:
                printf("Fitur Delete History belum diimplementasikan.\n");
                break;
            case 6:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 6);

    return 0;
}

