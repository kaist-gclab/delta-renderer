#include "gmodel.h"
#include "renderer.h"
#include <string>
#include <sstream>
#include <limits>
#include <charconv>
#include <cassert>

void StlAsciiGModelLoader::statement(std::string_view line)
{
    if (line.size() == 0)
    {
        return;
    }

    std::stringstream s;
    s << line;
    std::string type;
    s >> type;
    if (type == "facet")
    {
        face(s);
    }
    else if (type == "vertex")
    {
        vertex(s);
    }
}

void StlAsciiGModelLoader::vertex(std::istream &s)
{
    std::string sx, sy, sz;
    s >> sx >> sy >> sz;
    float x = stof(sx), y = stof(sy), z = stof(sz);
    model->vertices.emplace_back(x, y, z);
}

static const int nil = std::numeric_limits<int>::max();

void StlAsciiGModelLoader::face(std::istream &s)
{
    std::string normal, s1, s2, s3;
    s >> normal >> s1 >> s2 >> s3;
    model->faces.emplace_back(model->vertices.size(),
                              model->vertices.size() + 1,
                              model->vertices.size() + 2);
}

std::ostream &operator<<(std::ostream &os, const Vertex &vertex)
{
    os << "(" << vertex.x << ", " << vertex.y << ", " << vertex.z << ")";
    return os;
}
