#include "menu.h"
#include "basic_functions.h"



menu::menu(const std::string& menu_title)
{
	this->menu_title = menu_title;
}

menu::~menu()
{
}

bool menu::add_option(const std::string& option_name) {
	if (!does_option_exist(option_name)) {
		this->menu_options.push_back(option_name);
		return true;
	}
	return false;
}

void menu::display_menu(const HANDLE& hout, const std::string& pattern, const std::string& position, WORD title_forgC_color, WORD title_bacgC_color)
{
	create_screen_outline(hout, this->menu_title,pattern, (title_forgC_color + title_bacgC_color * 16) );

	if (to_lower_case(position).compare("m") == 0 ) {
		display_menu_at_mid(hout, pattern);
	}
	else if (to_lower_case(position).compare("tm") == 0) {
		display_menu_at_top_mid(hout, pattern);
	}
	else if(to_lower_case(position).compare("tl") == 0){
		display_menu_at_top_left(hout, pattern);
	}else{
		clear_screen(hout);
		std::cout << "Error Code: MenuDesignFlagError; flags: tl, tm, m" << std::endl;
	}
}

unsigned int menu::get_selection(const HANDLE& hout) {
	int no_of_try = 0;
	std::string choice;
	show_cursor(hout, TRUE);
	while (true)
	{
		if (no_of_try >= 1) {
			SetConsoleTextAttribute(hout, 4);
		}
		clear_line(hout, 32);
		std::cout << "Enter your choice: ";
		SetConsoleTextAttribute(hout, 15);
		std::getline(std::cin, choice);
		if (does_option_exist(choice)) {
			return choice_no(choice);
		}
		no_of_try++;
	}
	return -1;
}

void menu::display_exit_message(const HANDLE& hout,const std::string& quit_msg_title ,const std::string& quit_msg)
{
	clear_screen(hout, 11, 15);
	create_screen_outline(hout, quit_msg_title, "%",15);
	goto_xy(hout, 0, 3);

	center_allign_text_print(hout, quit_msg, 15);
	std::cout << std::endl;
}

unsigned int menu::choice_no(std::string choice) {
	for (unsigned int i = 0; i < this->menu_options.size(); i++) {
		if (to_lower_case(choice).compare(to_lower_case(this->menu_options[i])) == 0) {
			return i;
		}
	}
	return -1;
}

void menu::display_menu_at_top_left(const HANDLE& hout, const std::string& pattern) {
	for (int i = 0; i < static_cast<int>(menu_options.size()); i++) {
		goto_xy(hout, 2 , (i + 2));
		std::cout << menu_options[i] << std::endl;
	}
}

void menu::display_menu_at_top_mid(const HANDLE& hout, const std::string& pattern) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hout, &csbi);
	for (int i = 0; i < static_cast<int>(menu_options.size()); i++) {
		goto_xy(hout, calculate_mid_X(i, csbi), (i + 2));
		std::cout << menu_options[i] << std::endl;
	}
}

void menu::display_menu_at_mid(const HANDLE& hout, const std::string& pattern) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hout, &csbi);
	for (int i = 0; i < static_cast<int>(menu_options.size()); i++) {
		goto_xy(hout, calculate_mid_X(i, csbi), calculate_mid_Y(i, csbi));
		std::cout << menu_options[i] << std::endl;
	}
}

bool menu::does_option_exist(const std::string& option_name) {
	for (size_t i = 0; i < (this->menu_options).size(); i++)
	{
		if (to_lower_case(this->menu_options[i]).compare(to_lower_case(option_name)) == 0) {
			return true;
		}
	}
	return false;
}

inline int menu::calculate_mid_X(int option_no, const CONSOLE_SCREEN_BUFFER_INFO& csbi)
{
	return (csbi.dwSize.X / 2) - ( this->menu_options.at(option_no).length() / 2) + 1;
}

inline int menu::calculate_mid_Y(int option_no, const CONSOLE_SCREEN_BUFFER_INFO& csbi)
{
	return (csbi.dwSize.Y / 2) - (this->menu_options.size() / 2) + option_no;
}



