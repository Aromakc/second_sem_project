#pragma once
#include <iostream>
#include <string>
#include <Windows.h>

#include <time.h>

#include <stdexcept>

#include <openssl/sha.h>
#include <iomanip>
#include <sstream>

std::string to_lower_case(const std::string&);
std::string to_upper_case(const std::string& line);

void create_screen(const HANDLE&);
void clear_screen(const HANDLE&);
void clear_screen(const HANDLE&, int, int);
void goto_xy(const HANDLE&,int, int);
void show_cursor(const HANDLE&, bool);
void clear_line(const HANDLE&, int);
void clear_current_line(const HANDLE&);

void move_cursor_off_left_edge(const HANDLE&);
void set_cursor_at_middle(const HANDLE&);
void set_cursor_near_right(const HANDLE& hout);
void print_line_with_color(const HANDLE&,const std::string&, WORD);

void move_cursor_off_left_edge_and_print(const HANDLE& hout, const std::string& line, WORD color);
void set_cursor_at_middle_and_print(const HANDLE& hout, const std::string& line, WORD color);
void set_cursor_near_right_and_print(const HANDLE& hout, const std::string& line, WORD color);
void center_allign_text_print(const HANDLE& hout, const std::string& line, WORD color);

void create_screen_outline(const HANDLE&, const std::string&, const std::string&, WORD);

std::string generate_salt(const unsigned int len);
std::string getpassword();
std::string sha256(const std::string str);

