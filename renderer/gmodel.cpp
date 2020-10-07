#include "gmodel.h"
#include "renderer.h"
#include <string>
#include <sstream>
#include <limits>
#include <charconv>
#include <cassert>

void ObjGModelLoader::statement(std::string_view line)
{
    if (line.size() == 0)
    {
        return;
    }

    std::stringstream s;
    s << line;
    std::string type;
    s >> type;
    if (type == "#")
    {
    }
    else if (type == "v")
    {
        geometricVertex(s);
    }
    else if (type == "f")
    {
        face(s);
    }
    else if (type == "vt")
    {
        // ignored
    }
    else if (type == "mtllib")
    {
        // ignored
    }
    else if (type == "g")
    {
        // ignored
    }
    else if (type == "usemtl")
    {
        // ignored
    }
    else
    {
        error(type);
    }
}

void ObjGModelLoader::geometricVertex(std::istream &s)
{
    std::string sx, sy, sz;
    s >> sx >> sy >> sz;
    float x = stof(sx), y = stof(sy), z = stof(sz);
    model->vertices.emplace_back(x, y, z);
}

static const int nil = std::numeric_limits<int>::max();

std::vector<int> split(std::string_view s)
{
    std::vector<int> result;
    int begin = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (i == s.size() || s[i] == '/')
        {
            auto token = s.substr(begin, i - begin);
            if (token.size() == 0)
            {
                result.push_back(nil);
            }
            else
            {
                int value;
                if (std::from_chars(token.data(), token.data() + token.size(), value).ec != std::errc())
                {
                    error("split");
                }
                result.push_back(value);
            }
            begin = i + 1;
        }
    }
    return result;
}

size_t ObjGModelLoader::getAbsoluteVertexNumber(int number)
{
    if (number > 0)
    {
        return number - 1;
    }
    if (number < 0)
    {
        return model->vertices.size() - number;
    }
    error("getAbsoluteVertexNumber");
    assert(false);
}

void ObjGModelLoader::face(std::istream &s)
{
    std::string s1, s2, s3;
    s >> s1 >> s2 >> s3;
    auto t1 = split(s1);
    auto t2 = split(s2);
    auto t3 = split(s3);
    int size = t1.size();
    if (size != t2.size() || size != t3.size())
    {
        error("face");
    }

    if (size <= 2)
    {
        model->faces.emplace_back(getAbsoluteVertexNumber(t1[0]),
                           getAbsoluteVertexNumber(t2[0]),
                           getAbsoluteVertexNumber(t3[0]));
    }
    else
    {
        error("vn");
    }
}
