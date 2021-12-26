#pragma once

#include <string_view>

void error(std::string_view message);

void writeBMP(FILE *out, int width, int height, const char *bufferRgba);
void writePNG(FILE *out, int width, int height, const char *bufferRgba);

const int FORMAT_BMP = 1;
const int FORMAT_PNG = 2;
