#pragma once

#include <string_view>
#include <vector>
#include <memory>

struct Vertex
{
    Vertex(float x, float y, float z)
        : x(x), y(y), z(z) {}

    float x, y, z;
};

struct Face
{
    Face(size_t v1, size_t v2, size_t v3)
        : v1(v1), v2(v2), v3(v3), vn1(-1), vn2(-1), vn3(-1) {}

    Face(size_t v1, size_t v2, size_t v3, size_t vn1, size_t vn2, size_t vn3)
        : v1(v1), v2(v2), v3(v3), vn1(-1), vn2(-1), vn3(-1) {}

    size_t v1, v2, v3;
    size_t vn1, vn2, vn3;
};

struct GModel
{
    std::vector<Vertex> vertices;
    std::vector<Face> faces;
};

class StlAsciiGModelLoader
{
public:
    StlAsciiGModelLoader(std::shared_ptr<GModel> model)
        : model(model) {}

    std::shared_ptr<GModel> model;
    void statement(std::string_view line);

private:
    void vertex(std::istream &s);
    void face(std::istream &s);
    size_t getAbsoluteVertexNumber(int number);
};
