#include "shell.h"

int execute_command(char **args) {
    int background = 0;
    
    // Check if command should run in background
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "&") == 0) {
            background = 1;
            args[i] = NULL;
            break;
        }
    }

    // Check for built-in commands
    if (handle_builtin(args)) {
        return 1;
    }

    // Check for redirections and pipes
    if (handle_redirection(args)) {
        return 1;
    }

    // Fork and execute command
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
            printf("bingshell: command not found: %s\n", args[0]);
            exit(EXIT_FAILURE);
        }
    } else if (pid < 0) {
        perror("fork");
    } else {
        // Parent process
        if (!background) {
            waitpid(pid, NULL, 0);
        } else {
            // Add to jobs list
            jobs[job_count].pid = pid;
            strcpy(jobs[job_count].command, args[0]);
            jobs[job_count].running = 1;
            printf("[%d] %d\n", job_count + 1, pid);
            job_count++;
        }
    }

    return 1;
}

int handle_builtin(char **args) {
    if (strcmp(args[0], "exit") == 0) {
        printf("Goodbye!\n");
        exit(0);
        return 1;
    }
    if (strcmp(args[0], "help") == 0) {
        printf("\nBingShell - Available Commands:\n");
        printf("Built-in commands:\n");
        printf("  cd [dir]     - Change current directory\n");
        printf("  pwd          - Print working directory\n");
        printf("  history      - Show command history\n");
        printf("  jobs         - Show background jobs\n");
        printf("  help         - Show this help message\n");
        printf("  exit         - Exit the shell\n\n");
        printf("Special features:\n");
        printf("  command &    - Run command in background\n");
        printf("  cmd > file   - Redirect output to file\n");
        printf("  cmd < file   - Read input from file\n");
        printf("  cmd1 | cmd2  - Pipe output of cmd1 to cmd2\n\n");
        return 1;
    }
    if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            chdir(getenv("HOME"));
        } else {
            if (chdir(args[1]) != 0) {
                perror("cd");
            }
        }
        return 1;
    }
    if (strcmp(args[0], "pwd") == 0) {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s\n", cwd);
        }
        return 1;
    }
    if (strcmp(args[0], "history") == 0) {
        show_history();
        return 1;
    }
    if (strcmp(args[0], "jobs") == 0) {
        for (int i = 0; i < job_count; i++) {
            if (jobs[i].running) {
                printf("[%d] %d %s\n", i + 1, jobs[i].pid, jobs[i].command);
            }
        }
        return 1;
    }
    return 0;
}

void add_to_history(char *command) {
    if (history_count < HISTORY_SIZE) {
        strcpy(history[history_count], command);
        history_count++;
    } else {
        for (int i = 0; i < HISTORY_SIZE - 1; i++) {
            strcpy(history[i], history[i + 1]);
        }
        strcpy(history[HISTORY_SIZE - 1], command);
    }
}

void show_history(void) {
    for (int i = 0; i < history_count; i++) {
        printf("%d %s\n", i + 1, history[i]);
    }
}