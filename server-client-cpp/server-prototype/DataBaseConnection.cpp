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

        res = stmt->executeQuery("select count(*) from USER where username = \"" + userName + "\" and hashed_password = \"" + password + "\"" );
        while (res->next()) {

            if (res->getInt("count(*)") == 1) return 1;

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
        string userData = ",";
        string rola;

        stmt = con->createStatement();
        res = stmt->executeQuery("select * from USER where username = \'" + userName + "\'");
        while (res->next()) {

            userData += "\"id\":\"" + res->getString("user_id") + "\",";
            userData += "\"username\":\"" + res->getString("username") + "\",";
            userData += "\"password\":\"" + res->getString("hashed_password") + "\",";
            if (res->getString("system_role") == "0") {
                rola = "USER";
            } else rola = "TEAM_LEADER";
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
    int indeks = freeID("USER", "user_id");
    try {
        sql::ResultSet *res;

        stmt = con->createStatement();
        res = stmt->executeQuery("select count(*) from USER where username = \'" + userName + "\'");

        while (res->next()) {

            count = res->getInt(1);
        }

        if (count == 0) {

            stmt->executeUpdate(
                    "INSERT INTO USER VALUES(\"" + to_string(indeks) + "\",\"" + userName + "\",\"" + password +
                    "\",\"0\")");

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

string DataBaseConnection::userGroupsList(int userId) {

    int iterator = 0;
    string userGroups = "\"items\": [";

    try {
        sql::ResultSet *res;

        stmt = con->createStatement();

        res = stmt->executeQuery(
                "select g.group_id, g.name, (select USER.username from USER where user_id = g.leader_id) as leader_name from GROUP_USER gu join GROUPS g on gu.group_id = g.group_id  join USER u on u.user_id = gu.user_id where gu.status = 1 and u.user_id = " +
                to_string(userId));
        while (res->next()) {
            iterator++;
            userGroups += "{\"id\":\"" + res->getString("group_id") + "\",";

            userGroups += "\"name\":\"" + res->getString("name") + "\",";
            userGroups += "\"leader\":\"" + res->getString("leader_name") + "\"},";

        }
        if(iterator != 0) userGroups.pop_back();
        userGroups += "]}";


        stmt->close();
        res->close();
        delete res;
        delete stmt;

        return userGroups;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }

}

string DataBaseConnection::allGroups(int userId) {

    string userGroups = "\"items\": [";

    try {
        sql::ResultSet *res;

        stmt = con->createStatement();

        res = stmt->executeQuery(
                "select g.group_id, g.name, (select USER.username from USER where user_id = g.leader_id) as leader_name from GROUPS g where (select count(*) from GROUP_USER where GROUP_USER.group_id = g.group_id and GROUP_USER.user_id = " + to_string(userId) + " and GROUP_USER.status = 1) = 0 and (select count(*) from GROUP_USER where GROUP_USER.group_id = g.group_id and GROUP_USER.user_id = \"" + to_string(userId) + "\" and GROUP_USER.status = 0) = 0");
        while (res->next()) {

            userGroups += "{\"id\":\"" + res->getString("group_id") + "\",";
            userGroups += "\"name\":\"" + res->getString("name") + "\",";
            userGroups += "\"leader\":\"" + res->getString("leader_name") + "\"},";

        }
        userGroups.pop_back();
        userGroups += "]}";

        stmt->close();
        res->close();
        delete res;
        delete stmt;

        return userGroups;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }

}

string DataBaseConnection::makeGroup(int userId, string groupName) {

    string userName;
    int indeks = freeID("GROUPS", "group_id");
    try {


        sql::ResultSet *res;

        stmt = con->createStatement();
        stmt->executeUpdate(
                "INSERT INTO GROUPS VALUES(\"" + to_string(indeks) + "\",\"" + to_string(userId) + "\",\"" + groupName + "\")");

        res = stmt->executeQuery(
                "select username from USER where user_id = " + to_string(userId));
        while (res->next()) {

            userName =  res->getString("username");
        }

        stmt->close();
        res->close();
        delete res;
        delete stmt;
        string response = " \"id\": \"" + to_string(indeks) + "\",\n  \"name\": \"" + groupName + "\",\n  \"leader\": \"" + userName + "\"\n}\n";
        return response;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }


}

int DataBaseConnection::freeID(string tableName, string idName) {

    int id;

    try {

        sql::ResultSet *res1;

        stmt = con->createStatement();

        res1 = stmt->executeQuery(
                "SELECT min(g." + idName + ") + 1 as 'id' \n" "from " + tableName + " g\n" "left outer join " +
                tableName + " b\n" "on b." +
                idName + "= g." + idName + " +1\n" "where b." + idName + " is null");
        while (res1->next()) {
            id = stoi(res1->getString("id"));

        }

        stmt->close();
        res1->close();
        delete res1;
        delete stmt;

        return id;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

bool DataBaseConnection::applyGroup(int userId, int groupId) {
    try {
        stmt = con->createStatement();
        cout << "INSERT INTO GROUP_USER VALUES(" + to_string(groupId) + "," + to_string(userId) + ", 0)" << endl;
        stmt->executeUpdate(
                "INSERT INTO GROUP_USER VALUES(\"" + to_string(groupId) + "\",\"" + to_string(userId) + "\", 0)");


    stmt->close();
    delete stmt;
    return 1;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;

    }
    return 0;
}

