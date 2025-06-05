#include <iostream>
#include <fstream>
#include "currency_converter.h"
#include "menu.h"

#include <Windows.h>  // Обязательно с большой буквы W
#include <io.h>
#include <fcntl.h>

// Функция для настройки консоли
void InitConsole() {
    // Установка кодовых страниц
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Настройка буферов для широких символов
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
}
const std::string CONFIG_FILE = "config.txt";


std::string load_api_key() {
    std::ifstream file(CONFIG_FILE);
    std::string api_key;
    if (file.is_open()) {
        std::getline(file, api_key);
        file.close();
    }
    return api_key;
}

void save_api_key(const std::string& api_key) {
    std::ofstream file(CONFIG_FILE);
    if (file.is_open()) {
        file << api_key;
        file.close();
    }
}

int main() {
    std::string api_key = load_api_key();

    if (api_key.empty()) {
        std::cout << "Введите ваш API ключ от ExchangeRate-API: ";
        std::getline(std::cin, api_key);
        save_api_key(api_key);
    }

    CurrencyConverter converter(api_key);
    Menu menu;

    bool running = true;
    while (running) {
        menu.clear_screen();
        menu.display_main_menu();

        std::string choice = menu.get_user_input("Выберите действие: ");

        if (choice == "1") {
            // Конвертация валют
            std::string amount_str = menu.get_user_input("Введите сумму для конвертации: ");
            try {
                double amount = std::stod(amount_str);

                std::string from = menu.get_user_input("Введите код валюты для конвертации (например, USD): ");
                std::string to = menu.get_user_input("Введите код целевой валюты (например, EUR): ");

                try {
                    double result = converter.convert(from, to, amount);
                    converter.add_to_history(from, to, amount, result);
                    menu.display_conversion_result(amount, from, to, result);
                }
                catch (const std::exception& e) {
                    menu.display_error("Ошибка при конвертации: " + std::string(e.what()));
                }
            }
            catch (...) {
                menu.display_error("Неверный формат суммы");
            }
            menu.wait_for_enter();

        }
        else if (choice == "2") {
            // Список валют
            menu.display_currency_list(converter.get_currency_codes());
            menu.wait_for_enter();

        }
        else if (choice == "3") {
            // История конвертаций
            menu.display_history(converter.get_conversion_history());
            menu.wait_for_enter();

        }
        else if (choice == "4") {
            // Изменить API ключ
            api_key = menu.get_user_input("Введите новый API ключ: ");
            converter.set_api_key(api_key);
            save_api_key(api_key);
            std::cout << "API ключ успешно обновлен!\n";
            menu.wait_for_enter();

        }
        else if (choice == "5") {
            // Выход
            running = false;

        }
        else {
            menu.display_error("Неверный выбор. Попробуйте снова.");
            menu.wait_for_enter();
        }
    }

    return 0;
}