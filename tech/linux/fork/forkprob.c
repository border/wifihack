#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>

void unix_error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

pid_t Fork(void)
{
    pid_t pid;
    if((pid = fork()) < 0) {
        unix_error("fork error");
    }
    return pid;
}


void doit()
{
    Fork();
    Fork();
    printf("Hello - doit\n");
    return;
}
int main(void)
{
    int x = 1;
    if(Fork() == 0) {
        printf("printf1: x=%d\n", ++x);
        exit(0);
    }
    printf("printf2: x=%d\n", --x);
    exit(0);
}
