#pragma once

#include <string_view>

void error(std::string_view message);

void writeBMP(FILE *out, int width, int height, const char *bufferRgba);
