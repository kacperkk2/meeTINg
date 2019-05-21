#include <iostream>
#include <unistd.h>
#include "ConsoleManager.h"

using namespace std;

void ConsoleManager::runConsole(int readfd, int writefd) {
    char message=0;
    char response=0;

    while(message != 'q')
    {
        int choice;
        do
        {
            cout << "---- KONSOLA ADMINA ----"<<endl;
            cout << "1. Zamknij wszystkie polaczenia (wysyla komunikat x)"<<endl;
            cout << "2. Zamknij polaczenia i serwer (wysyla komunikat q)"<<endl;

            cout <<endl<< "Wybierz opcje: ";
            cin >> choice;
        } while(choice < 1 || choice > 2);

        switch(choice)
        {
            case 1:
                message = 'x';
                break;
            case 2:
                message = 'q';
                break;
            default:
                message = 'd';
                break;
        }

        if(write(writefd, &message, sizeof(message)) == -1)
        {
            perror("write");
            exit(EXIT_FAILURE);
        }

        response='S';
        if(read(readfd, &response, sizeof(response)) == -1){
            perror("read");
            exit(EXIT_FAILURE);
        }
    }
}
