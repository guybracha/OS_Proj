#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myShell.h"  // Include myShell.h for MAX_INPUT_LENGTH and function prototypes
#include "myFunction.h"  // Include myFunction.h for other function prototypes

int main() {
    char input[MAX_INPUT_LENGTH];
    char **args;
    int status;

    wellcome();

    while (1) {
        getLocation();  // Print current location (e.g., current directory)

        printf("$ ");
        fgets(input, MAX_INPUT_LENGTH, stdin); // Read user input

        // Remove trailing newline character
        input[strcspn(input, "\n")] = '\0';

        // Split input into arguments
        args = splitArgument(input);

        // Check for built-in commands
        if (args[0] != NULL) {
            if (strcmp(args[0], "exit") == 0) {
                logout(args[0]); // Exit the shell
                break;
            } else if (strcmp(args[0], "cd") == 0) {
                cd(args); // Change directory
                continue;
            } else if (strcmp(args[0], "cp") == 0) {
                cp(args); // Copy file
                continue;
            } else if (strcmp(args[0], "delete") == 0) {
                delete(args); // Delete file
                continue;
            } else if (strcmp(args[0], "move") == 0) {
                move(args); // Move file
                continue;
            } else if (strcmp(args[0], "wordcount") == 0) {
                wordCount(args); // Word count in a file
                continue;
            } else if (strcmp(args[0], "read") == 0) {
                myRead(args); // Read file
                continue;
            } else if (strcmp(args[0], "echoppend") == 0) {
                echoppned(args); // Echo to file (append)
                continue;
            } else if (strcmp(args[0], "echorite") == 0) {
                echorite(args); // Echo to file (overwrite)
                continue;
            }
        }

        // Check if the command execution was successful
        if (status == -1) {
            printf("Error: Command execution failed.\n");
        }

        // Free memory allocated for arguments
        free(args);
    }

    return 0;
}
