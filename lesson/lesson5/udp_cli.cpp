#include <iostream>
#include<stdlib.h>
#include "udpsocket.hpp"

#define CHECK_RET(q) if((q)==false){return -1;}

int main(int argc, char *argv[]) {
    if(argc != 3) {
        printf("em: ./udp_cli 192.168.122.132 9000\n");
        return -1;
    }
    std::string ip_addr = argv[1];
    uint16_t port_addr = atoi(argv[2]);
    UdpSocket sock;
    CHECK_RET(sock.Socket());

    while(1) {
        std::cout << "client say:";
        fflush(stdout);
        std::string buf;
        std::cin >> buf;
        sock.Send(buf, ip_addr, port_addr);

        buf.clear();
        sock.Recv(&buf);
        std::cout << "server say:" << buf << std::endl;
    }
    sock.Close();

    return 0;
}
