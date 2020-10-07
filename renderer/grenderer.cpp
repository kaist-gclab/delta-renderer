#include "grenderer.h"
#include <cmath>

void GRenderer::render()
{
}

float distSquared(const Vertex &a, const Vertex &b)
{
    auto dx = a.x - b.x;
    auto dy = a.y - b.y;
    auto dz = a.z - b.z;
    return dx * dx + dy * dy + dz * dz;
}

Sphere GRenderer::boundingSphere()
{
    // Jack Ritter
    auto f = model->vertices.front();
    Vertex minX = f, maxX = f, minY = f, maxY = f, minZ = f, maxZ = f;
    for (const auto &v : model->vertices)
    {
        if (minX.x > v.x)
        {
            minX = v;
        }
        if (maxX.x < v.x)
        {
            maxX = v;
        }
        if (minY.y > v.y)
        {
            minY = v;
        }
        if (maxY.y < v.y)
        {
            maxY = v;
        }
        if (minZ.z > v.z)
        {
            minZ = v;
        }
        if (maxZ.z < v.z)
        {
            maxZ = v;
        }
    }

    auto maxDistSquared = distSquared(minX, maxX);
    auto yDistSquared = distSquared(minY, maxY);
    auto zDistSquared = distSquared(minZ, maxZ);
    auto pairA = minX, pairB = maxX;
    if (maxDistSquared < yDistSquared)
    {
        maxDistSquared = yDistSquared;
        pairA = minY;
        pairB = maxY;
    }
    if (maxDistSquared < zDistSquared)
    {
        maxDistSquared = zDistSquared;
        pairA = minZ;
        pairB = maxZ;
    }

    Sphere s;
    s.x = (pairA.x + pairB.x) * 0.5;
    s.y = (pairA.y + pairB.y) * 0.5;
    s.z = (pairA.z + pairB.z) * 0.5;
    s.r = sqrt(distSquared(pairA, pairB)) * 0.5;
    auto rSquared = s.r * s.r;

    for (const auto &v : model->vertices)
    {
        auto dx = v.x - s.x;
        auto dy = v.y - s.y;
        auto dz = v.z - s.z;
        auto nextDistSquared = dx * dx + dy * dy + dz * dz;
        if (rSquared < nextDistSquared)
        {
            auto nextDist = sqrt(nextDistSquared);
            s.r = (s.r + nextDist) * 0.5;
            rSquared = s.r * s.r;
            auto diff = nextDist - s.r;
            s.x = (s.r * s.x + diff * v.x) / nextDist;
            s.y = (s.r * s.y + diff * v.y) / nextDist;
            s.z = (s.r * s.z + diff * v.z) / nextDist;
        }
    }

    return s;
}
