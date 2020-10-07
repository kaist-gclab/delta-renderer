#include <cstdio>
#include "processor.h"

int main()
{
    char *body;
    httpGet("https://www.example.com/", &body);
    printf("%s\n", body);
    return 0;
}
