#include "currency_converter.h"
#include "api_handler.h"
#include <sstream>
#include <iomanip>

CurrencyConverter::CurrencyConverter(const std::string& api_key) : api_key_(api_key) {}

double CurrencyConverter::convert(const std::string& from, const std::string& to, double amount) {
    std::string rates_data = ApiHandler::fetch_exchange_rates(api_key_);
    double rate = ApiHandler::get_conversion_rate(rates_data, from, to);
    return amount * rate;
}

std::map<std::string, std::string> CurrencyConverter::get_available_currencies() {
    std::string rates_data = ApiHandler::fetch_exchange_rates(api_key_);
    return ApiHandler::parse_currency_codes(rates_data);
}

std::vector<std::string> CurrencyConverter::get_currency_codes() {
    auto currencies = get_available_currencies();
    std::vector<std::string> codes;
    for (const auto& pair : currencies) {
        codes.push_back(pair.first);
    }
    return codes;
}

void CurrencyConverter::add_to_history(const std::string& from, const std::string& to, double amount, double result) {
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2);
    stream << amount << " " << from << " -> " << result << " " << to;
    conversion_history_.push_back(stream.str());
}

std::vector<std::string> CurrencyConverter::get_conversion_history() const {
    return conversion_history_;
}

void CurrencyConverter::set_api_key(const std::string& api_key) {
    api_key_ = api_key;
}

std::string CurrencyConverter::get_api_key() const {
    return api_key_;
}