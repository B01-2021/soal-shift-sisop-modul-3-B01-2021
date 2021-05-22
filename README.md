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
#### perintah 'add'
mengcopy perkarakter file text dari pathfile yang diinput ke file baru yang dimasukkan ke dalam direktori Server/FILES/nanafile.ekstensi
lalu membuat sebuah string yang berisi (nama file, publisher, tahun publikasi, ekstensi, filepath) yang kemudian di mamsukkan ke file files.tsv sebagai sebuah baris

#### perintah 'see'
memasukkan isi files.tsv ke dalam sebuah string lalu kirim ke client untuk di cetak sesuai format keluaran.

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