//
// Created by 方伟 on 2019-07-21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/select.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <poll.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define IPADDRESS   "127.0.0.1"
#define PORT        8787
#define MAXLINE     1024
#define LISTENQ     5
#define OPEN_MAX    1000
#define INFTIM      -1

//函数声明
//创建套接字并进行绑定
static int socket_bind(const char* ip,int port);
//IO多路复用select
static void do_select(int listenfd);
//处理多个连接
static void handle_connection(int* connfds, fd_set &allset, fd_set &rset, int num);

//int main(int argc,char *argv[])
//{
//    int listenfd,connfd,sockfd;
//    struct sockaddr_in cliaddr;
//    socklen_t cliaddrlen;
//    listenfd = socket_bind(IPADDRESS,PORT);
//    listen(listenfd,LISTENQ);
//    do_select(listenfd);
//    return 0;
//}

static int socket_bind(const char* ip,int port)
{
    int  listenfd;
    struct sockaddr_in servaddr;
    listenfd = socket(AF_INET,SOCK_STREAM,0);
    if (listenfd == -1){
        perror("socket error:");
        exit(1);
    }
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET,ip,&servaddr.sin_addr);
    servaddr.sin_port = htons(port);
    if (bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) == -1){
        perror("bind error: ");
        exit(1);
    }
    return listenfd;
}

static void do_select(int listenfd)
{
    int  connfd,sockfd;
    struct sockaddr_in cliaddr;
    socklen_t cliaddrlen;
    int maxfd, maxi, i, nready, client[FD_SETSIZE];
    fd_set rset, allset;
    //添加监听描述符
    //初始化客户连接描述符
    maxfd = listenfd;
    maxi = -1;
    for(int i=0;i<FD_SETSIZE;++i)
        client[i] = -1;
    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);
    //循环处理
    for ( ; ; )
    {
        rset = allset;
        //获取可用描述符的个数
        nready = select(maxfd+1, &rset, NULL, NULL, NULL);
        if (nready == -1){
            perror("select error:");
            exit(1);
        }
        //测试监听描述符是否准备好
        if (FD_ISSET(listenfd, &rset)){
            cliaddrlen = sizeof(cliaddr);
            //接受新的连接
            if ((connfd = accept(listenfd,(struct sockaddr*)&cliaddr,&cliaddrlen)) == -1){
                if (errno == EINTR)
                    continue;
                else{
                    perror("accept error:");
                    exit(1);
                }
            }
            fprintf(stdout,"accept a new client: %s:%d\n", inet_ntoa(cliaddr.sin_addr),cliaddr.sin_port);
            FD_SET(connfd, &allset);
            if(connfd > maxfd)
                maxfd = connfd;
            //将新的连接描述符添加到数组中
            //这个是找到最小的一个没有用的文件描述符
            for (i = 1;i < FD_SETSIZE;i++){
                if (client[i] < 0){
                    client[i] = connfd;
                    break;
                }
            }
            if (i == FD_SETSIZE){
                fprintf(stderr,"too many clients.\n");
                exit(1);
            }
            //记录客户连接套接字的个数
            maxi = (i > maxi ? i : maxi);
            if (--nready <= 0)
                continue;
        }
        //处理客户连接
        handle_connection(client, allset, rset, maxi);
    }
}

static void handle_connection(int* connfds,fd_set &allset ,fd_set &rset, int num) {
    int i, n;
    char buf[MAXLINE];
    memset(buf, 0, MAXLINE);
    for (i = 1; i <= num; i++) {
        if (connfds[i] < 0)
            continue;
        //测试客户描述符是否准备好
        if (FD_ISSET(connfds[i], &rset)) {
            //接收客户端发送的信息
            n = read(connfds[i], buf, MAXLINE);
            /*n == 0 就是说明子机与母机断开连接了，子机在那边不输入，直接敲回车，这边也是可以收到回车符的*/
            if (n == 0) {
                close(connfds[i]);
                FD_CLR(connfds[i], &allset);
                char buf2[20] = {"client closed"};
                write(STDOUT_FILENO, buf2, strlen(buf2));
                continue;
            }
            // printf("read msg is: ");
            write(STDOUT_FILENO, buf, n);
            //向客户端发送buf
            write(connfds[i], buf, n);
        }
    }
}