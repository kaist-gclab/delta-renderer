#pragma once

#include "gmodel.h"
#include <memory>

class GRenderer
{
public:
    std::shared_ptr<GModel> model;
    GRenderer(std::shared_ptr<GModel> model)
        : model(model) {}
    void render();
};
