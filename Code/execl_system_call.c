#include <unistd.h>
#include <stdio.h>
int main()
{
    printf("Before exec()\n");
    execl("/bin/ls", "ls", "-l", NULL);
    printf("After exec()\n");
}
