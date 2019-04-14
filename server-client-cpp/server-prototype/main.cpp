//
// Created by Tomasz Suchodolski, Kacper Klimczuk on 14.04.19.
//

#include <unistd.h>
#include <fstream>
#include "ClientManager.h"
#include "ConsoleManager.h"

using namespace std;


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

    if(pthread_create(&thread_id, NULL, ClientManager::handle_client, (void *) (intptr_t) &pipefd) < 0)
    {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    int writefd = pipefd[1];

    ConsoleManager::runConsole(writefd);

    close(writefd);

    return 0;
}
