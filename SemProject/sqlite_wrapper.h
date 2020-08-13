#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>
#include <sqlite3.h>

sqlite3* open_db(std::string dir);
bool does_entity_exist(sqlite3* db,const std::string& sql_cmd);
int does_entity_exist_callback(void* bool_data_passed, int argc, char** argv, char** azColName);