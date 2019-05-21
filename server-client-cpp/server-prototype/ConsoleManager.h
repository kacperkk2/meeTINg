#ifndef SERVER_PROTOTYPE_CONSOLEMANAGER_H
#define SERVER_PROTOTYPE_CONSOLEMANAGER_H


class ConsoleManager {

private:
    // Disallow creating an instance of this object
    ConsoleManager() = default;

public:
    static void runConsole(int readfd, int writefd);

};


#endif //SERVER_PROTOTYPE_CONSOLEMANAGER_H
