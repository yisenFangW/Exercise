//
// Created by 方伟 on 2019-08-08.
//

#include "epollEcho.h"

#define IPADDRESS "127.0.0.1"
#define PORT 8787
#define MAX_EVENTS 10
#define INFTIM      -1
#define MAXLINE 1024



EpollEcho::EpollEcho() {
    int listenfd = socketBind(IPADDRESS, PORT);
    listen(listenfd, 5);
    doEpoll(listenfd);
}

int EpollEcho::socketBind(const char *ip, int port) {
    int listenfd = listenFdCreate();
    EpollEcho::SA servaddr = initSockAddrIn(ip, port);
    if((bind(listenfd, (struct sockaddr *)&servaddr, sizeof(EpollEcho::SA))) == -1){
        perror("bind error");
        exit(1);
    }
    std::cout<<"bind success"<<std::endl;
    return listenfd;
}

void EpollEcho::handleConnection(struct pollfd *connfds, int num, int nready) {
    return;
}

void EpollEcho::doEpoll(int listenfd) {
    int connfd = 0;
    EpollEcho::SA cliaddr;
    socklen_t cliaddrlen;
    struct epoll_event event;
    EventList events(16);
    event.data.fd = listenfd;
    event.events = EPOLLIN;
    if(epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &event) == -1){
        perror("epoll_ctl: listen_sock");
        //exit(1);   //这里要设置退出的define；
    }

    while(1) {
        size_t nready = epoll_wait(epollfd, events, MAX_EVENTS, -1);
        if(nready == -1){  //创建失败；
            perror("epoll_wait");
            //exit(1);   //这里要设置退出的define；
        }
        if(nready == 0)    //如果nfds为0，则直接返回；
            continue;

        if(nready == events.size())
            events.resize(events.size() * 2);

        for(int i = 0; i < nready; ++i) {
            if(event[i].data.fd == listenfd) {
                if ((connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &cliaddrlen)) == -1) {
                    if (errno == EINTR)
                        return;
                    else {
                        perror("accept error:");
                        exit(1);
                    }
                }
                setnonblocking(connfd);

                fprintf(stdout, "accept a new client: %s:%d\n", inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port);
            }
        }
    }
}

EpollEcho::SA EpollEcho::initSockAddrIn(const char *ip, int port) {
    EpollEcho::SA servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &servaddr.sin_addr);
    servaddr.sin_port = htons(port);
    return servaddr;
}

int EpollEcho::listenFdCreate(){
    int listenfd = socket(AF_INET, SOCK_STREAM , 0);
    if(listenfd == -1){
        perror("socket error");
        exit(1);
    }
    std::cout<<"listenfd create success"<<std::endl;
    return listenfd;
}

int createEpollFd(){
    int epollfd = epoll_create(EPOLL_CLOEXEC);
    return epollfd;
}