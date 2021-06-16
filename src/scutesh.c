#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>
#include <sys/wait.h>
#include "lib/get_input.h"
#include <stdbool.h>

void exec_cmd(char **cmd);

int main(void) 
{
    char **command;
    char *input;
    char cmd_list[2][10] = {"scutecd", "scutels"};
    int arrlen = sizeof(cmd_list) / sizeof(cmd_list[0]);
    bool builtin;

    while (1) {
        // read what is passed to shell and parse it to separate
        // commands and args
        input = readline("scutesh> ");
        command = get_input(input);
        printf("%s\n", command[0]);
        
        /* create an array of builtin commands
        if command is in array, exec that command,
        otherwise use system command
        */
        for (int i = 0; i < arrlen; i++) {
            if (strcmp(command[0], cmd_list[i]) == 0) {
                builtin = true;
            }
        }
        if (builtin) {
            exec_builtin(command);
        } else {
            exec_cmd(command);
        }
    }
}

void exec_builtin(char **cmd) 
{

}

void exec_cmd(char **cmd) {
    pid_t child_pid;
    int stat_loc;
    
    // fork and execute the command by changing the child
    // process to be the executed command
    child_pid = fork();
    
    // check to make sure fork didnt fail
    if (child_pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    if (child_pid == 0) {
        //execute command in place os fork process
        if (execvp(cmd[0], cmd) < 0) {
            perror(cmd[0]);
            exit(1);
        }
    } else {
        waitpid(child_pid, &stat_loc, WUNTRACED);
    }
}