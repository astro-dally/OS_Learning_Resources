// // Mini terminal - use fork, execvp, waitpid
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <sys/wait.h>

// #define MAX_LINE 1024
// #define MAX_ARGS 64

// int main() {
//     char line[MAX_LINE];
//     char *args[MAX_ARGS];
//     pid_t pid;
//     int status;

//     while (1) {
//         printf("mini_shell> ");
//         if (fgets(line, MAX_LINE, stdin) == NULL) {
//             break;
//         }

//         // Parse the input
//         int i = 0;
//         args[i] = strtok(line, DELIMITERS);
//         while (args[i] != NULL && i < MAX_ARGS - 1) {
//             i++;
//             args[i] = strtok(NULL, DELIMITERS);
//         }
//         args[i] = NULL;

//         if (args[0] == NULL) {
//             continue;
//         }

//         pid = fork();
//         if (pid < 0) {
//             perror("fork");
//             exit(EXIT_FAILURE);
//         } else if (pid == 0) {
//             // Child process
//             if (execvp(args[0], args) == -1) {
//                 perror("execvp");
//                 exit(EXIT_FAILURE);
//             }
//         } else {
//             // Parent process
//             if (waitpid(pid, &status, 0) == -1) {
//                 perror("waitpid");
//                 exit(EXIT_FAILURE);
//             }
//         }
//     }

//     return 0;
// }

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX_LEN 1024
#define MAX_ARGS 64
// Parse input command into argument list
void parse(char *cmd, char **args)
{
    int i = 0;
    args[i] = strtok(cmd, " \t\n");
    while (args[i] && i < MAX_ARGS - 1)
        args[++i] = strtok(NULL, " \t\n");
    args[i] = NULL;
}
// Execute command using fork + exec
void execute(char **args)
{
    pid_t pid = fork();
    if (pid == 0)
    { // Child
        execvp(args[0], args);
        perror("Command not found"); // Only if exec fails
        _exit(1);
    }
    else
    {
        wait(NULL); // Parent waits
    }
}
int main()
{
    char cmd[MAX_LEN];
    char *args[MAX_ARGS];
    while (1)
    {
        printf("myshell> "); // Display prompt
        if (!fgets(cmd, MAX_LEN, stdin))
            break;
        if (cmd[0] == '\n') // Ignore empty input
            continue;
        parse(cmd, args);
        if (strcmp(args[0], "exit") == 0)
            break;
        execute(args);
    }
    return 0;
}