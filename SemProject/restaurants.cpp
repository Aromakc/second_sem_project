#include "restaurants.h"

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
