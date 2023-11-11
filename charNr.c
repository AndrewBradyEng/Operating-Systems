/*
Andrew Brady
C20769825

Assignment 3 - COMP3602
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int charcount = 0;

void *count_characters(void *args) {
    char *filename = (char *)args;
    char ch;
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Failed to open file");
        pthread_exit(NULL);
    }

    while (read(fd, &ch, 1) == 1) {
       if (!isspace(ch)) {
	        charcount++;
	    }
    }
    close(fd);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Please provide two text filenames.\n");
        exit(1);
    }

    pthread_t tid1, tid2;

    pthread_create(&tid1, NULL, count_characters, (void *)argv[1]);
    pthread_create(&tid2, NULL, count_characters, (void *)argv[2]);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("Number of characters in both files: %d\n", charcount);
    return 0;
}

