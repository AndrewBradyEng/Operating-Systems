/*
Andrew Brady
C20769825

Assignment 3 - COMP3602
*/
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// THREAD function to ping a host
void *perform_ping(void *arguments) {
    pid_t r;
    char *ip = (char *)arguments;
    printf("IN THREAD: Pinging host IP:%s started\n", ip);
    int i;
    for (i = 0; i < 5; i++) {
        pid_t child_pid = fork(); // Create a child process
        if (child_pid == 0) {
            // In the child process, execute the ping command
            execlp("ping", "ping", "-c", "1", ip, NULL);
            perror("execlp"); // Print an error message if execlp fails
            exit(1);
        } else if (child_pid < 0) {
            perror("fork"); // Print an error message if fork fails
        } else {
            int status;
            waitpid(child_pid, &status, 0); // Wait for the child process to complete
        }
    }

    printf("IN THREAD: Pinging host IP: %s ended\n", ip);

    pthread_exit(NULL);
}

// MAIN function to create threads
int main(int argc, char** argv) {
    // Printing command-line arguments (i.e. IP addresses)
    int k;
    printf("IN MAIN: The IP addresses are:\n");
    for (k = 1; k < argc; k++) {
        printf("%s\n", argv[k]);
    }

    // Create threads to ping each host
    pthread_t threads[argc - 1];
    int i;
    for (i = 1; i < argc; i++) {
            printf("IN MAIN: Creating thread %d to ping IP address: %s\n", i, argv[i]);
            int r = pthread_create(&threads[i - 1], NULL, perform_ping, argv[i]);
            if (r == 0) {
                printf("IN MAIN: Thread %d created succesfully.\n", i);
            } else {
                fprintf(stderr, "Error creating thread %d.\n", i);
            }
    }
    // Wait for each thread to complete
    int j;
    for (j = 0; j < argc - 1; j++) { 
	    pthread_join(threads[j], NULL);
            printf("IN MAIN: Thread %d has ended.\n", j);
    }
    printf("IN MAIN: Program has ended.\n");
    return 0;
}