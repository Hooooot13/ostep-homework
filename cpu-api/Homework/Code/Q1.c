/*
- Write a program that calls fork(). 
- Before calling fork(), have the main process access a variable (e.g., x) 
    and set its value to something (e.g., 100). 
    
Q: What value is the variable in the child process?
A: I belive the variable should be set to the provided value 
    (i.e. the parrent and child process will report the same value)
Q: What happens to the variable when both the child and parent change the value of x?
A: Since the child process is has a separate copy of the state of the parent process
    the child and parent process will increnemt separate variables.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if ( argc < 2 ) {
        fprintf(stderr, "Not enough arguments");
        return 0;
    }

    int x = atoi(argv[1]);
    int forkReturn = fork();

    if (forkReturn < 0){
        fprintf(stderr, "fork faild");
    } 
    else if (forkReturn == 0) {
        printf("Child process : %i\n", getpid());
        printf("\tThe value X is : %i\n", x);
        printf("\tAfter incrementing the value of x is: %i\n", ++x);
    } 
    else {
        printf("Parent process : %i\n", getpid());
        printf("\tThe value X is : %i\n", x);
        printf("\tAfter incrementing the value of x is: %i\n", ++x);
    }

    return 0;
}