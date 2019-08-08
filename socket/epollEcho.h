//
// Created by 方伟 on 2019-08-08.
//

#ifndef SOCKET_EPOLLECHO_H
#define SOCKET_EPOLLECHO_H


#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <epoll.h>
#include <poll.h>
#include <iostream>
#include <vector>

class EpollEcho {
public:
    typedef struct sockaddr_in SA;
    EpollEcho();
    ~EpollEcho(){}

private:
    int socketBind(const char* ip, int port);
    void doEpoll(int listenfd);
    void handleConnection(struct pollfd *connfds, int num, int nready);
    int listenFdCreate();
    SA initSockAddrIn(const char *ip, int port);
    int createEpollFd();



    typedef std::vector<struct epoll_event> EventList;
    //int epollfd;
};


#endif //SOCKET_EPOLLECHO_H
