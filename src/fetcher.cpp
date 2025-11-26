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



int fetch(){
    CURL* curl;
    CURLcode result;

    curl = curl_easy_init();
    if(curl == nullptr) {
        std::cerr << "Failed to initialize CURL" << std::endl;
        return 1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, STOCK_URL.c_str());
    result = curl_easy_perform(curl);
    if(result != CURLE_OK) {
        std::cerr << "CURL request failed: " << curl_easy_strerror(result) << std::endl;
        curl_easy_cleanup(curl);
        return 1;
    }
    std::cout << "CURL request succeeded." << std::endl;
    curl_easy_cleanup(curl);
    return 0;
}




int main()
{
    std::cout << std::setw(4) <<  nlohmann::json::meta() << std::endl;

    fetch();
    return 0;
}
