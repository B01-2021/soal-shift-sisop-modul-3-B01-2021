#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include <unistd.h>

void main()
{
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
}