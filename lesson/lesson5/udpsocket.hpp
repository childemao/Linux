#pragma once
#include<iostream>
#include<cstdio>
#include<string>
#include<unistd.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
class UdpSocket
{
public:
    UdpSocket():_sockfd(-1) {

    }
    bool Socket() {
        _sockfd =  socket(AF_INET, SOCK_DGRAM,IPPROTO_UDP);
        if(_sockfd < 0) {
            perror("socket error");
            return false;
        }
        return true;
    }

    bool Bind(const std::string &ip, uint32_t port) {
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = inet_addr(ip.c_str());

        socklen_t len = sizeof(struct sockaddr_in);
        int ret = bind(_sockfd, (struct sockaddr*)&addr, len);
        if(ret < 0) {
            perror("bind error");
            return false;
        }
        return true;
    }
    bool Send(const std::string &data, const std::string &ip, uint16_t port) {
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = inet_addr(ip.c_str());

        int ret;
        socklen_t len = sizeof(struct sockaddr_in);
        ret = sendto(_sockfd, data.c_str(), data.size(), 0, (struct sockaddr*)&addr, len);
        if(ret < 0) {
            perror("sendto error");
            return false;
        }
        return true;
    }
    bool Recv(std::string *buf, std::string *ip = NULL, uint16_t *port = NULL) {

        struct sockaddr_in addr;
        socklen_t len = sizeof(struct sockaddr_in);
        int ret;
        char tmp[4096] = {0};
        ret = recvfrom(_sockfd, tmp, 4096, 0, (struct sockaddr*)&addr, &len);
        if(ret < 0) {
            perror("recvfrom error");
            return -1;
        }
        buf->assign(tmp, ret);
        if(ip != NULL){
            *ip = inet_ntoa(addr.sin_addr);
        }
        if(port != NULL) {
            *port = ntohs(addr.sin_port);
        }
        return true;
    }
    void Close() {
        close(_sockfd);
        _sockfd = -1;
        return ;
    }

private:
    int _sockfd;

};

