#pragma once

#include <string_view>

void error(std::string_view message);

int httpGet(const char *url, char **body);
