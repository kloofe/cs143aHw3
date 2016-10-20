#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char ** args) {
    int k = 10;
    int status;
    char letter;
    if(argc >= 2) {
        k = atoi(args[1]);
    }

    pid_t pid;
    pid_t pid2;
    pid_t pid3;
    pid = fork();
    if(pid > 0) {
        pid2 = fork();
        if(pid2 > 0) {
            letter = 'B';
            pid3 = fork();
            if(pid3 > 0) {
                letter = 'A';
            }
        }
        else {
            letter = 'C';
        }
    }
    else {
        letter = 'D';
    }
    int i;
    int c;
    for(i = 0; i < k; i++) {
        
        printf("%c", letter);
        fflush(stdout);
    }
    

    while((pid = wait(&status)) > 0);
    return 0;
}
