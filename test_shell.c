#include "shell.h"
#include <assert.h>

// Test basic command execution
void test_basic_commands() {
    printf("\n=== Testing Basic Commands ===\n");
    
    // Test pwd
    printf("Testing pwd:\n");
    char *pwd_args[] = {"pwd", NULL};
    execute_command(pwd_args);
    
    // Test cd
    printf("\nTesting cd to /tmp:\n");
    char *cd_args[] = {"cd", "/tmp", NULL};
    execute_command(cd_args);
    execute_command(pwd_args);
}

// Test history functionality
void test_history() {
    printf("\n=== Testing History ===\n");
    
    add_to_history("test command 1");
    add_to_history("test command 2");
    add_to_history("test command 3");
    
    printf("History should show 3 commands:\n");
    show_history();
}

// Test I/O redirection
void test_io() {
    printf("\n=== Testing I/O Redirection ===\n");
    
    // Create a test file
    FILE *fp = fopen("test_input.txt", "w");
    fprintf(fp, "Hello\nWorld\n");
    fclose(fp);
    
    // Test input redirection
    printf("Testing input redirection (cat < test_input.txt):\n");
    char *cat_args[] = {"cat", "<", "test_input.txt", NULL};
    execute_command(cat_args);
    
    // Test output redirection
    printf("\nTesting output redirection (ls > test_output.txt):\n");
    char *ls_args[] = {"ls", ">", "test_output.txt", NULL};
    execute_command(ls_args);
    
    // Verify output
    printf("\nContents of test_output.txt:\n");
    char *verify_args[] = {"cat", "test_output.txt", NULL};
    execute_command(verify_args);
}

// Cleanup function
void cleanup_tests() {
    unlink("test_input.txt");
    unlink("test_output.txt");
}

int main() {
    printf("Starting BingShell Tests\n");
    
    test_basic_commands();
    test_history();
    test_io();
    
    cleanup_tests();
    printf("\nAll tests completed!\n");
    return 0;
}