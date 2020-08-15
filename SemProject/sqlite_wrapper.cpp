#include "sqlite_wrapper.h"

sqlite3* open_db(std::string dir)
{
    sqlite3* db;
    int res_code = sqlite3_open(dir.c_str(), &db);

    if (res_code != SQLITE_OK) {
        std::cerr << "Error: " << sqlite3_errmsg(db);
    }
    return db;
}

bool does_entity_exist(sqlite3* db, const std::string& sql_cmd)
{
    bool does_entity_exist = false;
    char* err_msg;

    int err_code = sqlite3_exec(db, sql_cmd.c_str(), does_entity_exist_callback, &does_entity_exist, &err_msg);
    if (err_code != SQLITE_OK) {
        std::cerr << err_msg << std::endl;
    }
    return does_entity_exist;
}
int does_entity_exist_callback(void* bool_data_passed, int argc, char** argv, char** azColName) {
    bool* does_entity_exist = static_cast<bool*>(bool_data_passed);
    *does_entity_exist = true;
    return 0;
}


