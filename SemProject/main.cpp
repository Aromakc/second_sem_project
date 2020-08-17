#include <stdio.h>
#include <iostream>
#include "menu.h"
#include <Windows.h>
#include "basic_functions.h"
#include "sqlite_wrapper.h"
#include "restaurants.h"
#include "user_authentication.h"

unsigned int display_main_menu_and_get_choice(const HANDLE& hout, menu& main_menu);
void process_main_menu_choice(const HANDLE& hout, unsigned int menu_choice);
int main()
{
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    create_screen(hout);
    clear_screen(hout, 0, 8);
    menu* mainMenu = new menu("Resturantey");
    unsigned int option_choice = display_main_menu_and_get_choice(hout, *mainMenu);
    process_main_menu_choice(hout, option_choice);
}

unsigned int display_main_menu_and_get_choice(const HANDLE& hout, menu& main_menu) {
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


void process_main_menu_choice(const HANDLE& hout, unsigned int menu_choice) {
    if (menu_choice == 0) {
        user* logged_in_user = new user();
        user_authenication::user_login_auth(hout, *logged_in_user);
        //std::cout << logged_in_user->get_id();
        logged_in_user->process_home_page_choice(hout, user::display_home_page_and_get_choice(hout));

        
    }
    else if (menu_choice == 1) {
        user_authenication::display_resgister_form(hout);
    }
    else if (menu_choice == 2) {
        restaurants* rest = new restaurants();
        restaurants::search_rest_and(hout, *rest, "-di");
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

