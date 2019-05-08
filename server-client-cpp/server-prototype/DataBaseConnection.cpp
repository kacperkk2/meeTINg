//
// Created by michal on 06.05.19.
//

#include "DataBaseConnection.h"
#include <stdlib.h>
#include <iostream>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <string>


using namespace sql;

DataBaseConnection::DataBaseConnection(string userName, string password) {

    try {

        /* Create a connection */
        driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "root", "admin");
        /* Connect to the MySQL test database */
        con->setSchema("meeting");
//
//        if (correctLogon(userName, password) == 1) {
//            //cout << "ZALOGOWANO" << userName << endl;
//        } else {
//            cout << "NIEZALOGOWANO" << endl;
//            con->close();
//            delete con;
//        }


    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }

}


bool DataBaseConnection::correctLogon(string userName, string password) {

    try {
        sql::ResultSet *res;

        stmt = con->createStatement();

        res = stmt->executeQuery("select * from USER");
        while (res->next()) {

            if (res->getString("username").c_str() == userName) {
                if (res->getString("hashed_password").c_str() == password) return 1;

            }

        }
        stmt->close();
        res->close();
        delete res;
        delete stmt;


    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
    return 0;
}


void DataBaseConnection::usersList() {

    try {
        sql::ResultSet *res;

        stmt = con->createStatement();

        res = stmt->executeQuery("select * from USER");
        while (res->next()) {

            cout << res->getString("username").c_str() << endl;

        }
        stmt->close();
        res->close();
        delete res;
        delete stmt;

    } catch (sql::SQLException &e) {
        cout << "nie jestes zalogowany" << endl;
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }

}

string DataBaseConnection::userLoginData(string userName) {

    try {
        sql::ResultSet *res;
        string userData = "{";
        string rola;

        stmt = con->createStatement();
        cout << "select * from USER where username = \'" + userName + "\';"<< endl;
        res = stmt->executeQuery("select * from USER where username = \'" + userName + "\'");
        while (res->next()) {

            userData += "\"id\":\"" + res->getString("user_id") + "\",";
            userData += "\"username\":\"" + res->getString("username") + "\",";
            userData += "\"password\":\"" + res->getString("hashed_password") + "\",";
            if(res->getString("system_role") == "0") {
                rola = "USER";
            }else rola = "TEAM_LEADER";
            userData += "\"systemRole\":\"" + rola + "\"}";

        }
        stmt->close();
        res->close();
        delete res;
        delete stmt;
        cout << userData << endl;
        return userData;

    } catch (sql::SQLException &e) {
        cout << "nie jestes zalogowany" << endl;
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }


}

//ResultSet *DataBaseConnection::groupsList() {
//
//    try {
//        ResultSet *res;
//
//        stmt = con->createStatement();
//
//        res = stmt->executeQuery("select * from GROUPS");
//
//        stmt->close();
//        //res->close();
//        //delete res;
//        delete stmt;
//        return res;
//
//    } catch (sql::SQLException &e) {
//        cout << "nie jestes zalogowany" << endl;
//        cout << "# ERR: SQLException in " << __FILE__;
//        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
//        cout << "# ERR: " << e.what();
//        cout << " (MySQL error code: " << e.getErrorCode();
//        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
//    }
//
//
//
//}

void DataBaseConnection::closeConnection() {
    cout << "Close connection" << endl;
    con->close();

    delete con;
}
