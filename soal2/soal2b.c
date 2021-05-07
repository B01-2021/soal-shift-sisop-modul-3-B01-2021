#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include <unistd.h>

pthread_t tid[3];
pid_t child;

int (* value)[6] = {0};

void * fact_result(void * arr)
{
    int i;
    int *data = (int *)arr;
    if (data[2] == 0) 
    {
        value[data[0]][data[1]] = 0;
    }
    else 
    {
        int x = value[data[0]][data[1]];
        int fact = x;

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
void main()
{
    int i, j, k, num;
    int size_m[2];

    // matriks result [row = 4, col = 6]
    size_m[0] = 4; 
    size_m[1] = 6; 
    int m[size_m[0]][size_m[1]];

    for (i = 0; i < size_m[0]; i++)
    {
        for (j = 0; j < size_m[1]; j++)
        {
            scanf("%d", &m[i][j]);
        }
    }

    // for (i = 0; i < size_m[0]; i++)
    // {
    //     for (j = 0; j < size_m[1]; j++)
    //     {
    //         printf("%d ", m[i][j]);
    //     }
    //     printf("\n");
    // }

    // shared memory
    key_t key = 1234;

    int shm_id = shmget(key, sizeof(int[size_m[0]][size_m[1]]), IPC_CREAT | 0666);
    value = shmat(shm_id, NULL, 0);

    int count = 0;
    pthread_t t_id[size_m[0] * size_m[1]];
    for (i = 0; i < size_m[0]; i++)
    {
        for (j = 0; j < size_m[1]; j++)
        {
            int data[3];
            data[0] = i;
            data[1] = j;
            data[2] = m[i][j];
            pthread_create(&t_id[count], NULL, fact_result, (void *)data);

            pthread_join(t_id[count++], NULL);
        }
    }

    printf("Result Matrix : \n");
    for (i = 0; i < size_m[0]; i++)
    {
        for (j = 0; j < size_m[1]; j++)
        {
            printf("%-2d ", value[i][j]);
        }
        printf("\n");
    }

    shmdt(value);
    shmctl(shm_id, IPC_RMID, NULL);
    exit(EXIT_SUCCESS);
}