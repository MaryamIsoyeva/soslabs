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
/*#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <strings.h>
void error(const char *);

int main(int argc, char *argv[])
{
    int sockfd, servlen,n;
    struct sockaddr_un  serv_addr;
    char buffer[82];
    
    bzero((char *)&serv_addr,sizeof(serv_addr));
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, argv[1]);
    servlen = strlen(serv_addr.sun_path) + sizeof(serv_addr.sun_family);
    if ((sockfd = socket(AF_UNIX, SOCK_STREAM,0)) < 0)
        error("Creating socket");
    if (connect(sockfd, (struct sockaddr *)
                &serv_addr, servlen) < 0)
        error("Connecting");
    printf("Please enter your message: ");
    bzero(buffer,82);
    fgets(buffer,80,stdin);
    write(sockfd,buffer,strlen(buffer));
    n=read(sockfd,buffer,80);
    printf("The return message was\n");
    write(1,buffer,n);
    close(sockfd);
    return 0;
}

void error(const char *msg)
{
    perror(msg);
    exit(0);
}*/
/*#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <time.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>

#define DATA "Hello from client"


int main(int argc, char *argv[]){
     int sock;
     struct sockaddr_un server;
//     char buf[1024];
    
    
     if (argc < 2) {
         printf("usage:%s <pathname>", argv[0]);
         exit(1);
     }
    
     sock = socket(AF_UNIX, SOCK_STREAM, 0);
     if (sock < 0) {
         perror("opening stream socket");
         exit(1);
     }
     server.sun_family = AF_UNIX;
     strcpy(server.sun_path, argv[1]);
    
    
     if (connect(sock, (struct sockaddr *) &server, sizeof(struct sockaddr_un)) < 0) {
         close(sock);
         perror("connecting stream socket");
         exit(1);
     }
     if (write(sock, "Hello from client", sizeof(DATA)) < 0)
         perror("writing on stream socket");
     close(sock);
}*/