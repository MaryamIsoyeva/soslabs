#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>
#define SOCK_PATH "/Users/elena/soslabs/echo_socket"

int main(void)
{
    int s, t, len;
    struct sockaddr_un remote;
    char str[100];
    
    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }
    
    printf("Trying to connect...\n");
    
    remote.sun_family = AF_UNIX;
    strcpy(remote.sun_path, SOCK_PATH);
    len = strlen(remote.sun_path) + sizeof(remote.sun_family);
    if (connect(s, (struct sockaddr *)&remote, len) == -1) {
        perror("connect");
        exit(1);
    }
    
    printf("Connected.\n");
    clock_t begin = clock();
//    while(printf("> "), fgets(str, 100, stdin), !feof(stdin)) {
//        if (send(s, str, strlen(str), 0) == -1) {
//            perror("send");
//            exit(1);
//        }
        
        if ((t=recv(s, str, 100, 0)) > 0) {
            str[t] = '\0';
            printf("%s", str);
            clock_t end = clock();
            double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
            printf("\nTime spent is %f seconds\n", time_spent);

        } else {
            if (t < 0) perror("recv");
            else printf("Server closed connection\n");
            exit(1);
        }
//    }
    
    close(s);
    
    return 0;
}
