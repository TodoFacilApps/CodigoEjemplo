#include <iostream>
#include <string>
#include <curl/curl.h>

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response)
{
    size_t totalSize = size * nmemb;
    response->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

std::string RecolectarDatos(const std::string& tnTelefono, const std::string& tcRazonSocial, const std::string& tcCiNit, double tnMonto, const std::string& tcCorreo, int tnTipoServicio, const std::vector<std::string>& taPedidoDetalle)
{
    try
    {
        std::string lcComerceID = "";
        int lnMoneda = 2;
        std::string lcNroPago = "test-" + std::to_string(rand() % 900000 + 100000);
        std::string lcUrlCallBack = "http://localhost:8000/";
        std::string lcUrlReturn = "http://localhost:8000/";
        std::string lcUrl = "";

        CURL* curl;
        CURLcode res;
        std::string response;

        curl = curl_easy_init();
        if (!curl) {
            return "Failed to initialize cURL.";
        }

        if (tnTipoServicio == 1) {
            lcUrl = "https://serviciostigomoney.pagofacil.com.bo/api/servicio/generarqrv2";
        }
        else if (tnTipoServicio == 2) {
            lcUrl = "https://serviciostigomoney.pagofacil.com.bo/api/servicio/realizarpagotigomoneyv2";
        }

        curl_easy_setopt(curl, CURLOPT_URL, lcUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "");

        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Accept: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            response = "cURL error: " + std::string(curl_easy_strerror(res));
        }
        else {
            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);

            if (response_code == 200) {
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
                res = curl_easy_perform(curl);
            }
            else {
                response = "Error - HTTP response code: " + std::to_string(response_code);
            }
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);

        return response;
    }
    catch (const std::exception& ex)
    {
        return std::string("Exception: ") + ex.what();
    }
}

int main()
{
    std::vector<std::string> taPedidoDetalle = { "Item 1", "Item 2", "Item 3" };
    std::string result = RecolectarDatos("123456789", "My Company", "12345", 1.00, "test@example.com", 1, taPedidoDetalle);
    std::cout << "Response: " << result << std::endl;
    return 0;
}
