#include <iostream>
#include <fstream>
#include "currency_converter.h"
#include "menu.h"

#include <Windows.h>  // ��易⥫쭮 � ����让 �㪢� W
#include <io.h>
#include <fcntl.h>

// �㭪�� ��� ����ன�� ���᮫�
void InitConsole() {
    // ��⠭���� ������� ��࠭��
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // ����ன�� ���஢ ��� �ப�� ᨬ�����
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
        std::cout << "������ ��� API ���� �� ExchangeRate-API: ";
        std::getline(std::cin, api_key);
        save_api_key(api_key);
    }

    CurrencyConverter converter(api_key);
    Menu menu;

    bool running = true;
    while (running) {
        menu.clear_screen();
        menu.display_main_menu();

        std::string choice = menu.get_user_input("�롥�� ����⢨�: ");

        if (choice == "1") {
            // ��������� �����
            std::string amount_str = menu.get_user_input("������ �㬬� ��� �������樨: ");
            try {
                double amount = std::stod(amount_str);

                std::string from = menu.get_user_input("������ ��� ������ ��� �������樨 (���ਬ��, USD): ");
                std::string to = menu.get_user_input("������ ��� 楫���� ������ (���ਬ��, EUR): ");

                try {
                    double result = converter.convert(from, to, amount);
                    converter.add_to_history(from, to, amount, result);
                    menu.display_conversion_result(amount, from, to, result);
                }
                catch (const std::exception& e) {
                    menu.display_error("�訡�� �� �������樨: " + std::string(e.what()));
                }
            }
            catch (...) {
                menu.display_error("������ �ଠ� �㬬�");
            }
            menu.wait_for_enter();

        }
        else if (choice == "2") {
            // ���᮪ �����
            menu.display_currency_list(converter.get_currency_codes());
            menu.wait_for_enter();

        }
        else if (choice == "3") {
            // ����� �������権
            menu.display_history(converter.get_conversion_history());
            menu.wait_for_enter();

        }
        else if (choice == "4") {
            // �������� API ����
            api_key = menu.get_user_input("������ ���� API ����: ");
            converter.set_api_key(api_key);
            save_api_key(api_key);
            std::cout << "API ���� �ᯥ譮 ��������!\n";
            menu.wait_for_enter();

        }
        else if (choice == "5") {
            // ��室
            running = false;

        }
        else {
            menu.display_error("������ �롮�. ���஡�� ᭮��.");
            menu.wait_for_enter();
        }
    }

    return 0;
}