#pragma once

#include <string_view>
#include <vector>
#include <memory>
#include <iostream>

struct Vertex
{
    Vertex(float x, float y, float z)
        : x(x), y(y), z(z) {}

    float x, y, z;
};
std::ostream &operator<<(std::ostream &os, const Vertex &vertex);

struct Face
{
    Face(size_t v1, size_t v2, size_t v3)
        : v1(v1), v2(v2), v3(v3), vn1(0), vn2(0), vn3(0) {}

    Face(size_t v1, size_t v2, size_t v3, float vn1, float vn2, float vn3)
        : v1(v1), v2(v2), v3(v3), vn1(vn1), vn2(vn2), vn3(vn3) {}

    size_t v1, v2, v3;
    float vn1, vn2, vn3;
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
