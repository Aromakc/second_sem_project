#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "cuisines.h"
#include "menu.h"
#include "sqlite_wrapper.h"
#include "restaurants.h"

class user {

protected:
	int id;
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

	std::vector<std::pair<std::string, std::string>> favourite_rest_list;
	std::vector<std::pair<std::string, std::string>> checked_In_list;

public:
	user();
	user(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, int, const std::string&, const std::string&, 
		const std::string&, std::vector<std::string>&, const std::vector<std::pair<std::string, std::string>>&, const std::vector<std::pair<std::string, std::string>>&);

	user(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, int, const std::string&, const std::string&,
		const std::string&, std::vector<std::string>&);
	~user();
	
	
	

	void set_personal_info(int id, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, int);
	void set_preference(const std::string&, const std::string&, const std::string&);
	void build_user_perf_cuisines(const std::vector<std::string>& food_list);
	void build_user_fav_list(const std::vector<std::pair<std::string, std::string>>& fav_list);
	void build_user_checkIn_list(const std::vector<std::pair<std::string, std::string>>& checkIn_list);
	void set_id(int id);
	int get_id();

	
	void display_home_page_and_process_choice(const HANDLE& hout);
	static bool does_user_name_exists(sqlite3* db, const std::string& userName);

private:
	static unsigned int display_home_page_and_get_choice(const HANDLE& hout);
	
	void review_and_rate(const HANDLE& hout);
	void add_to_favourites(const HANDLE& hout);
	void check_in(const HANDLE& hout);

	void display_user_profile(const HANDLE& hout);
	void display_reviews(const HANDLE& hout);
	void view_restaurant_info(const HANDLE& hout);
	void display_user_favourites(const HANDLE& hout);
	void display_user_checkIns(const HANDLE& hout);

	bool store_review_rate_in_db(sqlite3* db, std::string review, std::string time_stamp, double rate, restaurants& reviewer);
	bool store_fav_in_db(sqlite3* db, restaurants& fav_resturant);
	bool store_checked_in_db(sqlite3* db, restaurants& checkedIn_resturant);
};
