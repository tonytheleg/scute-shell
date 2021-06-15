#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

// get_input returns a pointer to a pointer, taking the 
// command passed to the shell by user
char **get_input(char *input) {
    char **command = malloc(BUFFER_SIZE * sizeof(char *));
    if (command == NULL) {
        perror("malloc failed");
        exit(1);
    }
    char *separator = " ";
    char *parsed;
    int index = 0;

    // splits the command and args into an array until
    // it hits a null operator
    parsed = strtok(input, separator);
    while (parsed != NULL) {
        command[index] = parsed;
        index++;

        parsed = strtok(NULL, separator);
    }

    command[index] = NULL;
    return command;
}