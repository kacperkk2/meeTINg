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
    ConnectionManager connectionManager;
    connectionManager.manage_connections(BACKLOG, args);
    return 0;
}


void DataBase() {
    std::cout << std::endl;
    std::cout << "Running 'SELECT 'Hello World!" << std::endl;

    try {
        sql::Driver *driver;
        sql::Connection *con;
        sql::Statement *stmt;
        sql::ResultSet *res;

        /* Create a connection */
        driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "root", "admin");
        /* Connect to the MySQL test database */
        con->setSchema("meeting");

        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT 'Hello World!' AS _message"); // replace with your statement
        while (res->next()) {
            /*cout << "\t... MySQL replies: ";
            // Access column data by alias or column name //
                cout << res->getString("_message") << endl;
                cout << "\t... MySQL says it again: ";
                // Access column fata by numeric offset, 1 is the first column //
                cout << res->getString(1) << endl;*/
        }
        delete res;
        delete stmt;
        delete con;

    } catch (sql::SQLException &e) {

        /* cout << "# ERR: " << e.what();
         cout << " (MySQL error code: " << e.getErrorCode();
         cout << ", SQLState: " << e.getSQLState() << " )" << endl;*/
    }
}

int main(int argc, char* argv[])
{
    DataBase();

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

    ConsoleManager::runConsole(writefd);

    close(writefd);
    pthread_join(thread_id, NULL);

    return 0;
}
