#include "../include/fetcher.h"
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <iomanip>
#include <string>
#include <unordered_map>


const std::string API_KEY{"d4jnhspr01qgcb0ud610d4jnhspr01qgcb0ud61g"};
const std::string BASE_URL{"https://api.weather.gov/alerts"};
const std::string STOCK_URL{"https://finnhub.io/api/v1/quote?symbol=AAPL&token=d4jnhspr01qgcb0ud610d4jnhspr01qgcb0ud61g"};


// Callback function to capture response data
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string fetch(){
    CURL* curl;
    CURLcode result;
    std::string responseData{};

    curl = curl_easy_init();
    if(curl == nullptr) {
        std::cerr << "Failed to initialize CURL" << std::endl;
        return "";
    }

    curl_easy_setopt(curl, CURLOPT_URL, STOCK_URL.c_str());
    // Set the callback function to capture data
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    // Pass the string to store data in
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);
    // Perform the request
    result = curl_easy_perform(curl);
    if(result != CURLE_OK) {
        std::cerr << "CURL request failed: " << curl_easy_strerror(result) << std::endl;
        curl_easy_cleanup(curl);
        return "";
    }
    std::cout << "CURL request succeeded." << std::endl;
    curl_easy_cleanup(curl);
    return responseData;
}

std::unordered_map<std::string, double> parseStockData(const std::string& jsonData) {
    std::unordered_map<std::string, double> stockData;
    try {
        auto json = nlohmann::json::parse(jsonData);
        stockData["current"] = json["c"].get<double>();
        stockData["high"] = json["h"].get<double>();
        stockData["low"] = json["l"].get<double>();
        stockData["open"] = json["o"].get<double>();
        stockData["previousClose"] = json["pc"].get<double>();
    } catch (const std::exception& e) {
        std::cerr << "Error parsing JSON data: " << e.what() << std::endl;
    }
    return stockData;
}



int main()
{
    std::unordered_map<std::string,double> stockData = parseStockData(fetch());
    // Print the parsed data
    std::cout << "\n=== Stock Data ===" << std::endl;
    std::cout << "Current Price: $" << stockData["current"] << std::endl;
    std::cout << "High: $" << stockData["high"] << std::endl;
    std::cout << "Low: $" << stockData["low"] << std::endl;
    std::cout << "Open: $" << stockData["open"] << std::endl;
    std::cout << "Previous Close: $" << stockData["previousClose"] << std::endl;
    return 0;
}
