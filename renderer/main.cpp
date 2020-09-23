#include <string>

#include <GL/gl.h>
#include <GL/osmesa.h>

#include "renderer.h"

int viewportWidth, viewportHeight;
std::string inputFilePath;
std::string outputFilePath;

void parseArgs(int argc, char *argv[])
{
    if (argc != 5)
    {
        error("parseArgs");
    }

    viewportWidth = std::stoi(argv[1]);
    viewportHeight = std::stoi(argv[2]);
    inputFilePath = std::string(argv[3]);
    outputFilePath = std::string(argv[4]);
}

int main(int argc, char *argv[])
{
    OSMesaContext ctx = OSMesaCreateContextExt(OSMESA_RGBA, 24, 8, 8, NULL);
    if (!ctx)
    {
        error("OSMesaCreateContextExt");
    }

    parseArgs(argc, argv);

    char *buffer = (char *)malloc(viewportWidth * viewportHeight * 4 * sizeof(GLubyte));
    if (!buffer)
    {
        error("buffer");
    }

    if (!OSMesaMakeCurrent(ctx, buffer, GL_UNSIGNED_BYTE, viewportWidth, viewportHeight))
    {
        error("OSMesaMakeCurrent");
    }

    fprintf(stderr, "GL_VERSION %s\n", glGetString(GL_VERSION));

    glFinish();

    writeBMP(outputFilePath.c_str(), viewportWidth, viewportHeight, buffer);

    free(buffer);
    OSMesaDestroyContext(ctx);

    return 0;
}
