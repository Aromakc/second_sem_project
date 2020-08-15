#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "favourites.h"
#include "cuisines.h"

class user {

protected:
	std::string first_name;
	std::string last_name;
	std::string address;
	std::string city;
	std::string country;
	int country_code;
	std::string online_book;
	std::string online_delivery;
	std::string switch_menu;
	cuisines* user_pref_cuisine;


public:
	user();
	user(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, int, const std::string&, const std::string&, const std::string&, std::vector<std::string>&);
	~user();
	
	void display_user_profile(const HANDLE& hout);

	void set_personal_info(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, int);
	void set_preference(const std::string&, const std::string&, const std::string&);
	void add_user_perf_cuisines(const std::vector<std::string>& food_list);


	static bool does_user_name_exists(sqlite3* db, const std::string& userName);
};
