//
// Created by wefang on 2019-07-19.
//

//struct pollfd{
//    int fd;           //用于检测的文件描述符
//    short events;     //设置所用的文件类型
//    short revents;    //检测所用的文件类型
//};
/*  poll函数
 *  fds指向监控pollfd的首指针
 *  nfds是poll监听的最大文件描述符的个数,使用时传入最大文件描述符+1
 *  timeout设置超时模式
 *  返回值：0表示没有套接字发生变化  n(n>0)表示有n个套接字有变化  -1有错误
 */
//int poll(struct pollfd* fds, unsigned long nfds, int timeout);

//struct sockaddr {
//    unsigned short sa_family; /* 地址家族, AF_xxx */
//    char sa_data[14]; /*14字节协议地址*/
//};

//struct sockaddr_in {
//    short int sin_family; /* 通信类型 */
//    unsigned short int sin_port; /* 端口 */
//    struct in_addr sin_addr; /* Internet 地址 */
//    unsigned char sin_zero[8]; /* 与sockaddr结构的长度相同*/
//};
//int socket(int domain, int type, int protocol);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

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
//IO多路复用poll
static void do_poll(int listenfd);
//处理多个连接
static void handle_connection(struct pollfd *connfds, int num, int nready);

//int main(int argc,char *argv[])
//{
//    int listenfd,connfd,sockfd;
//    struct sockaddr_in cliaddr;
//    socklen_t cliaddrlen;
//    listenfd = socket_bind(IPADDRESS,PORT);
//    listen(listenfd,LISTENQ);
//    do_poll(listenfd);
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

static void do_poll(int listenfd)
{
    int  connfd,sockfd;
    struct sockaddr_in cliaddr;
    socklen_t cliaddrlen;
    struct pollfd clientfds[OPEN_MAX];
    int maxi;
    int i;
    int nready;
    //添加监听描述符
    clientfds[0].fd = listenfd;
    clientfds[0].events = POLLIN;
    //初始化客户连接描述符
    for (i = 1;i < OPEN_MAX;i++)
        clientfds[i].fd = -1;
    maxi = 0;
    //循环处理
    for ( ; ; ){
        //获取可用描述符的个数
        nready = poll(clientfds,maxi+1,INFTIM);
        if (nready == -1){
            perror("poll error:");
            exit(1);
        }
        //测试监听描述符是否准备好
        if (clientfds[0].revents & POLLIN){
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
            //将新的连接描述符添加到数组中
            //这个是找到最小的一个没有用的文件描述符
            for (i = 1;i < OPEN_MAX;i++){
                if (clientfds[i].fd < 0){
                    clientfds[i].fd = connfd;
                    break;
                }
            }
            if (i == OPEN_MAX){
                fprintf(stderr,"too many clients.\n");
                exit(1);
            }
            //将新的描述符添加到读描述符集合中
            clientfds[i].events = POLLIN;
            //记录客户连接套接字的个数
            maxi = (i > maxi ? i : maxi);
            if (--nready <= 0)
                continue;
        }
        //处理客户连接
        handle_connection(clientfds, maxi, nready);
    }
}

static void handle_connection(struct pollfd *connfds, int num, int nready)
{
    int i,n;
    char buf[MAXLINE];
    memset(buf,0,MAXLINE);
    for (i = 1;i <= num;i++){
        if (connfds[i].fd < 0)
            continue;
        //测试客户描述符是否准备好
        if (connfds[i].revents & POLLIN){
            //接收客户端发送的信息
            n = read(connfds[i].fd,buf,MAXLINE);
            /*n == 0 就是说明子机与母机断开连接了，子机在那边不输入，直接敲回车，这边也是可以收到回车符的*/
            if (n == 0){
                close(connfds[i].fd);
                connfds[i].fd = -1;
                char buf2[1024] = {"client closed"};
                write(STDOUT_FILENO, buf2, strlen(buf2));
                continue;
            }
            // printf("read msg is: ");
            write(STDOUT_FILENO,buf,n);
            //向客户端发送buf
            write(connfds[i].fd,buf,n);
            if(--nready <= 0)
                break;
        }
    }
}