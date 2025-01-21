#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_LINE 1024
#define MAX_ARGS 64
#define HISTORY_SIZE 10
#define MAX_JOBS 10
#define PROMPT "bingshell> "

// Simple job structure
typedef struct {
    pid_t pid;
    char command[MAX_LINE];
    int running;
} Job;

// Global variables
extern Job jobs[MAX_JOBS];
extern int job_count;
extern char history[HISTORY_SIZE][MAX_LINE];
extern int history_count;

// Function declarations
void shell_loop(void);
int execute_command(char **args);
int handle_builtin(char **args);
void handle_signal(int sig);
void add_to_history(char *command);
void show_history(void);
int handle_redirection(char **args);

#endif