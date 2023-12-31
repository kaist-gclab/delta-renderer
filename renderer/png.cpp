#include <cstdio>
#include <cstring>
#include <png.h>
#include <GL/gl.h>
#include <string>

void writePNG(const char *outputFilePath, int width, int height, const char *bufferRgba)
{
    png_image image;
    memset(&image, 0, sizeof(image));

    image.version = PNG_IMAGE_VERSION;
    image.width = width;
    image.height = height;
    image.format = PNG_FORMAT_RGBA;
    image.warning_or_error = 2; // error

    png_image_write_to_file(&image, outputFilePath, 0, bufferRgba, width * 4 * sizeof(GLubyte), nullptr);
}
