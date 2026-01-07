#include <stdio.h>
#include <unistd.h>
int main()
{
    pid_t id = fork();
    if (id == 0)
    {
        printf("child process\n. pid = %d\n", id);
    }
    else
    {
        printf("parent process\n. Child pid = %d\n", id);
    }
    return 0;
}