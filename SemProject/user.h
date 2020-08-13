#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "favourites.h"

class user {

private:
	int user_id;
	std::string first_name;
	std::string last_name;
	std::string city;
	std::string country;
	int country_code;


public:
	user();
	user(int user, const std::string&, const std::string&,const std::string&,const std::string&, int);
	static bool does_user_name_exists(sqlite3* db, const std::string& userName);
};
