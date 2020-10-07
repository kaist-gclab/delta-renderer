#include <cstdlib>
#include <memory.h>
#include <curl/curl.h>
#include "processor.h"

struct MemoryStruct
{
    char *memory;
    size_t size;
};

static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    char *ptr = (char *)realloc(mem->memory, mem->size + realsize + 1);
    if (ptr == NULL)
    {
        error("realloc");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

int httpGet(const char *url, char **body)
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
    CURL *curl = curl_easy_init();
    if (!curl)
    {
        error("curl_easy_init");
    }

    struct MemoryStruct chunk;
    chunk.memory = (char *)malloc(1);
    chunk.size = 0;

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

    curl_easy_setopt(curl, CURLOPT_URL, url);
    if (curl_easy_perform(curl) != CURLE_OK)
    {
        error("curl_easy_perform");
    }

    curl_easy_cleanup(curl);
    curl_global_cleanup();

    *body = chunk.memory;
    return 0;
}
