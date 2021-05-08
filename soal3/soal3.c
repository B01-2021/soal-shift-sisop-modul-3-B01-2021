#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>

pthread_t tid[100];
pid_t child;

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

void * cthread(void *arg)
{
    char *name;
    strcpy(name, arg);
    categorize(name);
}

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

int main(int argc, char const *argv[])
{
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

    return 0;
}
