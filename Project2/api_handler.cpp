#include "api_handler.h"
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <stdexcept>

using json = nlohmann::json;

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string ApiHandler::fetch_exchange_rates(const std::string& api_key) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        std::string url = "https://v6.exchangerate-api.com/v6/" + api_key + "/latest/USD";
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            throw std::runtime_error("Failed to fetch exchange rates: " + std::string(curl_easy_strerror(res)));
        }
    }

    return readBuffer;
}

std::map<std::string, std::string> ApiHandler::parse_currency_codes(const std::string& json_response) {
    try {
        json j = json::parse(json_response);
        if (j["result"] != "success") {
            throw std::runtime_error("API error: " + j["error-type"].get<std::string>());
        }

        std::map<std::string, std::string> currencies;
        for (auto& [key, value] : j["conversion_rates"].items()) {
            currencies[key] = key; // ћожно добавить полные названи€ валют при наличии
        }
        return currencies;
    }
    catch (const json::exception& e) {
        throw std::runtime_error("JSON parsing error: " + std::string(e.what()));
    }
}

double ApiHandler::get_conversion_rate(const std::string& json_response, const std::string& from, const std::string& to) {
    try {
        json j = json::parse(json_response);
        if (j["result"] != "success") {
            throw std::runtime_error("API error: " + j["error-type"].get<std::string>());
        }

        double from_rate = j["conversion_rates"][from];
        double to_rate = j["conversion_rates"][to];

        if (from_rate == 0) {
            throw std::runtime_error("Invalid source currency rate");
        }

        return to_rate / from_rate;
    }
    catch (const json::exception& e) {
        throw std::runtime_error("JSON parsing error: " + std::string(e.what()));
    }
}