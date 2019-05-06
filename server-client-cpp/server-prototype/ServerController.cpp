//
// Created by michal on 06.05.19.
//

#include "ServerController.h"
#include "nlohmann/json.hpp"
#include <iomanip>
#include <iostream>
#include <fstream>


using namespace std;
using namespace nlohmann;
ServerController::ServerController(){
    cout<<"hehe";

}

void ServerController::test(){
   json j = "{\n \"happy\": \"true\",\n \"pi\": \"3.141\" }"_json;
   cout << j;


}