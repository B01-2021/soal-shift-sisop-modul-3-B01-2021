# soal-shift-sisop-modul-3-B01-2021

Dokumentasi soal shift Sisop Modul 3.
---
Kelompok B01:
- [Shidqi Dhaifullah](https://github.com/shdkong1)	05111940000108
- [Fiqey Indriati Eka Sari](https://github.com/finesaaa)	05111940000015 
- [Bunga Fairuz Wijdan](https://github.com/bungafairuz)	05111940000030

---

### Rangkuman Jawaban 
- [Soal 1](https://github.com/B01-2021/soal-shift-sisop-modul-3-B01-2021/blob/main/soal1/)
- [Soal 2](https://github.com/B01-2021/soal-shift-sisop-modul-3-B01-2021/blob/main/soal2/)
- [Soal 3](https://github.com/B01-2021/soal-shift-sisop-modul-3-B01-2021/blob/main/soal3/)
---

# Soal 1
## Perintah 'add'
client mengirim string input_file yang berisi (nama file, publisher, tahun publikasi, ekstensi, filepath) ke server

```
if(pilihan[0]=='a'){
            char input_file[200];
            char publisher[100], tahun[100], filepath[100], nama[100], ekstensi[100];
            long int posisi;
            //ambil variabel2 yang mai diinput
            printf("Publisher : ");
            scanf("%s", publisher);
            printf("Tahun Publikasi: ");
            scanf("%s", tahun);
            printf("Filepath : ");
            scanf("%s", filepath);

            //mengambil nama dan ekstensi dari pathfile
            char* hasil = strchr(filepath, '/');
            while(hasil != NULL){
                posisi = hasil - filepath+1;
                hasil = strchr(hasil+1, '/');
            }
            int ii=0, jj=0, eks=0;
            for(int i= posisi; i<strlen(filepath); i++){
                nama[ii++] = filepath[i];
                if(eks)
                    ekstensi[jj++]=filepath[i];
                if (filepath[i]=='.')
                    eks=1;
            }
            nama[ii]='\0';
            ekstensi[jj]='\0';

            //menyusun input_file lalu kirim ke server
            strcpy(input_file, nama);
            strcat(input_file, ",");
            strcat(input_file, publisher);
            strcat(input_file, ",");
            strcat(input_file, tahun);
            strcat(input_file, ",");
            strcat(input_file, ekstensi);
            strcat(input_file, ",");
            strcat(input_file, filepath);
            input_file[strlen(input_file)] = '\0';
            send(sock , input_file, strlen(input_file) , 0 );
        }
```

server menerima string input_file lalu memasukkan ke dalam file files.tsv lalu mengambil bagian filepath untuk mengcopy tiap karakter yang ada pada file tersebut ke sebuah file baru di Server/FILES/namafile.ekstensi kemudian mengisi file running.log dengan fungsi yang telah dibuat
```
if(pilihan[0]=='a'){
            //ambil input nama, publisher, tahun publikasi, ekstensi, filepath
            char input_file[1024] = {0};
            valread = read( new_socket , input_file, 1024);

            //tambah file di files.tsv
            ffiles= fopen("files.tsv","a");
            fputs(input_file, ffiles);
            fputs("\n", ffiles);
            printf("%s\n", input_file);
            fflush(ffiles);
            fclose(ffiles);

            //ambil tiap variabel yang dipisahin ','
            char filepath2[100], filepath[100], nama[100];
            char* hasil = strchr(input_file, ',');
            long int posisi, posisi1;
            posisi1 = hasil - input_file+1;
            while(hasil != NULL){
                posisi = hasil - input_file+1;
                hasil = strchr(hasil+1, ',');
            }
    
            // mendapat variabel nama dalam input_file
            int ii=0;
            for(int i = 0; i<posisi1-1; i++){
                nama[ii++] = input_file[i];

            }
            nama[ii]='\0';

            // mendapat variabel filepath dalam input file
            ii=0;
            for(int i = posisi; i<strlen(input_file); i++){
                filepath[ii++] = input_file[i];

            }
            filepath[ii]='\0';

            //cek udah ada folder FILES blm
            DIR* dir = opendir("FILES");
            if (!dir){
                int check = mkdir("FILES",0777);
            }

            //open file mula-mula
            fptr1 = fopen(filepath, "r");
            if(!fptr1)
                printf("fptr1 eror\n");

            //open file tujuan
            strcpy(filepath2, "FILES/");
            strcat(filepath2, nama);

            fptr2 = fopen(filepath2, "a");
            if(!fptr2)
                printf("fptr2 eror\n");    

            //copy
            char c = fgetc(fptr1);
            while (c != EOF)
            {
                fputc(c, fptr2);
                c = fgetc(fptr1);
            }
            //tambah running.log
            addRunning("Tambah", nama, input_akun);
        }
```

## Perintah 'see'
Memasukkan isi `files.tsv` ke dalam sebuah string lalu kirim ke client untuk di cetak sesuai format keluaran.

---
# Soal 2
Crypto (kamu) adalah teman Loba. Suatu pagi, Crypto melihat Loba yang sedang kewalahan mengerjakan tugas dari bosnya. Karena Crypto adalah orang yang sangat menyukai tantangan, dia ingin membantu Loba mengerjakan tugasnya. Detil dari tugas tersebut adalah:
## 2a
Membuat program perkalian matrix (4x3 dengan 3x6) dan menampilkan hasilnya. Matriks nantinya akan berisi angka 1-20 (tidak perlu dibuat filter angka).
**Jawaban :**
- Membuat dua buah array 2D bertipe `long long` untuk menyimpan input matrix. 
```
    int i, j, k;
    long long size_m1[2], size_m2[2];

    // matriks 1 [row = 4, col = 3]
    size_m1[0] = 4; 
    size_m1[1] = 3; 
    long long m1[size_m1[0]][size_m1[1]];

    // matriks 2 [row = 3, col = 6]
    size_m2[0] = 3; 
    size_m2[1] = 6; 
    long long m2[size_m2[0]][size_m2[1]];

    for (i = 0; i < size_m1[0]; i++)
    {
        for (j = 0; j < size_m1[1]; j++)
        {
            scanf("%lld", &m1[i][j]);
        }
    }

    for (i = 0; i < size_m2[0]; i++)
    {
        for (j = 0; j < size_m2[1]; j++)
        {
            scanf("%lld", &m2[i][j]); 
        }
    }
```
- Melakukan perkalian kedua matrix sesuai ketentuan perkalian matrix 
```
    // perkalian matriks
    long long mresult[size_m1[0]][size_m2[1]];
    memset(mresult, 0, sizeof(mresult));
    for (i = 0; i < size_m2[0]; i++)
    {
        for (j = 0; j < size_m2[1]; j++)
        {
            for (k = 0; k < size_m1[0]; k++) 
            {
                mresult[k][j] += m1[k][i] * m2[i][j];
            }
        }
    }
```
**Output :**

<img src="/soal2/2a.png" width="600">

## 2b
Membuat program dengan menggunakan matriks output dari program sebelumnya (program soal2a.c) (Catatan!: gunakan shared memory). Kemudian matriks tersebut akan dilakukan perhitungan dengan matrix baru (input user) sebagai berikut contoh perhitungan untuk matriks yang a    da. Perhitungannya adalah setiap cel yang berasal dari matriks A menjadi angka untuk faktorial, lalu cel dari matriks B menjadi batas maksimal faktorialnya matri(dari paling besar ke paling kecil) (Catatan!: gunakan thread untuk perhitungan di setiap cel). 
**Ketentuan :**
- If a >= b  -> a!/(a-b)!
- If b > a -> a!
- If 0 -> 0

**Jawaban :**
- Membuat shared memory pada `soal2a.c` berupa array 2D bertipe `long long`, yaitu pada variabel `long long (* value)[size_m2[1]]`
```
// shared memory
    key_t key = 1234;
    long long (* value)[size_m2[1]];

    int shm_id = shmget(key, sizeof(long long[size_m1[0]][size_m2[1]]), IPC_CREAT | 0666);
    value = shmat(shm_id, NULL, 0);

    printf("\nMultiplication Result Matrix : \n");
    for (i = 0; i < size_m1[0]; i++)
    {
        for (j = 0; j < size_m2[1]; j++)
        {
            value[i][j] = mresult[i][j];
            printf("%-2lld ", value[i][j]);
        }
        printf("\n");
    }

    shmdt((void *) value);
```
- Membuat variabel untuk menyimpan input matrix yang baru array 2D bertipe `long long`
```
    int i, j, k, num;
    long long size_m[2];

    // matriks result [row = 4, col = 6]
    size_m[0] = 4; 
    size_m[1] = 6; 
    long long m[size_m[0]][size_m[1]];

    for (i = 0; i < size_m[0]; i++)
    {
        for (j = 0; j < size_m[1]; j++)
        {
            scanf("%lld", &m[i][j]);
        }
    }
```
- Menerima hasil shared memory pada `soal2b.c`
```
    // shared memory
    key_t key = 1234;

    int shm_id = shmget(key, sizeof(long long[size_m[0]][size_m[1]]), IPC_CREAT | 0666);
    value = shmat(shm_id, NULL, 0);

    printf("\nShared Memory Matrix : \n");
    for (i = 0; i < size_m[0]; i++)
    {
        for (j = 0; j < size_m[1]; j++)
        {
            printf("%-2lld ", value[i][j]);
        }
        printf("\n");
    }
    printf("\n");
```
- Membuat `thread` untuk melakukan perkalian antara input matrix yang baru sebagai B dan matrix hasil shared memory sesuai ketentuan di atas
    **Ketentuan :**
    - If a >= b  -> a!/(a-b)!
    - If b > a -> a!
    - If 0 -> 0
```
    int count = 0;
    pthread_t t_id[size_m[0] * size_m[1]];
    for (i = 0; i < size_m[0]; i++)
    {
        for (j = 0; j < size_m[1]; j++)
        {
            long long data[3];
            data[0] = i;
            data[1] = j;
            data[2] = m[i][j];

            pthread_create(&t_id[count], NULL, fact_result, (void *)data);

            pthread_join(t_id[count++], NULL);
        }
    }
```
Dengan definisi fungsi `fact_result` sebagai berikut:
```
void * fact_result(void * arr)
{
    int i;
    long long *data = (long long *)arr;
    if (data[2] == 0) 
    {
        value[data[0]][data[1]] = 0;
    }
    else 
    {
        long long x = value[data[0]][data[1]];
        long long fact = x;

        for (i = 0; i < data[2]; i++)
        {
            if (x > 0)
            {
                fact *= x;
            }
            else
            {
                break;
            }
            x--;
        }

        value[data[0]][data[1]] = fact;
    }

}
```
- Terakhir, mencetak hasil perkalian matrix
```
    printf("Result Matrix : \n");
    for (i = 0; i < size_m[0]; i++)
    {
        for (j = 0; j < size_m[1]; j++)
        {
            printf("%-2lld ", value[i][j]);
        }
        printf("\n");
    }

    shmdt(value);
    shmctl(shm_id, IPC_RMID, NULL);
    exit(0);
```
**Output :**

<img src="/soal2/2b.png" width="600">

## 2c
Karena takut lag dalam pengerjaannya membantu Loba, Crypto juga membuat program (soal2c.c) untuk mengecek 5 proses teratas apa saja yang memakan resource komputernya dengan command “ps aux | sort -nrk 3,3 | head -5” (Catatan!: Harus menggunakan IPC Pipes)
**Jawaban :**
- Mendeklarasikan variabel `command` yang diperlukan sebagai variabel global
```
typedef int pipes[2];
char *argv0[] = {"ps", "aux", NULL};
char *argv1[] = {"sort", "-nrk", "3,3", NULL};
char *argv2[] = {"head", "-5", NULL};

static char **argvs[] = {argv0, argv1, argv2};
static int n_argv = sizeof(argvs) / sizeof(argvs[0]);
```
- Eksekusi `pipe`
```
static void exec_pipe(int n_argv, char ***argvs, pipes output);

static void exec_command(int n_argv, char ***argvs) 
{
    if (n_argv > 1) 
    {
        pid_t pid;
        pipes input;

        if (pipe(input) != 0)
        {
            exit(1);
        }
            
        pid = fork();
        if (pid < 0)
        {
            exit(1);
        }
        if (pid == 0) 
        {
            exec_pipe(n_argv - 1, argvs, input); 
        }

        close(0);
        dup(input[0]);

        close(input[0]);
        close(input[1]);
    }
    execvp(argvs[n_argv - 1][0], argvs[n_argv - 1]);
}

static void exec_pipe(int n_argv, char ***argvs, pipes output) 
{
    close(1);
    dup(output[1]);

    close(output[0]);
    close(output[1]);
    
    exec_command(n_argv, argvs);
}

int main(int argc, char **argv) 
{
    exec_command(n_argv, argvs);
    return(0);
}
```
**Output :**

<img src="/soal2/2c.png" width="600">

---

# Soal 3
Seorang mahasiswa bernama Alex sedang mengalami masa gabut. Di saat masa gabutnya, ia memikirkan untuk merapikan sejumlah file yang ada di laptopnya. Karena jumlah filenya terlalu banyak, Alex meminta saran ke Ayub. Ayub menyarankan untuk membuat sebuah program C agar file-file dapat dikategorikan. Program ini akan memindahkan file sesuai ekstensinya ke dalam folder sesuai ekstensinya yang folder hasilnya terdapat di working directory ketika program kategori tersebut dijalankan.
## 3a
Program menerima opsi -f seperti contoh di atas, jadi pengguna bisa menambahkan argumen file yang bisa dikategorikan sebanyak yang diinginkan oleh pengguna. 
Output yang dikeluarkan adalah seperti ini :
```
    File 1 : Berhasil Dikategorikan (jika berhasil)
    File 2 : Sad, gagal :( (jika gagal)
    File 3 : Berhasil Dikategorikan
```
## 3b
Program juga dapat menerima opsi -d untuk melakukan pengkategorian pada suatu directory. Namun pada opsi -d ini, user hanya bisa memasukkan input 1 directory saja, tidak seperti file yang bebas menginput file sebanyak mungkin. Contohnya adalah seperti ini:
```
    $ ./soal3 -d /path/to/directory/
```
Perintah di atas akan mengkategorikan file di /path/to/directory, lalu hasilnya akan disimpan di working directory dimana program C tersebut berjalan (hasil kategori filenya bukan di /path/to/directory).
Output yang dikeluarkan adalah seperti ini :
```
    Jika berhasil, print “Direktori sukses disimpan!”
    Jika gagal, print “Yah, gagal disimpan :(“
```
## 3c
Selain menerima opsi-opsi di atas, program ini menerima opsi *, contohnya ada di bawah ini:
```
    $ ./soal3 \*
```
Opsi ini akan mengkategorikan seluruh file yang ada di working directory ketika menjalankan program C tersebut.
## 3d
Semua file harus berada di dalam folder, jika terdapat file yang tidak memiliki ekstensi, file disimpan dalam folder “Unknown”. Jika file hidden, masuk folder “Hidden”.
## 3e
Setiap 1 file yang dikategorikan dioperasikan oleh 1 thread agar bisa berjalan secara paralel sehingga proses kategori bisa berjalan lebih cepat.

**Jawaban :**
- Membuat fungsi untuk mengkategorikan
```
void categorize(char *arg)
{
    char name[500];
    strcpy(name, arg);
    char *type;

    if (name[0] == '.')
    {
        strcpy(type, "hidden");
    }
    else if (strchr(name, '.') == NULL)
    {
        strcpy(type, "unknown");
    }
    else
    {
        type = strtok(name,".");
        type = strtok(NULL,".");
    }
    mkdir(type, S_IRWXU);

    char name2[500];
    strcpy(name2, arg);
    char path[500];
    strcat(path, type);
    strcat(path,"/");
    strcat(path,name2);
    rename(name2,path);
}
```
- Membuat fungsi untuk melist file
```
void listFiles(char *path)
{
    char fpath[1000];

    struct dirent *dp;
    DIR *dir = opendir(path);

    char wdir[1000];
    getcwd(wdir, sizeof(wdir));

    int threads = 0;

    if (!dir)
        return;
    while ((dp = readdir(dir)) != NULL)
    {
        if (!strcmp(dp->d_name, ".") && !strcmp(dp->d_name, ".."))
        {
            strcpy(fpath, path);
            strcat(fpath, "/");
            strcat(fpath, dp->d_name);
            if (dp->d_type == DT_REG)
            {
                pthread_create(&tid[threads], NULL, cthread, fpath);
                threads++;
            }
        }
        else if (dp->d_name[0] != '.')
            listFiles(fpath);
    }

    for (size_t i = 0; i < threads; i++)
    {
        pthread_join(tid[i], NULL);
    }
}
```
Dengan definisi fungsi `cthread` sebagai berikut
```
void * cthread(void *arg)
{
    char *name;
    strcpy(name, arg);
    categorize(name);
}

```
- Dan menjalankan keseluruhan
```
     char wdir[1000];
    getcwd(wdir, sizeof(wdir));

    if (strcmp(argv[1], "-f") == 0)
    {
        int err;
        int threads = 0;
        for (size_t i = 2; i < argc; i++)
        {
            err = pthread_create(&(tid[i - 2]), NULL, &cthread, argv[i]);
            if (err)
                printf("\n Thread create failed");
            else
                threads++;

        }
        for (size_t i = 0; i < threads; i++)
        {
            pthread_join(tid[i], NULL);
        }
    }
    else if ((strcmp(argv[1], "-d") == 0))
        listFiles(argv[2]);
    else if ((strcmp(argv[1], "\*") == 0))
        listFiles(wdir);
```

