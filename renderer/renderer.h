#pragma once

#include <string_view>

void error(std::string_view message);

void writeBMP(const char *outputFilePath, int width, int height, const char *bufferRgba);
void writePNG(const char *outputFilePath, int width, int height, const char *bufferRgba);

const int FORMAT_BMP = 1;
const int FORMAT_PNG = 2;
