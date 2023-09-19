#define CURL_STATICLIB
#include <curl\curl.h>
#include <iostream>
#include <string>


int main() {
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Установка URL-адреса для отправки SMS через сервис Bytehand
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.bytehand.com/v2/sms/messages");

        // Установка метода POST
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        // Установка заголовков запроса, включая ключ авторизации X-Service-Key
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json;charset=UTF-8");
        headers = curl_slist_append(headers, "X-Service-Key: ");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Указание параметров SMS-сообщения в виде JSON-строки
        std::string postData = R"({
            "sender": "SMS-INFO",
            "receiver": "+7",
            "text": "m"
        })";

        // Установка данных для отправки
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());

        // Выполнение запроса и проверка результата
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "Ошибка при отправке SMS: " << curl_easy_strerror(res) << std::endl;
        }

        // Освобождение ресурсов libcurl
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}
