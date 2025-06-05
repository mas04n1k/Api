
#include "menu.h"
#include <iostream>
#include <limits>
#include <cstdlib>

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

void Menu::display_main_menu() {
    std::cout << "=== �������� ����� ===\n"
        << "1. �������஢��� ������\n"
        << "2. �������� ᯨ᮪ �����\n"
        << "3. �������� ����� �������権\n"
        << "4. �������� API ����\n"
        << "5. ��室\n\n";
}

void Menu::display_currency_list(const std::vector<std::string>& currency_codes) {
    std::cout << "=== ����㯭� ������ ===\n";
    for (size_t i = 0; i < currency_codes.size(); ++i) {
        std::cout << currency_codes[i];
        if ((i + 1) % 5 == 0) std::cout << '\n';
        else std::cout << '\t';
    }
    std::cout << '\n';
}

void Menu::display_conversion_result(double amount, const std::string& from,
    const std::string& to, double result) {
    std::cout << "\n������� �������樨:\n"
        << amount << " " << from << " = " << result << " " << to << "\n\n";
}

void Menu::display_history(const std::vector<std::string>& history) {
    std::cout << "=== ����� �������権 ===\n";
    if (history.empty()) {
        std::cout << "����� ����\n";
    }
    else {
        for (const auto& entry : history) {
            std::cout << entry << '\n';
        }
    }
    std::cout << '\n';
}

void Menu::display_error(const std::string& message) {
    std::cerr << "�訡��: " << message << '\n';
}

std::string Menu::get_user_input(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

void Menu::clear_screen() {
    system(CLEAR);
}

void Menu::wait_for_enter() {
    std::cout << "������ Enter ��� �த�������...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}