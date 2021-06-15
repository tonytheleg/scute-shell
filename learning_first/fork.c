/* Fork creates a copy of the current process to create a 
* child process. It will have its own PID. This is to allow for
* the shell to run in th emain thread, and commands entered
* to run in their own process shell so if it fails it doesn't
* break the main shell thread
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    // Creates a child_pid with the call to fork()
    pid_t child_pid = fork();

    // The conditional below checks the current value of the child_process
    // If we are in the parent process, child_pid is the actual child PID, else
    // we are in the child process and child pid is 0 since it doesnt have a child
    // The order in which things are exectued  is up to OS scheduler
    if (child_pid == 0) {
        printf("### Child ###\nCurrent PID: %d and Child PID: %d\n",
        getpid(), child_pid);
    } else {
        sleep(1);
        printf("### Parent ###\nCurrent PID: %d and Child PID: %d\n",
        getpid(), child_pid);
    }
    
    return 0;
}