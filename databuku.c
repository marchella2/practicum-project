#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char nama[100];
    char jenis[50];
    int harga;
} Buku;

void inputBuku() {
    FILE *file;
    Buku b;
    getchar(); // Bersihkan newline dari input sebelumnya

    printf("Masukkan nama buku  : ");
    fgets(b.nama, sizeof(b.nama), stdin);
    b.nama[strcspn(b.nama, "\n")] = '\0'; // Hapus newline

    printf("Masukkan jenis buku : ");
    fgets(b.jenis, sizeof(b.jenis), stdin);
    b.jenis[strcspn(b.jenis, "\n")] = '\0'; // Hapus newline

    printf("Masukkan harga buku : ");
    scanf("%d", &b.harga);

    file = fopen("databuku.txt", "a"); // buka file dalam mode append
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    fprintf(file, "%s#%s#%d\n", b.nama, b.jenis, b.harga);
    fclose(file);

    printf("Buku berhasil ditambahkan ke databuku.txt!\n");
}

int main() {
    int pilihan;

    do {
        printf("\n===== MENU =====\n");
        printf("1. Input Buku\n");
        printf("6. Exit\n");
        printf("Pilihan Anda: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                inputBuku();
                break;
            case 6:
                printf("Terima kasih!\n");
                break;
            default:
                printf("Pilihan tidak tersedia.\n");
        }
    } while (pilihan != 6);

    return 0;
}
