#include<iostream>
#include<stdlib.h>
#include "tcpSocket.hpp"

int main(int argc, char *argv[])
{
    if(argc != 3) {
        printf("em: ./tcp_srv 172.17.0.1 9010\n");
        return -1;
    }
    std::string ip = argv[1];
    uint16_t port = atoi(argv[2]);

    TcpSocket lst_sock;
    CHECK_RET(lst_sock.Socket());
    CHECK_RET(lst_sock.Bind(ip, port));
    CHECK_RET(lst_sock.Listen());
    while(1) {
        TcpSocket cli_sock;
        std::string cli_ip;
        uint16_t cli_port;

        bool ret = lst_sock.Accept(&cli_sock, &cli_ip, &cli_port);
        if(ret == false) {
            continue;
        }
        std::string buf;
        if(cli_sock.Recv(&buf) == false) {
            cli_sock.Close();
            continue;
        }
        printf("client:[%s:%d] say:%s\n", &cli_ip[0], cli_port, &buf[0]);
        std::cout << "server say;";
        fflush(stdout);
        buf.clear();
        std::cin >> buf;
        if(cli_sock.Send(buf) == false){
            cli_sock.Close();
            continue;
        }

    }
    lst_sock.Close();
    return 0;
}
