#pragma once
#include <iostream>
#include <string>
#include "cuisines.h"
#include <sqlite3.h>
#include <stdlib.h>
#include "sqlite_wrapper.h"
#include <Windows.h>
#include "basic_functions.h"

class restaurants {
private:
	int resturant_id;
	std::string name;
	std::string city;
	std::string	address;
	std::string country;
	int country_code;

	cuisines* user_dishes;
	
	int food_price_range;
	
	bool has_online_deliviry;
	bool has_table_booking;
	bool has_switch_to_order_menu;
	
	int avg_rating;
	int votes;

public:
	static void display_top_k(sqlite3*, unsigned int);
	static int display_top_k_callback(void* not_used, int argc, char** argv, char** azColName);
};
