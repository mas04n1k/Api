#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>

class Menu {
public:
    void display_main_menu();
    void display_currency_list(const std::vector<std::string>& currency_codes);
    void display_conversion_result(double amount, const std::string& from,
        const std::string& to, double result);
    void display_history(const std::vector<std::string>& history);
    void display_error(const std::string& message);
    std::string get_user_input(const std::string& prompt);
    void clear_screen();
    void wait_for_enter();
};

#endif // MENU_H