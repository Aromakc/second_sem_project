#pragma once
#include <iostream>
#include <string>
#include "cuisines.h"
#include <sqlite3.h>
#include <stdlib.h>
#include "sqlite_wrapper.h"
#include <Windows.h>
#include "basic_functions.h"
#include <algorithm>

class restaurants {
private:
	int resturant_id;
	std::string name;
	std::string	address;
	std::string city;
	std::string country;
	int country_code;

	cuisines* dishes;
	
	int food_price_range;
	
	std::string has_table_booking;
	std::string has_online_deliviery;
	std::string has_switch_to_order_menu;
	
	double avg_rating;
	int votes;

public:
	restaurants();
	restaurants(int, const std::string&, const std::string&, const std::string&, const std::string&, int, std::vector<std::string>&, int, const std::string&, const std::string&, const std::string&, double, int);

	void set_rest_info(int, const std::string&, const std::string&, const std::string&, const std::string&, int);
	void set_rest_perf_cuisines(const std::vector<std::string>& food_list);
	void set_rest_price_range(int);
	void set_rest_features(const std::string&, const std::string&, const std::string&);
	void load_rating(int, int);

	static void display_top_k(sqlite3*, unsigned int);
	static void search_rest(const HANDLE& hout, restaurants& rest);
	static void display_resturant_info(const HANDLE& hout, sqlite3* db ,restaurants& rest,const std::string& restaurant_name);
	

	


private:
	static bool does_resturant_exist(sqlite3* db, const std::string& restaurant_name);
	static int display_top_k_callback(void* not_used, int argc, char** argv, char** azColName);

	static unsigned int number_of_rest(sqlite3* db, const std::string& restaurant_name);
	static int rest_no_callback(void* memory_to_store_rest_no, int argc, char** argv, char** azColName);

	static std::vector<std::string> get_city_list(sqlite3* db, const std::string& restaurant_name);
	static int city_list_callback(void* memory_to_store_list, int argc, char** argv, char** azColName);

	static bool load_restaurant_info(sqlite3* db, const std::string& rest_name, restaurants& rest_to_load);
	static int load_rest_info_callback(void* memory_to_store_rest_obj, int argc, char** argv, char** azColName);
	static int load_cuisines_callback(void* memory_to_store_cuisine, int argc, char** argv, char** azColName);
	static int load_rest_price_range_callback(void* memory_to_store_rest_obj, int argc, char** argv, char** azColName);
	static int load_rest_features_callback(void* memory_to_store_rest_obj, int argc, char** argv, char** azColName);
	static int load_rest_rating_callback(void* memory_to_store_rest_obj, int argc, char** argv, char** azColName);
};