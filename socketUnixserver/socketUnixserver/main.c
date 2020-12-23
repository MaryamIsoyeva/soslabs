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
#define SOCK_PATH "/Users/elena/soslabs/echo_socket"

int main(void)
{
    int s, s2, t, len;
    struct sockaddr_un local, remote;
    char str[100] = "Hello from the unix server";
    
    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }
    
    local.sun_family = AF_UNIX;
    strcpy(local.sun_path, SOCK_PATH);
    unlink(local.sun_path);
    len = strlen(local.sun_path) + sizeof(local.sun_family);
    unlink("/Users/elena/soslabs/echo_socke");
    if (bind(s, (struct sockaddr *)&local, len) == -1) {
        perror("bind");
        exit(1);
    }
    
    if (listen(s, 5) == -1) {
        perror("listen");
        exit(1);
    }
    
//    for(;;) {
        int done, n;
        printf("Waiting for a connection...\n");
        t = sizeof(remote);
        if ((s2 = accept(s, (struct sockaddr *)&remote, &t)) == -1) {
            perror("accept");
            exit(1);
        }
        
        printf("Connected.\n");
        
        done = 0;
//        do {
//            n = recv(s2, str, 100, 0);
//            if (n <= 0) {
//                if (n < 0) perror("recv");
//                done = 1;
//            }
//            
//            if (!done)
                    if (send(s2, str, 100/*n*/, 0) < 0) {
                    perror("send");
                    done = 1;
                }
//        } while (!done);
        
        close(s2);
//    }
    
    return 0;
}
/*#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/un.h>
#include <stdio.h>
#include <strings.h>
void error(const char *);
int main(int argc, char *argv[])
{
    int sockfd, newsockfd, servlen, n;
    socklen_t clilen;
    struct sockaddr_un  cli_addr, serv_addr;
    char buf[80];
    
    if ((sockfd = socket(AF_UNIX,SOCK_STREAM,0)) < 0)
        error("creating socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, argv[1]);
    servlen=strlen(serv_addr.sun_path) + sizeof(serv_addr.sun_family);
    if(bind(sockfd,(struct sockaddr *)&serv_addr,servlen)<0)
        error("binding socket");
    
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd,(struct sockaddr *)&cli_addr,&clilen);
    if (newsockfd < 0)
        error("accepting");
    n=read(newsockfd,buf,80);
    printf("A connection has been established\n");
    write(1,buf,n);
    write(newsockfd,"I got your message\n",19);
    close(newsockfd);
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

#define NAME "socket"


int main()
{
     int sock, msgsock, rval;
     struct sockaddr_un server;
     char buf[1024];
    
    
     sock = socket(AF_UNIX, SOCK_STREAM, 0);
     if (sock < 0) {
         perror("opening stream socket");
         exit(1);
     }
     server.sun_family = AF_UNIX;
     strcpy(server.sun_path, NAME);
     if (bind(sock, (struct sockaddr *) &server, sizeof(struct sockaddr_un))) {
         perror("binding stream socket");
         exit(1);
     }
     printf("Socket has name %s\n", server.sun_path);
     listen(sock, 5);
//     for (;;) {
         msgsock = accept(sock, 0, 0);
         if (msgsock == -1)
             perror("accept");
          else do {
             bzero(buf, sizeof(buf));
             if ((rval = read(msgsock, buf, 1024)) < 0)
                 perror("reading stream message");
             else if (rval == 0)
                 printf("Ending connection\n");
             else
                 printf("-->%s\n", buf);
         } while (rval > 0);
         close(msgsock);
//     }
     close(sock);
     unlink(NAME);
 }*/