#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int isEmpty(const char *s) {
    while(*s) {
        if(!isspace(*s)) {
            return 0;
        }
        s++;
    }
    return 1;
}

void parseline(char* command, char** arg) {
    int index = 0;
    char* tok;
    tok = strtok(command, "\t \n");
    arg[index] = tok;
    while((tok = strtok(NULL, "\t \n")) != NULL) {
        index++;
        arg[index] = tok;
    }
    arg[index+1] = NULL;

}

void eval() {
    char *args[1024];
    int child_status;
    int bg;
    pid_t pid;
    char command[1024];
    char *com = command;
    size_t bufsize = 1024;
    size_t comLen;

    printf("$ ");
    fflush(stdout);
    comLen = getline(&com, &bufsize, stdin);
    if(comLen == -1) {
        do {
            waitpid(pid, &child_status, WUNTRACED);
        } while(!WIFEXITED(child_status) && !WIFSIGNALED(child_status));
        exit(0);
 
    }
    else if(isEmpty(command)) {
        return;
    }
    

    parseline(command, args);

    pid = fork();
    if(pid == 0) {
        if(execvp(args[0], args) < 0) {
            printf("Command not found\n");
            fflush(stdout);
            exit(0);
        }
    }
    else if(pid == -1) {
        printf("Failed to fork\n");
    }
    else {
        do {
            waitpid(pid, &child_status, WUNTRACED);
        } while(!WIFEXITED(child_status) && !WIFSIGNALED(child_status));
    }
    
}

int main() {
    int option = 0;
    do {
        eval();
    } while(option != 1);

    return 0;
}
