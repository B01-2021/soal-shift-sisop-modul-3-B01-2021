#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <unistd.h>

int fileExists(const char *fname)
{
    struct stat buffer;
    int exist = stat(fname, &buffer);
    if (exist == 0)
        return 1;
    else
        return 0;
}

void * move(void *path)
{
    char cwd[4096];
    char dname[200], hidden[100], fname[100];
    strcpy(hidden, path);
    char *temp = strrchr(hidden, '/');
    strcpy(hidden, temp);

    if (hidden[1] == '.')
    {
        strcpy(dname, "Hidden");
    }
    else if (strstr(path, ".") != NULL)
    {
        strcpy(fname, path);
        strtok(fname, ".");
        char *token = strtok(NULL, "");
        int i;
        for (i = 0; token[i]; i++)
        {
            token[i] = tolower(token[i]);
        }
        strcpy(dname, token);
    }
    else
    {
        strcpy(dname, "Unknown");
    }

    if (fileExists(path))
        mkdir(dname, S_IRWXU);

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        char *name = strrchr(path, '/');
        char absPath[200];
        strcpy(absPath, cwd);
        strcat(absPath, "/");
        strcat(absPath, dname);
        strcat(absPath, name);

        rename(path, absPath);
    }
}

void listFilesRecursively(char *basePath)
{
    char path[4096];
    struct dirent *dp;
    struct stat buffer;
    DIR *dir = opendir(basePath);
    int n = 0;

    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            if (stat(path, &buffer) == 0 && S_ISREG(buffer.st_mode))
            {
                pthread_t thread;
                int err = pthread_create(&thread, NULL, move, (void *)path);
                pthread_join(thread, NULL);
            }

            listFilesRecursively(path);
        }
    }
    closedir(dir);
}

int main(int argc, char *argv[])
{
    char cwd[4096];

    if (strcmp(argv[1], "-f") == 0)
    {
        pthread_t thread;
        int i;
        for (i = 2; i < argc; i++)
        {
            if (fileExists(argv[i]))
            {
                printf("File %d : Berhasil Dikategorikan\n", i - 1);
            }
            else
            {
                printf("File %d : Sad, gagal :(\n", i - 1);
            }
            int err = pthread_create(&thread, NULL, move, (void *)argv[i]);
        }
        pthread_join(thread, NULL);
    }
    else
    {
        if (strcmp(argv[1], "*") == 0)
        {
            if (getcwd(cwd, sizeof(cwd)) != NULL)
            {
                listFilesRecursively(cwd);
            }
        }

        else if (strcmp(argv[1], "-d") == 0)
        {
            listFilesRecursively(argv[2]);
            struct stat buffer;
            int err = stat(argv[2], &buffer);
            if (err == -1)
            {
                printf("Yah, gagal disimpan :(\n");
            }
            else
            {
                printf("Direktori sukses disimpan!\n");
            }
        }
    }
}
