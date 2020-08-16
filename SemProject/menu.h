#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "basic_functions.h"

class menu {
private:
	std::string menu_title;
	std::vector<std::string> menu_options;
public:
	menu(const std::string&);
	bool add_option(const std::string&);
	void display_menu(const HANDLE&, const std::string&, const std::string&, WORD, WORD);
	unsigned int get_selection(const HANDLE&);
	void display_exit_message(const HANDLE& hout,const std::string& quit_msg_title,const std::string& quit_screen);

private:
	bool does_option_exist(const std::string&);
	inline int calculate_mid_X(int , const CONSOLE_SCREEN_BUFFER_INFO&);
	inline int calculate_mid_Y(int , const CONSOLE_SCREEN_BUFFER_INFO&);
	void display_menu_at_top_left(const HANDLE&, const std::string&);
	void display_menu_at_top_mid(const HANDLE&, const std::string&);
	void display_menu_at_mid(const HANDLE&, const std::string&);
	unsigned int choice_no(std::string);
};
