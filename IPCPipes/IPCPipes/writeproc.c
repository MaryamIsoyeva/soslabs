#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <unistd.h>
#define NAMEDPIPE_NAME "named_pipe"
#define BUFSIZE        50

int main (int argc, char ** argv) {
    int fd, len;
    char buf[BUFSIZE];
    
//    if ( mkfifo(NAMEDPIPE_NAME, 0777) ) {
//        perror("mkfifo");
//        return 1;
//    }
    //    printf("%s is created\n", NAMEDPIPE_NAME);
    
    if ( (fd = open(NAMEDPIPE_NAME, O_WRONLY)) <= 0 ) {
        perror("open");
        return 1;
    }
    printf("%s is opened\n", NAMEDPIPE_NAME);
    
    //    do {
    memset(buf, '\0', BUFSIZE);
    strcpy(buf, "Hello from writer to pipe");
    clock_t begin = clock();
    if ( (len = write(fd, buf, BUFSIZE-1)) <= 0 ) {
        perror("write");
        close(fd);
        remove(NAMEDPIPE_NAME);
        return 0;
    }
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nTime spent for writing is %f seconds\n", time_spent);
//    printf("Received: %s\n", buf);
    //    } while ( 1 );
}