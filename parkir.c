#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

struct Kendaraan {
    char plat_nomor[50];
    char jenis_kendaraan[10];
    float jam_masuk,jam_keluar,tarif;
    int kode_parkir;
    time_t waktu_masuk;
    time_t waktu_keluar;
} Kendaraan;

void menu();
void parkirMobil();
void parkirMotor();
void keluar();
void urut();
void cari();

int main() {
    menu();
    return 0;
}

void menu() {
    int pilih;
    do {
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
        printf("                               PARKIR KENDARAAN RODA DUA/RODA EMPAT                             \n");
        printf("                                INSTITUT TEKNOLOGI TELKOM SURABAYA                              \n");
        printf("                        Jl. Ketintang No. 156,Surabaya,Jawa Timur,Indonesia                   \n\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
        printf("Menu Sistem Parkir:\n");
        printf("1. Parkir motor\n");
        printf("2. Parkir mobil\n");
        printf("3. Exit\n");
        printf("4. Pencarian data\n");
        printf("5. Pengurutan data\n");
        printf("Masukkan pilihan Anda: ");
        scanf("%d", & pilih);
        printf("\n");
        switch (pilih) {
        case 1:
            parkirMotor();
            break;
        case 2:
            parkirMobil();
            break;
        case 3:
            exit(0);
            break;
        case 4:
            cari();
            break;
        case 5:
            urut();
            break;
        default:
            printf("\t\tPilihan yang anda masukkan salah !! \n");
            menu();
            break;
        }
    } while (pilih != 3);

}
void print_current_date(char filename[20]) 
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    FILE * fp = fopen(filename, "a");
    fprintf(fp, "Tanggal : %d-%d-%d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}


void parkirMotor() {
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
    printf("                                    Anda memilih parkir motor.                                \n\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	float lama,bayar,biaya;
	Kendaraan.tarif = 2000;
    printf("Masukkan plat nomor: ");
    scanf(" %[^\n]s", Kendaraan.plat_nomor);
	
    // Validasi plat nomor
    if (strlen(Kendaraan.plat_nomor) < 1 || strlen(Kendaraan.plat_nomor) > 50) {
        printf("Plat nomor tidak valid.\n");
    }
    
    printf("Jam Masuk: ");
    scanf("%f", &Kendaraan.jam_masuk);
    
    printf("Jam Keluar: ");
    scanf("%f", &Kendaraan.jam_keluar);
    
    // Simpan data kendaraan ke file
    FILE * fp = fopen("parkir_motor.txt", "a");
    if (fp == NULL) {
        printf("Gagal membuka file.\n");
    }
	srand(time(NULL));
	Kendaraan.kode_parkir = rand()% 9000 + 1000;
	lama= Kendaraan.jam_keluar - Kendaraan.jam_masuk;
	biaya=lama*Kendaraan.tarif;
	                
    fprintf(fp, "%s %.2f %.2f\n", Kendaraan.plat_nomor,Kendaraan.jam_masuk, Kendaraan.jam_keluar);
    fclose(fp);
    printf("Data kendaraan berhasil disimpan.\n");
}

void parkirMobil() {
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
    printf("                                  Anda memilih parkir mobil.                                  \n\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	float lama,bayar,biaya;
	Kendaraan.tarif = 3000;
    printf("Masukkan plat nomor: ");
    scanf(" %s", Kendaraan.plat_nomor);
	
    // Validasi plat nomor
    if (strlen(Kendaraan.plat_nomor) < 1 || strlen(Kendaraan.plat_nomor) > 50) {
        printf("Plat nomor tidak valid.\n");
    }
    
    printf("Jam masuk: ");
    scanf("%f", &Kendaraan.jam_masuk);
    
    printf("Jam masuk: ");
    scanf("%f", &Kendaraan.jam_keluar);
    
    // Simpan data kendaraan ke file
    FILE * fp = fopen("parkir_mobil.txt", "a");
    if (fp == NULL) {
        printf("Gagal membuka file.\n");
    }
	srand(time(NULL));

    fprintf(fp, "%s %.2f %.2f\n", Kendaraan.plat_nomor,Kendaraan.jam_masuk, Kendaraan.jam_keluar);
    fclose(fp);
    printf("Data kendaraan berhasil disimpan.\n");
}

void cari() {
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
    printf("                                   Anda memilih pencarian data.                               \n\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

    // Pilih jenis kendaraan
    printf("1. Motor\n");
    printf("2. Mobil\n");
    printf("Masukkan pilihan Anda: ");
    int biaya,pilihan_kendaraan;
    
    scanf("%d", & pilihan_kendaraan);

    // Baca file sesuai dengan jenis kendaraan
    char * filename;
    if (pilihan_kendaraan == 1) {
        filename = "parkir_motor.txt";
    } else if (pilihan_kendaraan == 2) {
        filename = "parkir_mobil.txt";
    } else {
        printf("Pilihan tidak valid.\n");
    }

    FILE * fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Gagal membuka file.\n");
    }

    // Cari plat nomor
    char plat_nomor[50];
    char nomorKendaraan[50];
    printf("Masukkan plat nomor: ");
    scanf(" %[^\n]s", plat_nomor);
    struct Kendaraan kendaraan;
    char line[150], temp[150];
      int lineNumber = 1;
    while(fgets(line, sizeof line, fp) != NULL) {
        strcpy(temp, line);
        if (strstr(temp, plat_nomor) != NULL) {
            printf("%s ditemukan", plat_nomor);
        }
    }
    fclose(fp);
}

void urut() {
    printf("Anda memilih pengurutan data.\n");

    // Pilih jenis kendaraan
    printf("1. Motor\n");
    printf("2. Mobil\n");
    printf("Masukkan pilihan Anda: ");
    int pilihan_kendaraan;
    scanf("%d", & pilihan_kendaraan);

    // Baca file sesuai dengan jenis kendaraan
    char * filename;
    if (pilihan_kendaraan == 1) {
        filename = "parkir_motor.txt";
    } else if (pilihan_kendaraan == 2) {
        filename = "parkir_mobil.txt";
    } else {
        printf("Pilihan tidak valid.\n");
    }

    FILE * fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Gagal membuka file.\n");
    }
    // Baca semua data kendaraan dari file ke dalam array of struct Kendaraan
    int i = 0;
    float jam_masuk[100];
    float jam_keluar[100];
    char nomorKendaraan[100][30];
    struct Kendaraan kendaraan[100];
	while (fscanf(fp, "%s %.2f %.2f", kendaraan[i].plat_nomor, &kendaraan[i].jam_masuk, &kendaraan[i].jam_keluar) == 3)
    {
        i++;
    }
	fclose(fp);

	int n = i;
    for (i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (kendaraan[j].jam_masuk > kendaraan[j + 1].jam_masuk)
            {
                struct Kendaraan temp = kendaraan[j];
                        kendaraan[j] = kendaraan[j + 1];
                        kendaraan[j + 1] = temp;

            }
        }
    }

     printf("Data yang telah diurutkan:\n");
  for(int m = 0; m < i; m++) {
    printf("Plat nomor: %s\n", kendaraan[m].plat_nomor);
    printf("Waktu masuk: %f", &kendaraan[m].jam_masuk);
    if (kendaraan[m].jam_keluar > 0) {
      printf("Waktu keluar: %f", &kendaraan[i].waktu_keluar);
    }
  }
    
}
