#include "basic_functions.h"

std::string to_lower_case(const std::string& line) {
	std::string converted_line;
	for (size_t i = 0; i < line.length(); i++)
	{
		converted_line += static_cast<char>(tolower(line[i]));
	}
	return converted_line;
}

std::string to_upper_case(const std::string& line) {
	std::string converted_line;
	for (size_t i = 0; i < line.length(); i++)
	{
		converted_line += static_cast<char>(toupper(line[i]));
	}
	return converted_line;
}

void create_screen(const HANDLE& hout) {
	//disable the scroll bar
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hout, &csbi);
	SetConsoleScreenBufferSize(hout, { csbi.srWindow.Right - csbi.srWindow.Left + 1, csbi.srWindow.Bottom - csbi.srWindow.Top + 1 });

	//create a unresizable console window with size of  98 char by 35 line; 
	HWND handle = GetConsoleWindow();
	RECT win_rect;
	GetWindowRect(handle, &win_rect);
	MoveWindow(handle, win_rect.left, win_rect.top, 800, 600, TRUE);
	SetWindowLong(handle, GWL_STYLE, GetWindowLong(handle, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
	
	show_cursor(hout, FALSE);
}

void clear_screen(const HANDLE& hout) {
	COORD start_pos = { 0,0 };
	DWORD dwBytesWritten;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hout, &csbi);

	FillConsoleOutputCharacter(hout, (TCHAR)32, csbi.dwSize.X * csbi.dwSize.Y, start_pos, &dwBytesWritten);
	FillConsoleOutputAttribute(hout, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, start_pos, &dwBytesWritten);
	SetConsoleCursorPosition(hout, start_pos);
}

void clear_screen(const HANDLE& hout, int ForgC, int BackC)
{
	WORD color = ForgC + BackC * 16;

	COORD start_pos = { 0,0 };
	DWORD dwBytesWritten;

	SetConsoleTextAttribute(hout, color);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hout, &csbi);

	FillConsoleOutputCharacter(hout, (TCHAR)32, csbi.dwSize.X * csbi.dwSize.Y, start_pos, &dwBytesWritten);
	FillConsoleOutputAttribute(hout, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, start_pos, &dwBytesWritten);
	SetConsoleCursorPosition(hout, start_pos);
}

void goto_xy(const HANDLE& hout, int x, int y)
{
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hout, &cci);
	cci.bVisible = false;
	SetConsoleCursorPosition(hout, { (short)x, (short)y });
}

void move_cursor_off_left_edge(const HANDLE& hout) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hout, &csbi);
	SetConsoleCursorPosition(hout, { csbi.dwCursorPosition.X + 5, csbi.dwCursorPosition.Y });
}

void set_cursor_at_middle(const HANDLE& hout) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hout, &csbi);
	SetConsoleCursorPosition(hout, {(csbi.dwSize.X / 2), csbi.dwCursorPosition.Y });
}
void set_cursor_near_right(const HANDLE& hout) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hout, &csbi);
	SetConsoleCursorPosition(hout, { (csbi.dwSize.X -20), csbi.dwCursorPosition.Y });
}

void show_cursor(const HANDLE& hout, bool choice) {
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hout, &cci);
	cci.bVisible = choice;
	SetConsoleCursorInfo(hout, &cci);
}

void clear_line(const HANDLE& hout, int line_no) {

	COORD start_pos = { 1, (SHORT)line_no };
	DWORD dwBytesWritten;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hout, &csbi);

	FillConsoleOutputCharacter(hout, (TCHAR)32, csbi.dwSize.X - 2, start_pos, &dwBytesWritten);
	FillConsoleOutputAttribute(hout, csbi.wAttributes, csbi.dwSize.X - 2, start_pos, &dwBytesWritten);
	SetConsoleCursorPosition(hout, start_pos);
}

void clear_current_line(const HANDLE& hout) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hout, &csbi);

	COORD start_pos = { csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y };
	DWORD dwBytesWritten;

	FillConsoleOutputCharacter(hout, (TCHAR)32, csbi.dwSize.X - (1 + csbi.dwCursorPosition.X), start_pos, &dwBytesWritten);
	FillConsoleOutputAttribute(hout, csbi.wAttributes, csbi.dwSize.X - (1 + csbi.dwCursorPosition.X), start_pos, &dwBytesWritten);
	SetConsoleCursorPosition(hout, start_pos);

}


void print_line_with_color(const HANDLE& hout,const std::string& line, WORD color) {
	SetConsoleTextAttribute(hout, color);
	std::cout << line;
}

void move_cursor_off_left_edge_and_print(const HANDLE& hout, const std::string& line, WORD color)
{
	move_cursor_off_left_edge(hout);
	print_line_with_color(hout, line, color);
}

void set_cursor_at_middle_and_print(const HANDLE& hout, const std::string& line, WORD color)
{
	set_cursor_at_middle(hout);
	print_line_with_color(hout, line, color);
}

void set_cursor_near_right_and_print(const HANDLE& hout, const std::string& line, WORD color)
{
	set_cursor_near_right(hout);
	print_line_with_color(hout, line, color);
}

void center_allign_text_print(const HANDLE& hout, const std::string& line, WORD color) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hout, &csbi);
	int line_start_pos = (csbi.dwSize.X / 2) - (line.length() / 2) + 1;
	goto_xy(hout, line_start_pos, csbi.dwCursorPosition.Y);
	print_line_with_color(hout, line, color);
}

void create_screen_outline(const HANDLE& hout, const std::string& title, const std::string& pattern, WORD title_color)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hout, &csbi);
	int title_start_pos = (csbi.dwSize.X / 2) - (title.length() / 2) + 1;
	int title_end_pos = title_start_pos + title.length() - 1;

	int j = 0;
	for (int i = 0; i < csbi.dwSize.X; i++) {
		SetConsoleTextAttribute(hout, csbi.wAttributes);
		goto_xy(hout, i, csbi.dwSize.Y - 2);
		std::cout << pattern << std::endl;
		goto_xy(hout, i, 0);
		if (i >= title_start_pos && i <= title_end_pos) {
			SetConsoleTextAttribute(hout, title_color);
			std::cout << title[j] << std::endl;
			j++;
			continue;
		}
		std::cout << pattern << std::endl;
	}

	for (int i = 0; i < (csbi.dwSize.Y - 1); i++) {
		goto_xy(hout, 0, i);
		std::cout << pattern << std::endl;
		goto_xy(hout, csbi.dwSize.X - 1, i);
		std::cout << pattern << std::endl;
	}

	goto_xy(hout, 0, 0);
}