#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

int main() {

    int sock_raw;
    unsigned char buffer[65536];

    sock_raw = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);

    if(sock_raw < 0) {
        perror("Socket Error");
        return 1;
    }

    cout << "Advanced Packet Sniffer Started...\n";

    while(true) {

        ssize_t data_size =
        recvfrom(sock_raw, buffer, 65536, 0, NULL, NULL);

        if(data_size < 0) {
            perror("Recvfrom error");
            return 1;
        }

        struct iphdr *ip = (struct iphdr*)buffer;

        struct sockaddr_in source, dest;

        source.sin_addr.s_addr = ip->saddr;
        dest.sin_addr.s_addr = ip->daddr;

        cout << "\nPacket Captured\n";

        cout << "Source IP: "
             << inet_ntoa(source.sin_addr) << endl;

        cout << "Destination IP: "
             << inet_ntoa(dest.sin_addr) << endl;

        if(ip->protocol == 6) {

            struct tcphdr *tcp =
            (struct tcphdr*)(buffer + ip->ihl*4);

            cout << "Protocol: TCP\n";

            cout << "Source Port: "
                 << ntohs(tcp->source) << endl;

            cout << "Destination Port: "
                 << ntohs(tcp->dest) << endl;

            if(ntohs(tcp->dest) == 80)
                cout << "HTTP Traffic Detected\n";

            if(ntohs(tcp->dest) == 443)
                cout << "HTTPS Traffic Detected\n";
        }

        cout << "-----------------------------\n";
    }

    close(sock_raw);
    return 0;
}