#pragma once

#include "gmodel.h"
#include <memory>

struct Sphere
{
    float x, y, z, r;
};

class GRenderer
{
public:
    std::shared_ptr<GModel> model;
    GRenderer(std::shared_ptr<GModel> model)
        : model(model) {}
    void render();

private:
    Sphere boundingSphere();
};
