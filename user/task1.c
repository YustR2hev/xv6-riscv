#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    if(argc < 2){
        printf("Usage: proc_test a|b\n");
        exit(1);
    }

    int pid = fork();

    if(pid < 0){
        printf("Fork failed\n");
        exit(1);
    }

    if(pid == 0){
        volatile int i;
        for(i = 0; i < 100000000; i++);
        exit(1);
    }
    else {
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);

        int status;

        if(argv[1][0] == 'a'){
            int wpid = wait(&status);
            printf("Child %d exited with status %d\n", wpid, status);
        }
        else if(argv[1][0] == 'b'){
            kill(pid);
            int wpid = wait(&status);
            printf("Child %d killed, status %d\n", wpid, status);
        }

        exit(0);
    }
}
