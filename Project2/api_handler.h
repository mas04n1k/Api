#ifndef API_HANDLER_H
#define API_HANDLER_H

#include <string>
#include <map>

class ApiHandler {
public:
    static std::string fetch_exchange_rates(const std::string& api_key);
    static std::map<std::string, std::string> parse_currency_codes(const std::string& json_response);
    static double get_conversion_rate(const std::string& json_response, const std::string& from, const std::string& to);
};

#endif // API_HANDLER_H