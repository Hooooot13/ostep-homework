/*
Write a program that:
- opens a file (with the open() system call)
- then calls fork() to create a new process. 

Q: Can both the child and parent access the file descriptor returned by open()? 
A: I think that both processes will be able to acces the file desriptor.

Q: What happens when they are writing to the file concurrently, i.e., at the same time?
A: I am not sure. If the processies execut one after the other then I don't forsee an issue 
    However if the OS switches processies when the I/O call goes out then the other process might start trying to write to the file and I don't know what will happen in that case
Result: Yeah so both processies just kept switching between between as they wrote to the file pretty much as predicted
*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h> //strlen()
#include <sys/stat.h> //chmod()
#include <unistd.h> //fork(), exec(), wait()
#include <fcntl.h> //open()

int main(){

    int fd = open("Q2.Test", O_WRONLY|O_APPEND|O_CREAT, S_IRWXU);
    if (fd == -1){
        printf("open() failed %d\n", errno);
        return 1;
    }

    char string1[29] = "Writing to file before fork\n";
    write(fd, &string1, strlen(string1));

    int rc = fork();
    if (rc < 0){
        fprintf(stderr, "fork faild");
    } 
    else if (rc == 0) {
        printf("Child process : %i\n", getpid());
        char childString[14] = "Child Writing\n";
        for (int i = 0; i < 1000; i++) {
            write(fd, childString, strlen(childString));
        }
    } 
    else {
        printf("Parent process : %i\n", getpid());
        char parrentString[18] = "Parrent Writing\n";
        for (int i = 0; i < 1000; i++) {
            write(fd, parrentString, strlen(parrentString));
        }
    }

    close(fd);

    return 0;
}