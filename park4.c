#include <stdio.h>
#include <time.h>
#include <string.h>

struct Kendaraan
{
    char plat_nomor[50];
    time_t waktu_masuk;
    time_t waktu_keluar;
};

int main()
{ 
    int pilihan;
    do
{
    printf("Menu Sistem Parkir:\n");
    printf("1. Parkir motor\n");
    printf("2. Parkir mobil\n");
    printf("3. Exit\n");
    printf("4. Pencarian data\n");
    printf("5. Pengurutan data\n");
    printf("Masukkan pilihan Anda: ");
    scanf("%d", &pilihan);

        switch (pilihan)
        {
            case 1:
            {
                printf("Anda memilih parkir motor.\n");

                char plat_nomor[50];
                printf("Masukkan plat nomor: ");
                scanf("%s", plat_nomor);
                getchar(); //to flush the buffer 
                fgets(plat_nomor, sizeof(plat_nomor), stdin);
                //Remove newline character from the string
                plat_nomor[strcspn(plat_nomor, "\n")] = 0;

                // Validasi plat nomor
                if (strlen(plat_nomor) < 1 || strlen(plat_nomor) > 50)
                {
                    printf("Plat nomor tidak valid.\n");
                    break;
                }

                // Buat struct Kendaraan
                struct Kendaraan kendaraan;
                strcpy(kendaraan.plat_nomor, plat_nomor);
                kendaraan.waktu_masuk = time(NULL);
                kendaraan.waktu_keluar = 0;

                // Simpan data kendaraan ke file
                FILE *fp = fopen("parkir_motor.txt", "a");
                if (fp == NULL)
                {
                    printf("Gagal membuka file.\n");
                    break;
                }

                fprintf(fp, "%s %ld\n", kendaraan.plat_nomor,kendaraan.waktu_masuk);
                fclose(fp);

                printf("Data kendaraan berhasil disimpan.\n");
                break;
            }

            case 2:
            {
                printf("Anda memilih parkir mobil.\n");

                char plat_nomor[50];
                printf("Masukkan plat nomor: ");
                scanf("%s", plat_nomor);
                getchar(); //to flush the buffer
                fgets(plat_nomor, sizeof(plat_nomor), stdin);
                //Remove newline character from the string
                plat_nomor[strcspn(plat_nomor, "\n")] = 0;

                // Validasi plat nomor
                if (strlen(plat_nomor) < 1 || strlen(plat_nomor) > 50)
                {
                    printf("Plat nomor tidak valid.\n");
                    break;
                }

                // Buat struct Kendaraan
                struct Kendaraan kendaraan;
                strcpy(kendaraan.plat_nomor, plat_nomor);
                kendaraan.waktu_masuk = time(NULL);
                kendaraan.waktu_keluar = 0;

                // Simpan data kendaraan ke file
                FILE *fp = fopen("parkir_mobil.txt", "a");
                if (fp == NULL)
                {
                    printf("Gagal membuka file.\n");
                    break;
                }

                fprintf(fp, "%s %ld\n", kendaraan.plat_nomor, kendaraan.waktu_masuk);
                fclose(fp);

                printf("Data kendaraan berhasil disimpan.\n");
                break;
            }

            case 4:
            {
                printf("Anda memilih pencarian data.\n");
                char plat_nomor[50];
                printf("Masukkan plat nomor: ");
                scanf("%s", plat_nomor);

                // Validasi plat nomor
                if (strlen(plat_nomor) < 1 || strlen(plat_nomor) > 50)
                {
                    printf("Plat nomor tidak valid.\n");
                    break;
                }

                // Buka file parkir_motor.txt dan parkir_mobil.txt
                FILE *fp_motor = fopen("parkir_motor.txt", "r");
                FILE *fp_mobil = fopen("parkir_mobil.txt", "r");

                if (fp_motor == NULL || fp_mobil == NULL)
                {
                    printf("Gagal membuka file.\n");
                    break;
                }

                //Cari data pada file parkir_motor.txt
                char plat[50], timestring[100];
                long int time;
                while (fscanf(fp_motor, "%s %ld", plat, &time) != EOF)
                {
                    if (strcmp(plat, plat_nomor) == 0)
                    {
                        strftime(timestring, sizeof(timestring), "%c", localtime(&time));
                        printf("Data ditemukan! Plat nomor: %s, Waktu masuk: %s (motor)\n", plat_nomor, timestring);
                        fclose(fp_motor);
                        fclose(fp_mobil);
                        return 0;
                    }
                }
                //Cari data pada file parkir_mobil.txt
                while (fscanf(fp_mobil, "%s %ld", plat, &time) != EOF)
                {
                    if (strcmp(plat, plat_nomor) == 0)
                    {
                        strftime(timestring, sizeof(timestring), "%c", localtime(&time));
                        printf("Data ditemukan! Plat nomor: %s, Waktu masuk: %s (mobil)\n", plat_nomor, timestring);
                        fclose(fp_motor);
                        fclose(fp_mobil);
                        return 0;
                    }
                }

                printf("Data tidak ditemukan.\n");
                fclose(fp_motor);
                fclose(fp_mobil);
                break;
            }

            case 5:
            {
                        printf("Anda memilih pengurutan data.\n");

                        // Pilih jenis kendaraan
                        printf("1. Motor\n");
                        printf("2. Mobil\n");
                        printf("Masukkan pilihan Anda: ");
                        int pilihan_kendaraan;
                        scanf("%d", &pilihan_kendaraan);

                        // Baca file sesuai dengan jenis kendaraan
                        char *filename;
                        if (pilihan_kendaraan == 1)
                    {
                        filename = "parkir_motor.txt";
                    }
                        else if (pilihan_kendaraan == 2)
                    {
                       filename = "parkir_mobil.txt";
                    }
                        else
                    {
                        printf("Pilihan tidak valid.\n");
                        break;
                    }

                        FILE *fp = fopen(filename, "r");
                        if (fp == NULL)
                    {
                        printf("Gagal membuka file.\n");
                        break;
                    }

    // Baca semua data kendaraan dari file ke dalam array of struct Kendaraan
                        struct Kendaraan kendaraan[100];
                        int i = 0;
                        while (fscanf(fp, "%s,%ld,%ld\n", kendaraan[i].plat_nomor, &kendaraan[i].waktu_masuk, &kendaraan[i].waktu_keluar) == 3)
                    {
                        i++;
                    }
                        int n = i;
                        fclose(fp);

    // Lakukan pengurutan data kendaraan menggunakan bubble sort
                        for (i = 0; i < n - 1; i++)
                    {
                        for (int j = 0; j < n - i - 1; j++)
                    {
                         if (kendaraan[j].waktu_masuk > kendaraan[j + 1].waktu_masuk)
                {
                        struct Kendaraan temp = kendaraan[j];
                        kendaraan[j] = kendaraan[j + 1];
                        kendaraan[j + 1] = temp;
                }
     }
    }

    // Cetak data kendaraan yang sudah terurut
                        printf("Data kendaraan terurut:\n");
                        for (i = 0; i < n; i++)
                    {
                        printf("Plat nomor: %s\n", kendaraan[i].plat_nomor);
                        printf("Waktumasuk: %s", ctime(&kendaraan[i].waktu_masuk));
                        if (kendaraan[i].waktu_keluar > 0)
                    {
                        printf("Waktu keluar: %s", ctime(&kendaraan[i].waktu_keluar));
                    }
                    }
                        break;
                }
                       
                {
                        
                }


        }
            
    } while (pilihan != 3);

    return 0;
                }

