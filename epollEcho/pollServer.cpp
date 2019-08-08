//
// Created by 方伟 on 2019-07-28.
//

#include "pollServer.h"

#define IPADDRESS "127.0.0.1"
#define PORT 8787
#define OPEN_MAX 1000
#define INFTIM      -1
#define MAXLINE 1024

pollServer::pollServer() {
    int listenfd = socketBind(IPADDRESS, PORT);
    listen(listenfd, 5);
    dopoll(listenfd);
}

pollServer::~pollServer() {

}

int pollServer::socketBind(const char *ip, int port) {
    int listenfd;
    struct sockaddr_in servaddr;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == -1){
        perror("socket error");
        exit(1);
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &servaddr.sin_addr);
    servaddr.sin_port = htons(port);
    if((bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr))) == -1){
        perror("bind error");
        exit(1);
    }
    return listenfd;
}

void pollServer::dopoll(int listenfd) {
    int connfd, sockfd;
    struct sockaddr_in cliaddr;
    socklen_t cliaddrlen;
    struct pollfd clientfds[OPEN_MAX];
    int maxi = 0, nready = 0;
    clientfds[0].fd = listenfd;
    clientfds[0].events = POLLIN;
    for(int i=1;i<OPEN_MAX;++i)
        clientfds[i].fd = -1;
    for(;;){
        nready = poll(clientfds, maxi+1, INFTIM);
        if (nready == -1){
            perror("poll error:");
            exit(1);
        }
        if(clientfds[0].revents & POLLIN){
            cliaddrlen = sizeof(cliaddr);
            if((connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &cliaddrlen)) == -1){
                if (errno == EINTR)
                    continue;
                else{
                    perror("accept error:");
                    exit(1);
                }
            }

            fprintf(stdout, "accept a new client: %s:%d\n", inet_ntoa(cliaddr.sin_addr),cliaddr.sin_port);
            int i = 1;
            for(i=1;i<OPEN_MAX;++i) {
                if (clientfds[i].fd < 0) {
                    clientfds[i].fd = connfd;
                    break;
                }
            }
            if (i == OPEN_MAX){
                fprintf(stderr,"too many clients.\n");
                exit(1);
            }
            clientfds[i].events = POLLIN;
            maxi = std::max(maxi, i);
            if(--nready <= 0)
                continue;
        }

        handleConnection(clientfds, maxi, nready);
    }
}

void pollServer::handleConnection(struct pollfd *connfds, int num, int nready) {
    int i, n;
    char buf[MAXLINE];
    memset(buf, 0, sizeof(buf));
    for(i=1;i<=num;++i){
        if(connfds[i].revents & POLLIN){
            n = read(connfds[i].fd, buf, MAXLINE);
            if(n == 0){
                close(connfds[i].fd);
                connfds[i].fd = -1;
                char buf2[MAXLINE] = {"client closed"};
                write(STDOUT_FILENO, buf2, strlen(buf2));
                continue;
            }
            write(STDOUT_FILENO, buf, n);
            write(connfds[i].fd, buf, n);
            if(--nready <= 0)
                break;
        }
    }
}















