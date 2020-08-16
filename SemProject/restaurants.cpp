#include "restaurants.h"

//constrctors
restaurants::restaurants()
	:resturant_id(0), name(""), address(""), city(""), country(""), country_code(0),
	dishes(new cuisines()), food_price_range(0), has_table_booking("no"), has_online_deliviery("no"), has_switch_to_order_menu("no"),
	avg_rating(0.0), votes(0)
{
}

restaurants::restaurants(int id, const std::string& name, const std::string& address, const std::string& city, const std::string& country, int country_code, std::vector<std::string>& cuisine_list, int price_range, const std::string& table_book, const std::string& online_del, const std::string& switch_menu, double avg_rate, int votes)
	:resturant_id(id), name(name), address(address), city(city), country(country), country_code(country_code), 
	 dishes(new cuisines(cuisine_list)), food_price_range(price_range), has_table_booking(table_book), has_online_deliviery(online_del), has_switch_to_order_menu(switch_menu),
	 avg_rating(avg_rate), votes(votes)
{
}
//constructors ends

//setter
void restaurants::set_rest_info(int id, const std::string& name, const std::string& address, const std::string& city, const std::string& country, int country_code)
{
	this->resturant_id = id;
	this->name = name;
	this->address = address;
	this->city = city;
	this->country = country;
	this->country_code = country_code;
}

void restaurants::set_rest_perf_cuisines(const std::vector<std::string>& food_list)
{
	this->dishes->add_cuisine_list(food_list);
}

void restaurants::set_rest_price_range(int price_range)
{
	this->food_price_range = price_range;
}

void restaurants::set_rest_features(const std::string& table_book, const std::string& online_delivery, const std::string& switch_to_order)
{
	this->has_table_booking = table_book;
	this->has_online_deliviery = online_delivery;
	this->has_switch_to_order_menu = switch_to_order;
}

void restaurants::load_rating(int avg_rate, int votes)
{
	this->avg_rating = avg_rate;
	this->votes = votes;
}
//setter end

//method and elper to display k resturant
void restaurants::display_top_k(sqlite3* db, unsigned int k)
{

	char* err_msg;
	std::string sql_cmd = "SELECT restName, city, avgRate FROM restAddressInfo \
						   INNER JOIN restRatings ON restAddressInfo.rest_id = restRatings.rest_id \
						   WHERE avgRate > 4.5 AND votes > 2000 \
						   ORDER BY avgRate DESC LIMIT "  + std::to_string(k) + ";";

	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	
	//creating the top kresturants table column names
	std::cout << std:: endl;

	move_cursor_off_left_edge_and_print(hout, "***************************** Highly Rated Restaurants ************************\n", (0 + 9 * 16));
	move_cursor_off_left_edge_and_print(hout, "Retaurant Name", (0 + 15 * 16));
	set_cursor_at_middle_and_print(hout, "Location", (0 + 12 * 16));
	set_cursor_near_right_and_print(hout, "Rating\n", (0 + 15 * 16));
	std::cout << std::endl;
	//top k resturant table column creation completed
	
	SetConsoleTextAttribute(hout, 15);
	int err_code = sqlite3_exec(db, sql_cmd.c_str(), display_top_k_callback, NULL, &err_msg);
	if (err_code != SQLITE_OK) {
		std::cerr << err_msg << std::endl;
	}
}
int restaurants::display_top_k_callback(void* not_used, int argc, char** argv, char** azColName)
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	

	for (int i = 0; i < argc; i++)
	{
		if (i == 0) {
			move_cursor_off_left_edge_and_print(hout, (std::string)argv[i], (0 + 15 * 16));
		}
		else if (i == 1) {
			set_cursor_at_middle_and_print(hout, (std::string)argv[i], (0 + 12 * 16));
		}
		else{
			set_cursor_near_right_and_print(hout, (std::string)argv[i], (0 + 15 * 16));
		}
	}
	std::cout << std::endl;
	SetConsoleTextAttribute(hout, 15);
	return 0;
}
//method and elper to display k resturant ends

//method and helper to find the no of retaurant with the given name in db
unsigned int restaurants::number_of_rest(sqlite3* db, const std::string& restaurant_name)
{
	unsigned int no_of_rest;
	char* err_msg;
	int err_code;

	std::string sql_cmd = "SELECT count(rest_id) FROM restAddressInfo WHERE restName = \"" + restaurant_name + "\";";

	err_code = sqlite3_exec(db, sql_cmd.c_str(), rest_no_callback, &no_of_rest, &err_msg);
	if (err_msg != SQLITE_OK) {
		std::cerr << err_msg << std::endl;
	}

	return no_of_rest;
}
int restaurants::rest_no_callback(void* memory_to_store_rest_no, int argc, char** argv, char** azColName)
{
	int* rest_no = static_cast<int*>(memory_to_store_rest_no);
	*rest_no = std::stoi(argv[0]);
	return 0;
}
std::vector<std::string> restaurants::get_city_list(sqlite3* db, const std::string& restaurant_name)
{
	std::vector<std::string> city_list;
	char* err_msg;
	int err_code;

	std::string sql_cmd = "SELECT city FROM restAddressInfo WHERE restName = \"" + restaurant_name + "\";";

	err_code = sqlite3_exec(db, sql_cmd.c_str(), city_list_callback, &city_list, &err_msg);
	if (err_msg != SQLITE_OK) {
		std::cerr << err_msg << std::endl;
	}
	return city_list;
}

int restaurants::city_list_callback(void* memory_to_store_list, int argc, char** argv, char** azColName)
{
	std::vector<std::string>* city_list = static_cast<std::vector<std::string>*>(memory_to_store_list);
	city_list->emplace_back(argv[0]);
	return 0;
}


void restaurants::search_rest(const HANDLE& hout, restaurants& rest)
{
	clear_screen(hout, 15, 11);
	create_screen_outline(hout, "Search Restaurant", "*", 15);
	goto_xy(hout, 0, 3);
	show_cursor(hout, TRUE);

	center_allign_text_print(hout, "******INSTRUCTIONS******\n", 15);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hout, &csbi);
	std::string rest_name;
	int no_of_try = 0;

	sqlite3* db = open_db("restaurants_info.db");
	while (true) {
		move_cursor_off_left_edge_and_print(hout, "Restaurant Name? ", (no_of_try >= 1) ? 4 : 15);
		clear_current_line(hout);
		std::getline(std::cin, rest_name);

		if (does_resturant_exist(db, rest_name)) {
			break;
		}
		no_of_try++;
		goto_xy(hout, csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y);
	}

	display_resturant_info(hout, db, rest, rest_name);
	
}

void restaurants::display_resturant_info(const HANDLE& hout, sqlite3* db, restaurants& rest, const std::string& rest_name)
{

	if (!load_restaurant_info(db, rest_name, rest)) {
		move_cursor_off_left_edge_and_print(hout, "Restaurant Not Found In Our Record\n", 4);
	}

	clear_screen(hout, 15, 11);
	create_screen_outline(hout, "Restaurant Info", "*", 15);
	goto_xy(hout, 0, 3);

	move_cursor_off_left_edge_and_print(hout, "Restaurant Name: " + rest.name + "\n", 15);
	move_cursor_off_left_edge_and_print(hout, "Address: " + rest.address + "\n", 15);
	move_cursor_off_left_edge_and_print(hout, "City: " + rest.city + "\n", 15);
	move_cursor_off_left_edge_and_print(hout, "Country: " + rest.country + "\n", 15);
	move_cursor_off_left_edge_and_print(hout, "Has online table booking?: " + rest.has_table_booking + "\n", 15);
	move_cursor_off_left_edge_and_print(hout, "Has online delivery?: " + rest.has_online_deliviery + "\n", 15);
	move_cursor_off_left_edge_and_print(hout, "Has switch to order menu?:: " + rest.has_switch_to_order_menu + "\n", 15);
	
	move_cursor_off_left_edge(hout);
	print_line_with_color(hout, "Average Rating: ", 15);
	std::cout << std::fixed;
	std::cout << std::setprecision(2);
	std::cout << rest.avg_rating << std::endl;

	move_cursor_off_left_edge_and_print(hout, "Votes: " + std::to_string(rest.votes), 15);
	std::cout << std::endl;

	std::vector<std::string> rest_cuisine_list = rest.dishes->get_cuisines();
	center_allign_text_print(hout, "***************Available Cuisines*********************\n", 15);
	for (size_t i = 0; i < rest_cuisine_list.size() ; i++) {
		center_allign_text_print(hout, rest_cuisine_list[i], 15);
		std::cout << std::endl;
	}

	sqlite3_close(db);
}

//method to know wether a resturant exists
bool restaurants::does_resturant_exist(sqlite3* db, const std::string& restaurant_name)
{
	std::string sql_search_cmd = "SELECT rest_id FROM restAddressInfo WHERE restName = \"" + restaurant_name + "\";";
	return does_entity_exist(db,sql_search_cmd);
}

//methods and helpers that loads the given resturant into a resturants object 
bool restaurants::load_restaurant_info(sqlite3* db, const std::string& rest_name, restaurants& rest_to_load)
{
	if (!does_resturant_exist(db, rest_name)) {
		return false;
	}

	unsigned int no_of_duplicate = number_of_rest(db, rest_name);
	
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	std::string selected_city;
	std::vector<std::string> list_of_city;

	if (no_of_duplicate > 1) {
		clear_screen(hout, 15, 11);
		create_screen_outline(hout, "Search Restaurant - (Ambiguity)", "*", 4);
		goto_xy(hout, 0, 3);
		center_allign_text_print(hout, "********INSTRUCTIONS*******\n", 15);
		center_allign_text_print(hout, "Restaurant with given name has been found in multiple cities as below.\n",  15);
		center_allign_text_print(hout, "So choose the city name as prompted. If you see a city repeated multiple\n", 15);
		center_allign_text_print(hout, "time, then it means there are multiple restaurants with that same name in\n", 15);
		center_allign_text_print(hout, "multiple places within the same city(city with repeated name), but all of\n", 15);
		center_allign_text_print(hout, "are of same time, i.e they have same type of cuisines and services.\n", 15);
		std::cout << std::endl;

		list_of_city = get_city_list(db, rest_name);
		
		int j = 0;
		for (size_t i = 0; i < list_of_city.size(); i++) {
			move_cursor_off_left_edge_and_print(hout, list_of_city[i], 15);
			j++;
			if (j > 5) {
				j = 0;
				std::cout << std::endl;
			}
		}
		std::cout << std::endl;

		GetConsoleScreenBufferInfo(hout, &csbi);
		int no_of_try = 0;
		while (true) {
			std::cout << std::endl;
			move_cursor_off_left_edge_and_print(hout, "Enter the city name from above list to view the restaurant: ", (no_of_try >= 1) ? 4 : 15);
			clear_current_line(hout);
			std::getline(std::cin, selected_city);
			if (std::find(list_of_city.begin(), list_of_city.end(), selected_city) != list_of_city.end()) {
				break;
			}
			no_of_try++;
			goto_xy(hout, csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y);
		}
	}



	char* err_msg;
	int err_code;

	std::string load_rest_info;

	if (no_of_duplicate > 1) {
		load_rest_info = "SELECT rest_id, restName, address, city, country.name, restAddressInfo.countryCode FROM restAddressInfo "
						 "INNER JOIN country ON country.countryCode = restAddressInfo.countryCode "
						 "WHERE restName = \"" + rest_name + "\" AND city = \"" + selected_city + "\";";
	}
	else {
		load_rest_info = "SELECT rest_id, restName, address, city, country.name, restAddressInfo.countryCode FROM restAddressInfo "
						 "INNER JOIN country ON country.countryCode = restAddressInfo.countryCode "
						 "WHERE restName = \"" + rest_name + "\";";
	}

	err_code = sqlite3_exec(db, load_rest_info.c_str(), load_rest_info_callback, &rest_to_load, &err_msg);
	if (err_code != SQLITE_OK) {
		std::cerr << err_msg << std::endl;
	}


	std::string load_rest_cuisine_list;
	if (no_of_duplicate > 1) {
		load_rest_cuisine_list = "SELECT cuisine FROM restFoodTypes INNER JOIN restAddressInfo ON restAddressInfo.rest_id = restFoodTypes.rest_id " 
								 "WHERE restAddressInfo.rest_id = " + std::to_string(rest_to_load.resturant_id) + " AND restAddressInfo.city = \"" + selected_city + "\";";
	}
	else {
		load_rest_cuisine_list = "SELECT cuisine FROM restFoodTypes WHERE rest_id = " + std::to_string(rest_to_load.resturant_id) + ";";
	}
	std::vector<std::string> cuisine_list;
	err_code = sqlite3_exec(db, load_rest_cuisine_list.c_str(), load_cuisines_callback, &cuisine_list, &err_msg);
	if (err_code != SQLITE_OK) {
		std::cerr << err_msg << std::endl;
	}
	rest_to_load.set_rest_perf_cuisines(cuisine_list);

	std::string load_price_range;
	if (no_of_duplicate > 1) {
		load_price_range = "SELECT priceRange FROM restPriceRange INNER JOIN restAddressInfo ON restAddressInfo.rest_id = restPriceRange.rest_id " 
						   "WHERE restAddressInfo.rest_id = " + std::to_string(rest_to_load.resturant_id) + " AND restAddressInfo.city = \"" + selected_city + "\";";
	}
	else {
		load_price_range = "SELECT priceRange FROM restPriceRange WHERE rest_id = " + std::to_string(rest_to_load.resturant_id) + ";";
	}
	err_code = sqlite3_exec(db, load_price_range.c_str(), load_rest_price_range_callback, &rest_to_load, &err_msg);
	if (err_code != SQLITE_OK) {
		std::cerr << err_msg << std::endl;
	}

	std::string load_rest_feat;
	if (no_of_duplicate > 1) {
		load_rest_feat = "SELECT hasTableBookingooking, hasOnlineDelivery, switchToOrderMenu FROM restFeatures " 
						 "INNER JOIN restAddressInfo ON restAddressInfo.rest_id = restFeatures.rest_id "
						 "WHERE restAddressInfo.rest_id = " + std::to_string(rest_to_load.resturant_id) + " AND restAddressInfo.city = \"" + selected_city + "\";";
	}
	else {
		load_rest_feat = "SELECT hasTableBookingooking, hasOnlineDelivery, switchToOrderMenu FROM restFeatures WHERE rest_id = " + std::to_string(rest_to_load.resturant_id) + ";";
	}
	err_code = sqlite3_exec(db, load_rest_feat.c_str(), load_rest_features_callback, &rest_to_load, &err_msg);
	if (err_code != SQLITE_OK) {
		std::cerr << err_msg << std::endl;
	}

	std::string load_rest_rate;
	if (no_of_duplicate > 1) {
		load_rest_rate = "SELECT avgRate, votes FROM restRatings "
						 "INNER JOIN restAddressInfo ON restAddressInfo.rest_id = restRatings.rest_id "
						 "WHERE restAddressInfo.rest_id = " + std::to_string(rest_to_load.resturant_id) + " AND restAddressInfo.city = \"" + selected_city + "\";";
	}
	else {
		load_rest_rate = "SELECT avgRate, votes FROM restRatings WHERE rest_id = " + std::to_string(rest_to_load.resturant_id) + ";";
	}

	
	err_code = sqlite3_exec(db, load_rest_rate.c_str(), load_rest_rating_callback, &rest_to_load, &err_msg);
	if (err_code != SQLITE_OK) {
		std::cerr << err_msg << std::endl;
	}
	return true;
}

int restaurants::load_rest_info_callback(void* memory_to_store_rest_obj, int argc, char** argv, char** azColName)
{
	restaurants* rest_to_load = static_cast<restaurants*>(memory_to_store_rest_obj);
	rest_to_load->set_rest_info(std::stoi(argv[0]), argv[1], argv[2], argv[3], argv[4], std::stoi(argv[5]));
	return 0;
}

int restaurants::load_cuisines_callback(void* memory_to_store_cuisine, int argc, char** argv, char** azColName)
{
	std::vector<std::string>* cuisine_list = static_cast<std::vector<std::string>*>(memory_to_store_cuisine);
	cuisine_list->emplace_back(argv[0]);
	return 0;
}

int restaurants::load_rest_price_range_callback(void* memory_to_store_rest_obj, int argc, char** argv, char** azColName)
{
	restaurants* rest_to_load = static_cast<restaurants*>(memory_to_store_rest_obj);
	rest_to_load->set_rest_price_range(std::stoi(argv[0]));
	return 0;
}

int restaurants::load_rest_features_callback(void* memory_to_store_rest_obj, int argc, char** argv, char** azColName)
{
	restaurants* rest_to_load = static_cast<restaurants*>(memory_to_store_rest_obj);
	rest_to_load->set_rest_features(argv[0], argv[1], argv[2]);
	return 0;
}

int restaurants::load_rest_rating_callback(void* memory_to_store_rest_obj, int argc, char** argv, char** azColName)
{
	restaurants* rest_to_load = static_cast<restaurants*>(memory_to_store_rest_obj);
	rest_to_load->load_rating(std::stod(argv[0]), std::stoi(argv[1]));
	return 0;
}
//methods and helpers that loads the given resturant into a resturants object ends