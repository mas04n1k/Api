
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
    std::cout << "=== Конвертер валют ===\n"
        << "1. Конвертировать валюту\n"
        << "2. Показать список валют\n"
        << "3. Показать историю конвертаций\n"
        << "4. Изменить API ключ\n"
        << "5. Выход\n\n";
}

void Menu::display_currency_list(const std::vector<std::string>& currency_codes) {
    std::cout << "=== Доступные валюты ===\n";
    for (size_t i = 0; i < currency_codes.size(); ++i) {
        std::cout << currency_codes[i];
        if ((i + 1) % 5 == 0) std::cout << '\n';
        else std::cout << '\t';
    }
    std::cout << '\n';
}

void Menu::display_conversion_result(double amount, const std::string& from,
    const std::string& to, double result) {
    std::cout << "\nРезультат конвертации:\n"
        << amount << " " << from << " = " << result << " " << to << "\n\n";
}

void Menu::display_history(const std::vector<std::string>& history) {
    std::cout << "=== История конвертаций ===\n";
    if (history.empty()) {
        std::cout << "История пуста\n";
    }
    else {
        for (const auto& entry : history) {
            std::cout << entry << '\n';
        }
    }
    std::cout << '\n';
}

void Menu::display_error(const std::string& message) {
    std::cerr << "Ошибка: " << message << '\n';
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
    std::cout << "Нажмите Enter для продолжения...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}