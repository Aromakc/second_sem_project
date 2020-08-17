#include "user.h"

user::user()
	:id(0), first_name(""), last_name(""), city(""), address(""), country(""), country_code(0), 
	 online_book("no"), online_delivery("no"), switch_menu("no"),user_pref_cuisine(new cuisines())
{
}

user::user(const std::string& first_name, const std::string& last_name, const std::string& address, const std::string& city, const std::string& country, int country_code, const std::string& online_book, const std::string& online_delivery, const std::string& switch_menu, std::vector<std::string>& pref_cuisines)
	:id(0),first_name(first_name), last_name(last_name), address(address) ,city(city), country(country), country_code(country_code), 
	 online_book(online_book), online_delivery(online_delivery), switch_menu(switch_menu), user_pref_cuisine(new cuisines(pref_cuisines))
{

}

user::~user()
{
	delete user_pref_cuisine;
}

int user::get_id()
{
	return this->id;
}





void user::set_personal_info(int id, const std::string& first_name, const std::string& last_name, const std::string& address, const std::string& city, const std::string& country, int country_code)
{
	this->id = id;
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

void user::set_id(int id)
{
	this->id = id;
}


unsigned int user::display_home_page_and_get_choice(const HANDLE& hout)
{
	clear_screen(hout, 0, 7);
	menu* home_page_menu = new menu("Home");
	home_page_menu->add_option("Recomend");
	home_page_menu->add_option("Rate and Review");
	home_page_menu->add_option("Check In");
	home_page_menu->add_option("Add Favourites");
	home_page_menu->add_option("Search Restaurant");
	home_page_menu->add_option("View Reviews");
	home_page_menu->add_option("View My Profile");
	home_page_menu->add_option("Log Out");
	home_page_menu->display_menu(hout, "%", "tm", 0, 9);
	return home_page_menu->get_selection(hout);
}

void user::process_home_page_choice(const HANDLE& hout,unsigned int choice) {
	if (choice == 0) {
		clear_screen(hout);
		std::cout << "Recommendation Coming soon!" << std::endl;
	}
	else if (choice == 1) {
		review_and_rate(hout);
	}
	else if (choice == 2) {
		clear_screen(hout);
		std::cout << "Check in soon!" << std::endl;
	}
	else if (choice == 3) {
		clear_screen(hout);
		std::cout << "Favourites Coming soon" << std::endl;
	}
	else if (choice == 4) {
		view_restaurant_info(hout);
	}
	else if (choice == 5) {
		display_reviews(hout);
	}
	else if (choice == 6) {
		display_user_profile(hout);
	}
	else if(choice == 7){
		clear_screen(hout);
		std::cout << "Logged out!" << std::endl;
	}
	else {
		clear_screen(hout);
		std::cerr << "Unexpected: No such options" << std::endl;
	}
}

void user::review_and_rate(const HANDLE& hout)
{
	restaurants* rest = new restaurants();

	rest->search_rest_and(hout, *rest, "-rvrt");

	clear_screen(hout, 8, 12);
	create_screen_outline(hout, "Review Restaurant", "*", 15);
	goto_xy(hout, 0, 3);
	center_allign_text_print(hout, "******INSTRUCTIONS******\n", 15);

	std::string user_review;
	std::string reviewed_time;
	move_cursor_off_left_edge_and_print(hout, "Your Review? ", 15);
	clear_current_line(hout);
	std::getline(std::cin, user_review);
	

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hout, &csbi);
	int no_of_rating_try = 0;
	double user_rate;
	
	while (true) {
		move_cursor_off_left_edge_and_print(hout, "Rate this restaurant on scale of 1-5 ((low - high) Recommendation)? ", (no_of_rating_try >= 1) ? 4 : 15);
		clear_current_line(hout);
		if (!(std::cin >> user_rate)) {
			std::cin.clear(); //clear previous input
		}

		if (user_rate >= 1 && user_rate <= 5) {
			std::cin.ignore(123, '\n');
			break;
		}

		no_of_rating_try++;
		goto_xy(hout, csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y);
		std::cin.ignore(123, '\n'); //flush out the newline character in cin that otherwise not removed will be eaten by the geline() function and lead to unexpected behaviour
	}

	reviewed_time = current_time_and_date();

	sqlite3* db = open_db("restaurants_info.db");

	if (store_review_rate_in_db(db, user_review, reviewed_time, user_rate , *rest)) {
		std::cout << std::endl;
		center_allign_text_print(hout, "**Reviewed Successfully**", 1);
	}
	else {
		std::cout << std::endl;
		center_allign_text_print(hout, "**Review Failed: Review cannot be more than 90 characters.**", 4);
	}

	rest->~restaurants();
	sqlite3_close(db);
}

void user::display_user_profile(const HANDLE& hout)
{
	clear_screen(hout, 15, 11);
	create_screen_outline(hout, "User Profile", "*", 0);

	goto_xy(hout, 0, 3);
	show_cursor(hout, FALSE);

	move_cursor_off_left_edge_and_print(hout, "Name: " + to_upper_case(this->first_name) + " " + to_upper_case(this->last_name) + '\n', 15);
	move_cursor_off_left_edge_and_print(hout, "Address: " + to_upper_case(this->address) + '\n', 15);
	move_cursor_off_left_edge_and_print(hout, "City: " + to_upper_case(this->city) + '\n', 15);
	move_cursor_off_left_edge_and_print(hout, "Country: " + to_upper_case(this->country) + '\n', 15);
	move_cursor_off_left_edge_and_print(hout, "Prefers online booking? " + to_upper_case(this->online_book) + '\n', 15);
	move_cursor_off_left_edge_and_print(hout, "Prefers online delivery? " + to_upper_case(this->online_delivery) + '\n', 15);
	move_cursor_off_left_edge_and_print(hout, "Prefers online booking? " + to_upper_case(this->online_book) + '\n', 15);

	std::vector<std::string> user_food_pref = this->user_pref_cuisine->get_cuisines();
	center_allign_text_print(hout, "***************User Cuisine Preferences*********************\n", 15);
	for (size_t i = 0; i < user_food_pref.size(); i++) {
		center_allign_text_print(hout, to_upper_case(user_food_pref[i]), 15);
		std::cout << std::endl;
	}
}

void user::display_reviews(const HANDLE& hout) {
	sqlite3* db = open_db("restaurants_info.db");
	restaurants* rest = new restaurants();
	rest->search_rest_and(hout, *rest, "-vr");
	rest->~restaurants();
	sqlite3_close(db);
}

void user::view_restaurant_info(const HANDLE& hout){
	sqlite3* db = open_db("restaurants_info.db");
	restaurants* rest = new restaurants();
	rest->search_rest_and(hout, *rest, "-di");
	rest->~restaurants();
	sqlite3_close(db);
}

bool user::store_review_rate_in_db(sqlite3* db, std::string review, std::string time_stamp, double rate, restaurants& rest)
{
	sqlite3_stmt* st;

	std::string store_review = "INSERT INTO restReviews VALUES(?,?,?,?,?);";
	int res_code = sqlite3_prepare(db, store_review.c_str(), -1, &st, NULL);

	if (res_code == SQLITE_OK) {
		sqlite3_bind_int(st, 1, rest.get_id());
		sqlite3_bind_text(st, 2, review.c_str(), review.length(), SQLITE_TRANSIENT);
		sqlite3_bind_text(st, 3, time_stamp.c_str(), time_stamp.length(), SQLITE_TRANSIENT);
		sqlite3_bind_int(st, 4, this->id);
		sqlite3_bind_double(st, 5, rate);
		sqlite3_step(st);
		sqlite3_finalize(st);
	}
	else {
		return false;
	}

	if (!(rest.update_avg_rating(db, rate))) {
		return false;
	}

	return true;
}

bool user::does_user_name_exists(sqlite3* db, const std::string& userName )
{
	std::string sql_cmd = "SELECT user_name FROM user_auth WHERE user_name = \"" + userName + "\";";
	return does_entity_exist(db,sql_cmd);
}



