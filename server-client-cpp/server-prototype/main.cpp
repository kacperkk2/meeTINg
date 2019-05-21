#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include "ConnectionManager.h"
#include "ConsoleManager.h"
#include "PackageSizeParser.h"


#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include "mysql_driver.h"
#include <stdlib.h>
#include <iostream>

#define BACKLOG 10

using namespace std;


void *handle_client(void* args)
{
    DataBaseConnection dbc("root", "marcin11");
    ConnectionManager connectionManager(dbc, args, BACKLOG);
    connectionManager.manage_connections();
    return 0;
}


int main(int argc, char* argv[])
{
//    DataBaseConnection dbc("root", "admin");
//    cout << dbc.applyGroup(5,6) << endl;
    int pipefd[2];
    int port = atoi(argv[1]);
    if (!port) {
        perror("Illegal argument (port)");
        return 0;
    }

    // uzyskanie 2 deskryptorow pipe, [1] do pisania, [0] do czytania
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // utworz nowy watek i przekaz mu deskryptor do pipe do read
    pthread_t thread_id;

    int thread_args[3] = {pipefd[0], pipefd[1], port};

    if(pthread_create(&thread_id, NULL, handle_client, (void *) (intptr_t) &thread_args) < 0)
    {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    int writefd = pipefd[1];
    int readfd = pipefd[0];

    ConsoleManager::runConsole(readfd, writefd);

    close(writefd);
    close(readfd);
    pthread_join(thread_id, NULL);

    return 0;
}
