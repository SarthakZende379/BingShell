#include "shell.h"

void shell_loop(void) {
    char line[MAX_LINE];
    char *args[MAX_ARGS];
    char *token;
    int status = 1;

    signal(SIGINT, handle_signal);   // Handle Ctrl-C
    signal(SIGTSTP, handle_signal);  // Handle Ctrl-Z

    while (status) {
        printf(PROMPT);
        fflush(stdout);

        // Read command line
        if (!fgets(line, MAX_LINE, stdin)) {
            if (feof(stdin)) {
                printf("\n");
                break;
            }
            continue;
        }

        // Remove trailing newline
        line[strcspn(line, "\n")] = 0;

        // Add command to history
        if (strlen(line) > 0) {
            add_to_history(line);
        }

        // Split line into arguments
        int i = 0;
        token = strtok(line, " ");
        while (token != NULL && i < MAX_ARGS - 1) {
            args[i] = token;
            token = strtok(NULL, " ");
            i++;
        }
        args[i] = NULL;

        if (args[0] != NULL) {
            status = execute_command(args);
        }
    }
}

int main(void) {
    printf("Welcome to BingShell! Type 'help' for commands.\n");
    shell_loop();
    return 0;
}

void handle_signal(int sig) {
    if (sig == SIGINT) {
        printf("\n%s", PROMPT);
        fflush(stdout);
    }
    if (sig == SIGTSTP) {
        printf("\n%s", PROMPT);
        fflush(stdout);
    }
}