#include "grenderer.h"
#include "renderer.h"
#include "util.h"
#include <cmath>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <cstring>

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

void GRenderer::render(float degree)
{
    auto s = boundingSphere();

    int success;
    const size_t infoLogSize = 512;
    char infoLog[infoLogSize];

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // black
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // white
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    auto vertexShaderSource = readShader("shader.vert");
    auto vertexShaderSourcePtr = vertexShaderSource.c_str();
    glShaderSource(vertexShader, 1, &vertexShaderSourcePtr, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, infoLogSize, nullptr, infoLog);
        error(infoLog);
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    auto fragmentShaderSource = readShader("shader.frag");
    auto fragmentShaderSourcePtr = fragmentShaderSource.c_str();
    glShaderSource(fragmentShader, 1, &fragmentShaderSourcePtr, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, infoLogSize, nullptr, infoLog);
        error(infoLog);
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, infoLogSize, nullptr, infoLog);
        error(infoLog);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLint projMatrixLoc = glGetUniformLocation(shaderProgram, "ProjMatrix");
    GLint viewMatrixLoc = glGetUniformLocation(shaderProgram, "ViewMatrix");
    GLint lightPosALoc = glGetUniformLocation(shaderProgram, "LightPosA");
    GLint lightPosBLoc = glGetUniformLocation(shaderProgram, "LightPosB");
    GLint lightPosCLoc = glGetUniformLocation(shaderProgram, "LightPosC");

    GLuint VBO, VAO;
    glGenVertexArrays(2, &VAO);
    glGenBuffers(1, &VBO);

    glUseProgram(shaderProgram);

    float projMatrix[16];
    float viewMatrix[16];

    float distance = s.r * 2;
    float rad = degree * M_PI / 180;
    createLookAt(s.x + sin(rad) * distance, s.y + s.r * 1.5, s.z + cos(rad) * distance, s.x, s.y, s.z, viewMatrix);
    createOrthographic(s.r, -s.r, -s.r, s.r, 0, s.r * 100, projMatrix);

    glUniformMatrix4fv(viewMatrixLoc, 1, false, viewMatrix);
    glUniformMatrix4fv(projMatrixLoc, 1, false, projMatrix);

    // three point lights
    float lightPosA[3] = {s.x + s.r * 2, s.y + s.r * 2, s.z + s.r * 2};
    float lightPosB[3] = {s.x - s.r * 2, s.y - s.r * 2, s.z - s.r * 2};
    float lightPosC[3] = {s.x + s.r * 2, s.y - s.r * 2, s.z - s.r * 2};
    glUniform3fv(lightPosALoc, 1, lightPosA);
    glUniform3fv(lightPosBLoc, 1, lightPosB);
    glUniform3fv(lightPosCLoc, 1, lightPosC);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    GLint positionLoc = 0;
    GLint normalLoc = 1;
    glEnableVertexAttribArray(positionLoc);
    glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
    glEnableVertexAttribArray(normalLoc);
    glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void *)(sizeof(float) * 3));

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    float buf[18] = {};

    for (auto v : model->faces)
    {
        auto v1 = model->vertices[v.v1];
        auto v2 = model->vertices[v.v2];
        auto v3 = model->vertices[v.v3];

        buf[0] = v1.x;
        buf[1] = v1.y;
        buf[2] = v1.z;

        buf[6] = v2.x;
        buf[7] = v2.y;
        buf[8] = v2.z;

        buf[12] = v3.x;
        buf[13] = v3.y;
        buf[14] = v3.z;

        buf[3] = buf[9] = buf[15] = v.vn1;
        buf[4] = buf[10] = buf[16] = v.vn2;
        buf[5] = buf[11] = buf[17] = v.vn3;

        glBufferData(GL_ARRAY_BUFFER, sizeof(buf), buf, GL_STATIC_DRAW);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    glDeleteVertexArrays(2, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

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
    // Jack Ritter 1990
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
