#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef int pipes[2];
char *argv0[] = {"ps", "aux", NULL};
char *argv1[] = {"sort", "-nrk", "3,3", NULL};
char *argv2[] = {"head", "-5", NULL};

static char **argvs[] = {argv0, argv1, argv2};
static int n_argv = sizeof(argvs) / sizeof(argvs[0]);

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