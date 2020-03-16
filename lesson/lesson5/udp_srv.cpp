#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include "udpsocket.hpp"
int main(int argc, char *argv[]){

    if(argc != 3) {
     printf("./udp_cli.srv ip port em:./udp_srv 192.168.122.132 9000\n");
     return -1;
    }
    const char *ip_addr = argv[1];
    uint16_t port_addr = atoi(argv[2]);

    int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sockfd < 0) {
        perror("socket error");
        return -1;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port_addr);
    addr.sin_addr.s_addr = inet_addr(ip_addr);
    socklen_t len = sizeof(struct sockaddr_in);
    int ret = bind(sockfd, (struct sockaddr*)&addr, len);

    if(ret < -1) {
        perror("bind error");
        return -1;
    }
    while(1){
        char buf[1024] = {0};
        struct sockaddr_in cliaddr;
        socklen_t len = sizeof(struct sockaddr_in);

        int ret = recvfrom(sockfd, buf, 1023, 0, (struct sockaddr*)&cliaddr, &len);
        if(ret < 0){
            perror("recefrom error");
            close(sockfd);
            return -1;
        }
      printf("client say: %s\n", buf);

      printf("server say: ");
      fflush(stdout);
      memset(buf, 0x00, 1024);
      scanf("%s" ,buf);

      ret = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&cliaddr, len);
      if(ret < 0) {
          perror("sendto error");
          close(sockfd);
          return -1;
      }
    }
    close(sockfd);
}
