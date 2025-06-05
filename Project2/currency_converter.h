#ifndef CURRENCY_CONVERTER_H
#define CURRENCY_CONVERTER_H

#include <string>
#include <map>
#include <vector>

class CurrencyConverter {
public:
    CurrencyConverter(const std::string& api_key);
    double convert(const std::string& from, const std::string& to, double amount);
    std::map<std::string, std::string> get_available_currencies();
    std::vector<std::string> get_currency_codes();
    void add_to_history(const std::string& from, const std::string& to, double amount, double result);
    std::vector<std::string> get_conversion_history() const;
    void set_api_key(const std::string& api_key);
    std::string get_api_key() const;

private:
    std::string api_key_;
    std::vector<std::string> conversion_history_;
};

#endif // CURRENCY_CONVERTER_H