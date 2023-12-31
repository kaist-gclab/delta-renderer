#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <cstring>

#include <GL/gl.h>
#include <GL/osmesa.h>

#include "renderer.h"
#include "gmodel.h"
#include "grenderer.h"

static int viewportWidth, viewportHeight;
static float degree;
static int format;
static std::string inputFilePath, outputFilePath;

static void parseArgs(int argc, char *argv[])
{
    if (argc != 7)
    {
        error("parseArgs");
    }

    viewportWidth = std::stoi(argv[1]);
    viewportHeight = std::stoi(argv[2]);
    degree = std::stof(argv[3]);
    auto formatIdentifier = argv[4];
    if (!strcmp(formatIdentifier, "BMP"))
    {
        format = FORMAT_BMP;
    }
    else if (!strcmp(formatIdentifier, "PNG"))
    {
        format = FORMAT_PNG;
    }
    else
    {
        error("formatIdentifier");
    }
    inputFilePath = argv[5];
    outputFilePath = argv[6];
}

static void printVersion()
{
    std::cerr << "GL_VERSION " << glGetString(GL_VERSION) << std::endl;
    std::cerr << "GL_RENDERER " << glGetString(GL_RENDERER) << std::endl;
    std::cerr << "GL_SHADING_LANGUAGE_VERSION " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

int main(int argc, char *argv[])
{
    const int attribs[] = {
        OSMESA_FORMAT, OSMESA_RGBA,
        OSMESA_DEPTH_BITS, 16,
        OSMESA_STENCIL_BITS, 8,
        OSMESA_ACCUM_BITS, 8,
        OSMESA_PROFILE, OSMESA_CORE_PROFILE,
        OSMESA_CONTEXT_MAJOR_VERSION, 3,
        OSMESA_CONTEXT_MINOR_VERSION, 3,
        0, 0};

    OSMesaContext ctx = OSMesaCreateContextAttribs(attribs, nullptr);
    if (!ctx)
    {
        error("OSMesaCreateContextAttribs");
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

    // printVersion();

    auto model = std::make_shared<GModel>();
    auto loader = std::make_shared<StlAsciiGModelLoader>(model);
    auto inputFileStream = std::ifstream(inputFilePath);
    std::string line;
    while (std::getline(inputFileStream, line))
    {
        loader->statement(line);
    }

    glViewport(0, 0, viewportWidth, viewportHeight);

    auto renderer = std::make_shared<GRenderer>(model);
    renderer->render(degree);

    if (format == FORMAT_BMP)
    {
        writeBMP(outputFilePath.c_str(), viewportWidth, viewportHeight, buffer);
    }
    else if (format == FORMAT_PNG)
    {
        writePNG(outputFilePath.c_str(), viewportWidth, viewportHeight, buffer);
    }
    else
    {
        error("format");
    }

    free(buffer);
    OSMesaDestroyContext(ctx);

    return 0;
}
