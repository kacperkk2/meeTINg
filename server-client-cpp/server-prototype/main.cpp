#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include "ConnectionManager.h"
#include "ConsoleManager.h"
#include "PackageSizeParser.h"

#define PORT 9543
#define BACKLOG 10

using namespace std;

void *handle_client(void* fd)
{
    ConnectionManager connectionManager;
    connectionManager.manage_connections(PORT, BACKLOG, fd);
    return 0;
}


int main()
{
    int pipefd[2];

    // uzyskanie 2 deskryptorow pipe, [1] do pisania, [0] do czytania
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // utworz nowy watek i przekaz mu deskryptor do pipe do read
    pthread_t thread_id;

    if(pthread_create(&thread_id, NULL, handle_client, (void *) (intptr_t) &pipefd) < 0)
    {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    int writefd = pipefd[1];

    ConsoleManager::runConsole(writefd);

    close(writefd);
    pthread_join(thread_id, NULL);

    return 0;
}
