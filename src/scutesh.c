#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>
#include <sys/wait.h>
#include "lib/get_input.h"

void exec_cmd(char **cmd);

int main(void) 
{
    char **command;
    char *input;

    char cmd_list[10][10];

    while (1) {
        // read what is passed to shell and parse it to separate
        // commands and args
        input = readline("scutesh> ");
        command = get_input(input);


        exec_cmd(command);
        free(input);
        free(command);
    }
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