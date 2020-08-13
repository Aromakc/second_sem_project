#include "user_authentication.h"


void user_authenication::display_resgister_form(const HANDLE& hout)
{
    std::string first_name;
    std::string last_name;
    std::string address;
    std::string city;
    std::string country;
    int country_code;
    std::string user_name;
    std::string password_hashed;

    
    display_first_page(hout,first_name,last_name,address,city,country,country_code);
    display_second_page(hout, user_name, password_hashed);

    std::cout << first_name << std::endl;
    std::cout << last_name << std::endl;
    std::cout << city << std::endl;
    std::cout << country << std::endl;
    std::cout << country_code << std::endl;
}

void user_authenication::display_first_page(const HANDLE& hout, std::string& first_name, std::string& last_name, std::string& address, std::string& city, std::string& country ,int& country_code)
{
    clear_screen(hout, 15, 11);
    create_screen_outline(hout, "Registration: Page - 1", "*", 15);
 
    goto_xy(hout, 0, 3);
    show_cursor(hout, TRUE);

    center_allign_text_print(hout, "******INSTRUCTIONS******\n", 15);

   

    move_cursor_off_left_edge_and_print(hout, "First Name? ", 15);
    std::cin >> first_name;
    
    move_cursor_off_left_edge_and_print(hout, "Last Name? ", 15);
    std::cin >> last_name;
    
    move_cursor_off_left_edge_and_print(hout, "Address? ", 15);
    std::cin >> address;

    move_cursor_off_left_edge_and_print(hout, "City? ", 15);
    std::cin >> city;
    
    sqlite3* db = open_db("restaurants_info.db");

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hout, &csbi);

    int no_of_try = 0;
    while (true) {
       
        move_cursor_off_left_edge_and_print(hout, "Country? ", (no_of_try >= 1) ? 4 : 15);
        clear_current_line(hout);
        std::cin >> country;

        move_cursor_off_left_edge_and_print(hout, "Country Code? ", (no_of_try >= 1) ? 4 : 15);
        clear_current_line(hout);
        
        //forcing user to enter an integer
        //if integer is not entered then the other 'type' entered and stored in input buffer will be ignored and cleared
        if (!(std::cin >> country_code)) {
            std::cin.clear(); //clear previous input
            std::cin.ignore(123, '\n');
        }

        //if the country is not in database then user has to reenter the country name and its specific country code
        if (validate_country(db, country, country_code)) {
            break;
        }

        no_of_try++;
        goto_xy(hout, csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y);
    }

    sqlite3_close(db);
}

void user_authenication::display_second_page(const HANDLE& hout, std::string& user_name, std::string& hashed_password)
{
    clear_screen(hout, 15, 11);
    create_screen_outline(hout, "Registration: Page - 1", "*", 15);

    goto_xy(hout, 0, 3);
    show_cursor(hout, TRUE);

    center_allign_text_print(hout, "******INSTRUCTIONS******\n", 15);
    
    
    sqlite3* db = open_db("restaurants_info.db");

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hout, &csbi);

    int no_of_try_user_name = 0;
    while (true) {
        move_cursor_off_left_edge_and_print(hout, "User Name? ", (no_of_try_user_name >= 1) ? 4 : 15);
        clear_current_line(hout);
        std::cin >> user_name;

        if (!does_user_name_exists(db, user_name)) {
            break;
        }
        no_of_try_user_name++;
        goto_xy(hout, csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y);
    }

    std::string temp_password;
    std::string temp_password_again;

    GetConsoleScreenBufferInfo(hout, &csbi);

    int no_of_try_password = 0;
    while (true) {
        move_cursor_off_left_edge_and_print(hout, "Password? ", (no_of_try_password >= 1) ? 4 : 15);
        clear_current_line(hout);
        std::cin >> temp_password;


        move_cursor_off_left_edge_and_print(hout, "Confirm Password? ", (no_of_try_password >= 1) ? 4 : 15);
        clear_current_line(hout);
        std::cin >> temp_password_again;

        if (strcmp(temp_password.c_str(), temp_password_again.c_str()) == 0) {
            break;
        }
        no_of_try_password++;
        goto_xy(hout, csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y);
    }
    
    
    sqlite3_close(db);
}

bool user_authenication::validate_country(sqlite3* db, const std::string& country_name, int country_code)
{
    std::string sql_cmd = "SELECT name FROM country WHERE name = \"" + to_upper_case(country_name) + "\" AND countryCode = " + std::to_string(country_code) + ";";
    return does_entity_exist(db, sql_cmd);
}


