#include "user.h"

user::user()
	:user_id(0), first_name(""), last_name(""), city(""), country(""), country_code(0)
{
}

user::user(int user_id, const std::string& first_name, const std::string& last_name, const std::string& city, const std::string& country, int country_code)
	:user_id(user_id), first_name(first_name), last_name(last_name), city(city), country(country), country_code(country_code)
{
}

bool user::does_user_name_exists(sqlite3* db, const std::string& userName )
{
	std::string sql_cmd = "SELECT user_name FROM user_auth WHERE user_name = \"" + to_lower_case(userName) + "\";";
	return does_entity_exist(db,sql_cmd);
}

