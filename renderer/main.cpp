#include <iostream>
#include <string>
#include <fstream>
#include <memory>

#include <GL/gl.h>
#include <GL/osmesa.h>

#include "renderer.h"
#include "gmodel.h"
#include "grenderer.h"

static int viewportWidth, viewportHeight;
static float degree;
static char *format;

static void parseArgs(int argc, char *argv[])
{
    if (argc != 5)
    {
        error("parseArgs");
    }

    viewportWidth = std::stoi(argv[1]);
    viewportHeight = std::stoi(argv[2]);
    degree = std::stof(argv[3]);
    format = argv[4];
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

    std::string line;
    while (std::getline(std::cin, line))
    {
        loader->statement(line);
    }

    glViewport(0, 0, viewportWidth, viewportHeight);

    auto renderer = std::make_shared<GRenderer>(model);
    renderer->render(degree);

    writePNG(stdout, viewportWidth, viewportHeight, buffer);

    free(buffer);
    OSMesaDestroyContext(ctx);

    return 0;
}
