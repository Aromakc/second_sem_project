#include <stdio.h>
#include <iostream>
#include "menu.h"
#include <Windows.h>
#include "basic_functions.h"
#include "sqlite_wrapper.h"
#include "restaurants.h"
#include "user_authentication.h"

unsigned int display_main_menu(const HANDLE& hout, menu& main_menu);
void process_main_menu_choice(const HANDLE& hout, unsigned int menu_choice, user& logged_in_user);
int main()
{
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    create_screen(hout);
    clear_screen(hout, 0, 8);
    menu* mainMenu = new menu("Resturantey");
    user* logged_in_user = new user();
    unsigned int option_choice = display_main_menu(hout, *mainMenu);
    process_main_menu_choice(hout, option_choice, *logged_in_user);
    logged_in_user->display_user_profile(hout);
}

unsigned int display_main_menu(const HANDLE& hout, menu& main_menu) {
    main_menu.add_option("Login");
    main_menu.add_option("Register");
    main_menu.add_option("Search");
    main_menu.add_option("Exit");
    main_menu.display_menu(hout, "*", "tm", 0, 9);
    sqlite3* db = open_db("restaurants_info.db");
    restaurants::display_top_k(db, 15);
    sqlite3_close(db);
    return main_menu.get_selection(hout);
}


void process_main_menu_choice(const HANDLE& hout, unsigned int menu_choice, user& logged_in_user) {
    if (menu_choice == 0) {
        clear_screen(hout);
        user_authenication::login_form(hout, logged_in_user);
    }
    else if (menu_choice == 1) {
        user_authenication::display_resgister_form(hout);
    }
    else if (menu_choice == 2) {
        clear_screen(hout);
        std::cout << "Your choice no: " << menu_choice << std::endl;
    }
    else if(menu_choice == 3) {
        clear_screen(hout);
        std::cout << "Your choice no: " << menu_choice << std::endl;
    }
    else {
        std::cout << "Error: Unexpected Behaviour" << std::endl;
        exit(0);
    }
}

