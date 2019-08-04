//
// Created by 方伟 on 2019-07-28.
//

#ifndef POLLECHO_POLLSERVER_H
#define POLLECHO_POLLSERVER_H

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
#include <poll.h>
#include <algorithm>

class pollServer {
public:
    pollServer();
    ~pollServer();

private:
    int socketBind(const char* ip, int port);
    void dopoll(int listenfd);
    void handleConnection(struct pollfd *connfds, int num, int nready);
};


#endif //POLLECHO_POLLSERVER_H
