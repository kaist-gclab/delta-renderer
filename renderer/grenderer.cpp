#include "grenderer.h"
#include "renderer.h"
#include <cmath>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/osmesa.h>

std::string readShader(std::string filePath)
{
    std::ifstream f(filePath);
    std::stringstream s;
    s << f.rdbuf();
    return s.str();
}

void GRenderer::render()
{
    auto s = boundingSphere();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(s.x, s.y + s.r + 1, s.z,
              s.x, s.y, s.z,
              0, 0, -1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-s.r, s.r, -s.r, s.r, 0, s.r * 2 + 1);

    GLfloat light_ambient[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_position[] = {s.x * 2, s.y + s.r + 1, s.z, 0.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    GLfloat specular_mat[] = {1, 1, 1, 1};
    GLfloat emission_mat[] = {0, 0, 0, 1};

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_NORMALIZE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for (auto v : model->faces)
    {
        auto v1 = model->vertices[v.v1];
        auto v2 = model->vertices[v.v2];
        auto v3 = model->vertices[v.v3];

        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_mat);
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission_mat);
        glColor3f(0.2, 0.1, 0.1);

        glBegin(GL_TRIANGLES);
        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);
        glVertex3f(v3.x, v3.y, v3.z);
        glEnd();
    }

    glFlush();
    glFinish();
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
