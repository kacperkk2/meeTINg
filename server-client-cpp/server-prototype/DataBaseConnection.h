//
// Created by michal on 06.05.19.
//

#ifndef TESTDB_DATABASECONNECTION_H
#define TESTDB_DATABASECONNECTION_H

#include <string>
#include <mysql_connection.h>
#include "DataBaseConnection.h"

using namespace std;
using namespace sql;


class DataBaseConnection {

    int userId = 0;    //id zalogowanego uzytkownika
    sql::Connection *con;
    sql::Driver *driver;
    sql::Statement *stmt;
public:

    DataBaseConnection(string userName, string password);
    bool correctLogon(string userName, string password);
    void usersList();
    void closeConnection();
    string userLoginData(string userName);
    bool correctRegistration(string userName, string password);
    //ResultSet groupsList();

};


#endif //TESTDB_DATABASECONNECTION_H
