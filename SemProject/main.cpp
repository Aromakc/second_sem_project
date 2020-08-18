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
    menu* mainMenu = new menu("Resturantey");
    
    unsigned int main_menu_choice;
    while (true) {
        clear_screen(hout, 0, 8);
        main_menu_choice = display_main_menu_and_get_choice(hout, *mainMenu);
        if (main_menu_choice == 3) {
            mainMenu->display_exit_message(hout, "Thank You\n", "Hope you enjoyed our service.");
            break;
        }
        process_main_menu_choice(hout, main_menu_choice);
        
    }
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
    clear_screen(0);
    if (menu_choice == 0) {
        user* logged_in_user = new user();
        user_authenication::user_login_auth(hout, *logged_in_user);
        logged_in_user->display_home_page_and_process_choice(hout);
        logged_in_user->~user();
    }
    else if (menu_choice == 1) {
        user_authenication::display_resgister_form(hout);
    }
    else if (menu_choice == 2) {
        restaurants* rest = new restaurants();
        restaurants::search_rest_and(hout, *rest, "-di");
        rest->~restaurants();
    }
    else {
        std::cout << "Error: Unexpected Behaviour" << std::endl;
        exit(0);
    }
}

