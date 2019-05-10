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

        return userData;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }


}

bool DataBaseConnection::correctRegistration(string userName, string password) {
    int count;
    try {
        sql::ResultSet *res;

        stmt = con->createStatement();
        res = stmt->executeQuery("select count(*) from USER where username = \'" + userName+ "\'");

        while (res->next()) {

            count = res->getInt(1);
        }

        if(count == 0){

            sql::ResultSet *res1;
            int indeks;
            res1 = stmt->executeQuery("select max(user_id) from USER");

            while (res1->next()) {
                indeks = res1->getInt(1) + 1;

            }
            cout<<"INSERT INTO USER VALUES(\"" + to_string(indeks) + "\",\"" + userName + "\",\"" + password + "\",\"0\")"<<endl;
            stmt->executeUpdate("INSERT INTO USER VALUES(\"" + to_string(indeks) + "\",\"" + userName + "\",\"" + password + "\",\"0\")");

            return 1;
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




void DataBaseConnection::closeConnection() {
    cout << "Close connection" << endl;
    con->close();

    delete con;
}
