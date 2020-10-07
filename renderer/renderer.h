#pragma once

#include <string_view>

void error(std::string_view message);

void writeBMP(std::string_view filePath, int width, int height, const char *bufferRgba);

