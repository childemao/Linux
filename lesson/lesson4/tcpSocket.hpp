#pragma once
#include <cstdio>
#include <string>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>


#define BACKLOG 10
#define CHECK_RET(q) if((q)==false){return -1;}
class TcpSocket
{
public:
    TcpSocket():_sockfd(-1){

    }
    //创建套接字
    bool Socket() {
        _sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if(_sockfd < 0) {
            perror("socket error");
            return false;
        }
        return true;
    }
    void Addr(struct sockaddr_in *addr, const std::string &ip, const uint16_t port) {
        addr->sin_family = AF_INET;
        addr->sin_port = htons(port);
        inet_pton(AF_INET, ip.c_str(), &(addr->sin_addr.s_addr));
    }
    bool Bind(const std::string &ip, const uint16_t port) {
        struct sockaddr_in addr;
        Addr(&addr, ip, port);
        socklen_t len = sizeof(struct sockaddr_in);
        int ret = bind(_sockfd, (struct sockaddr*)&addr, len);
        if(ret < 0)
        {
            perror("bind error");
            return false;
        }
        return true;
    }
    bool Listen(int backlog = BACKLOG){
        int ret = listen(_sockfd, backlog);
        if(ret < 0){
            perror("listen error");
            return false;
        }
        return true;
    }
    bool Connect(const std::string &ip, const uint16_t port) {
        struct sockaddr_in addr;
        Addr(&addr, ip,  port);
        socklen_t len = sizeof(struct sockaddr_in);
        int ret = connect(_sockfd, (struct sockaddr*)&addr, len);
        if(ret < 0) {
            perror("connet error");
            return false;
        }
        return true;
    }
    bool Accept(TcpSocket *sock, std::string *ip = NULL, uint16_t *port = NULL){
        struct sockaddr_in addr;
        socklen_t len = sizeof(struct sockaddr_in);
        int clisockfd = accept(_sockfd, (struct sockaddr*)&addr, &len);
        if(clisockfd < 0) {
            perror("accept error");
            return false;
        }
        sock->_sockfd = clisockfd;
        if(ip != NULL) {
            *ip = inet_ntoa(addr.sin_addr);
        }
        if(port != NULL) {
            *port = ntohs(addr.sin_port);
        }
        return true;
    }
    bool Send(const std::string &data) {
        int ret = send(_sockfd, data.c_str(), data.size(), 0);
        if(ret < 0) {
            perror("send error");
            return false;
        }
        return true;
    }
    bool Recv(std::string *buf) {
        char tmp[4096] = {0};
        int ret = recv(_sockfd, tmp, 4096, 0);
        if(ret < 0) {
            perror("recv error");
            return false;
        }else if(ret == 0){
            printf("connection break\n");
            return false;
        }
        buf->assign(tmp, ret);
        return true;
    }
    bool Close() {
        close(_sockfd);
        _sockfd = -1;
    }

private:
    int _sockfd;
};

