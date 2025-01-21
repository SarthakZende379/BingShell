#include "shell.h"

int handle_redirection(char **args) {
    int in_fd = -1, out_fd = -1;
    int i;

    // First pass: check for redirections
    for (i = 0; args[i] != NULL; i++) {
        // Input redirection
        if (strcmp(args[i], "<") == 0) {
            if (args[i + 1] == NULL) {
                printf("bingshell: syntax error near '<'\n");
                return 1;
            }
            in_fd = open(args[i + 1], O_RDONLY);
            if (in_fd == -1) {
                perror("bingshell");
                return 1;
            }
            // Remove redirection and filename from args
            args[i] = NULL;
            i++;
        }
        // Output redirection
        else if (strcmp(args[i], ">") == 0) {
            if (args[i + 1] == NULL) {
                printf("bingshell: syntax error near '>'\n");
                return 1;
            }
            out_fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (out_fd == -1) {
                perror("bingshell");
                return 1;
            }
            // Remove redirection and filename from args
            args[i] = NULL;
            i++;
        }
        // Pipe handling
        else if (strcmp(args[i], "|") == 0) {
            if (args[i + 1] == NULL) {
                printf("bingshell: syntax error near '|'\n");
                return 1;
            }
            
            int pipefd[2];
            if (pipe(pipefd) == -1) {
                perror("bingshell");
                return 1;
            }
            
            pid_t pid1 = fork();
            if (pid1 == -1) {
                perror("bingshell");
                close(pipefd[0]);
                close(pipefd[1]);
                return 1;
            }
            
            if (pid1 == 0) {
                // First child process
                close(pipefd[0]);
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[1]);
                
                args[i] = NULL;  // Terminate first command
                execvp(args[0], args);
                perror("bingshell");
                exit(EXIT_FAILURE);
            }
            
            pid_t pid2 = fork();
            if (pid2 == -1) {
                perror("bingshell");
                close(pipefd[0]);
                close(pipefd[1]);
                return 1;
            }
            
            if (pid2 == 0) {
                // Second child process
                close(pipefd[1]);
                dup2(pipefd[0], STDIN_FILENO);
                close(pipefd[0]);
                
                execvp(&args[i + 1][0], &args[i + 1]);
                perror("bingshell");
                exit(EXIT_FAILURE);
            }
            
            // Parent process
            close(pipefd[0]);
            close(pipefd[1]);
            waitpid(pid1, NULL, 0);
            waitpid(pid2, NULL, 0);
            return 1;
        }
    }

    // Apply redirections if any
    if (in_fd != -1) {
        dup2(in_fd, STDIN_FILENO);
        close(in_fd);
    }
    if (out_fd != -1) {
        dup2(out_fd, STDOUT_FILENO);
        close(out_fd);
    }

    return 0;
}