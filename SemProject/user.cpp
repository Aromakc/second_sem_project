#include "user.h"

user::user()
	:first_name(""), last_name(""), city(""), address(""), country(""), country_code(0), 
	 online_book("no"), online_delivery("no"), switch_menu("no"),user_pref_cuisine(new cuisines())
{
}

user::user(const std::string& first_name, const std::string& last_name, const std::string& address, const std::string& city, const std::string& country, int country_code, const std::string& online_book, const std::string& online_delivery, const std::string& switch_menu, std::vector<std::string>& pref_cuisines)
	:first_name(first_name), last_name(last_name), address(address) ,city(city), country(country), country_code(country_code), 
	 online_book(online_book), online_delivery(online_delivery), switch_menu(switch_menu), user_pref_cuisine(new cuisines(pref_cuisines))
{
}

user::~user()
{
	delete user_pref_cuisine;
}

void user::display_user_profile(const HANDLE& hout)
{
	clear_screen(hout, 15, 11);
	create_screen_outline(hout, "User Profile", "*", 0);

	goto_xy(hout, 0, 3);
	show_cursor(hout, TRUE);
	
	move_cursor_off_left_edge_and_print(hout, "Name: " + this->first_name + " " + this->last_name + '\n', 15);
	move_cursor_off_left_edge_and_print(hout, "Address: " + this->address + '\n', 15);
	move_cursor_off_left_edge_and_print(hout, "City: " + this->city + '\n', 15);
	move_cursor_off_left_edge_and_print(hout, "Country: " + this->country + '\n', 15);
	move_cursor_off_left_edge_and_print(hout, "Prefers online booking? " + this->online_book + '\n', 15);
	move_cursor_off_left_edge_and_print(hout, "Prefers online delivery? " + this->online_delivery + '\n', 15);
	move_cursor_off_left_edge_and_print(hout, "Prefers online booking? " + this->online_book + '\n', 15);

	std::vector<std::string> user_food_pref = this->user_pref_cuisine->get_cuisines();
	center_allign_text_print(hout, "***************User Cuisine Preferences*********************\n", 15);
	for (size_t i = 0; i < user_food_pref.size(); i++) {
		center_allign_text_print(hout, user_food_pref[i], 15);
		std::cout << std::endl;
	}
}

void user::set_personal_info(const std::string& first_name, const std::string& last_name, const std::string& address, const std::string& city, const std::string& country, int country_code)
{
	this->first_name = first_name;
	this->last_name = last_name;
	this->address = address;
	this->city = city;
	this->country = country;
	this->country_code = country_code;
}

void user::set_preference(const std::string& online_book, const std::string& online_delivery, const std::string& switch_menu)
{
	this->online_book = online_book;
	this->online_delivery = online_delivery;
	this->switch_menu = switch_menu;
}

void user::add_user_perf_cuisines(const std::vector<std::string>& food_list)
{
	this->user_pref_cuisine->add_cuisine_list(food_list);
}

bool user::does_user_name_exists(sqlite3* db, const std::string& userName )
{
	std::string sql_cmd = "SELECT user_name FROM user_auth WHERE user_name = \"" + userName + "\";";
	return does_entity_exist(db,sql_cmd);
}

