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
static std::string inputFilePath;
static std::string outputFilePath;

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

    std::cerr << "GL_VERSION " << glGetString(GL_VERSION) << std::endl;

    auto model = std::make_shared<GModel>();
    auto loader = std::make_shared<ObjGModelLoader>(model);

    std::ifstream modelFile(inputFilePath);
    std::string line;
    while (std::getline(modelFile, line))
    {
        loader->statement(line);
    }
    auto renderer = std::make_shared<GRenderer>(model);
    renderer->render();

    glFinish();

    writeBMP(outputFilePath, viewportWidth, viewportHeight, buffer);

    free(buffer);
    OSMesaDestroyContext(ctx);

    return 0;
}
