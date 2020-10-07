#include <cstdio>
#include <cstdlib>
#include <string>
#include <string_view>

void writeBMP(std::string_view filePath, int width, int height, const char *bufferRgba)
{
    int fileSize = 54 + 3 * width * height;

    unsigned char bmpFileHeader[14] = {'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0};
    unsigned char bmpInfoHeader[40] = {40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0};
    unsigned char bmpPad[3] = {0, 0, 0};

    bmpFileHeader[2] = (unsigned char)(fileSize);
    bmpFileHeader[3] = (unsigned char)(fileSize >> 8);
    bmpFileHeader[4] = (unsigned char)(fileSize >> 16);
    bmpFileHeader[5] = (unsigned char)(fileSize >> 24);

    bmpInfoHeader[4] = (unsigned char)(width);
    bmpInfoHeader[5] = (unsigned char)(width >> 8);
    bmpInfoHeader[6] = (unsigned char)(width >> 16);
    bmpInfoHeader[7] = (unsigned char)(width >> 24);
    bmpInfoHeader[8] = (unsigned char)(height);
    bmpInfoHeader[9] = (unsigned char)(height >> 8);
    bmpInfoHeader[10] = (unsigned char)(height >> 16);
    bmpInfoHeader[11] = (unsigned char)(height >> 24);

    FILE *file = fopen(std::string(filePath).c_str(), "wb");
    fwrite(bmpFileHeader, 1, 14, file);
    fwrite(bmpInfoHeader, 1, 40, file);

    char *bufferLine = (char *)malloc(width * 3);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            bufferLine[j * 3 + 0] = bufferRgba[width * (height - 1 - i) * 4 + 0];
            bufferLine[j * 3 + 1] = bufferRgba[width * (height - 1 - i) * 4 + 1];
            bufferLine[j * 3 + 2] = bufferRgba[width * (height - 1 - i) * 4 + 2];
        }
        fwrite(bufferLine, 3, width, file);
        fwrite(bmpPad, 1, (4 - (width * 3) % 4) % 4, file);
    }
    free(bufferLine);
    fclose(file);
}
