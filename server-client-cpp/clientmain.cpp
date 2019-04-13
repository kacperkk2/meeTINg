#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

using namespace std;

#define BUFLEN 20
#define PORT 9543

int main()
{
    string ipAddress = "127.0.0.1";

    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("socket");
        exit(1);
    }

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    inet_pton(AF_INET, ipAddress.c_str(), &server.sin_addr);


    if (connect(sockfd, (sockaddr*)&server, sizeof(server)) == -1)
    {
        printf("connect");
        exit(1);
    }

    char buf[BUFLEN];
    string message;

    while(true)
    {
        cout << "Podaj wiadomosc: ";
        getline(cin, message);

        string messageToSend = "";

        for (int i = 0; i < BUFLEN; i++) {
            messageToSend += "a";
        }

        cout << messageToSend.size() << endl;

        if(send(sockfd, messageToSend.c_str(), messageToSend.size(), 0) == -1)
        {
            printf("send");
            exit(1);
        }

        memset(buf, 0, BUFLEN);

        int bytes;
        if((bytes = recv(sockfd, buf, BUFLEN, 0)) == -1)
        {
            printf("recv");
            exit(1);
        }

        cout << "-- Odpowiedz: -" << ", bytes: "<< bytes << endl;
    }

    close(sockfd);


    return 0;
}







