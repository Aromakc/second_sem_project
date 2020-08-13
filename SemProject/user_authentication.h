#pragma once
#include <iostream>
#include <string>
#include "user.h"
#include "basic_functions.h"

class user_authenication : public user{
private:
	std::string user_name;
	std::string password;
	
public:
	static void display_resgister_form(const HANDLE& hout);

private:
	static void display_first_page(const HANDLE& hout, std::string& first_name, std::string& last_name, std::string& address, std::string& city, std::string& country, int& country_code);
	static void display_second_page(const HANDLE& hout, std::string& user_name, std::string& hashed_password);
	static void display_third_page(const HANDLE& hout);
	static bool validate_country(sqlite3* db, const std::string& country_name, int country_code);
};

