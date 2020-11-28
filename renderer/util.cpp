#include <cmath>
#include <cstring>
#include "util.h"

static void cross(const float a[3], const float b[3], float result[3])
{
    result[0] = a[1] * b[2] - b[1] * a[2];
    result[1] = a[2] * b[0] - b[2] * a[0];
    result[2] = a[0] * b[1] - b[0] * a[1];
}

static void normalize(float vect[3])
{
    float length = sqrt(vect[0] * vect[0] + vect[1] * vect[1] + vect[2] * vect[2]);

    vect[0] /= length;
    vect[1] /= length;
    vect[2] /= length;
}

static void createIdentity(float mat[16])
{
    for (int i = 0; i < 16; i++)
    {
        mat[i] = 0;
    }

    for (int i = 0; i < 4; i++)
    {
        mat[i * 4 + i] = 1;
    }
}

static void multiply(float a[16], const float b[16])
{
    float result[16];

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            result[j * 4 + i] = 0;
            for (int k = 0; k < 4; k++)
            {
                result[j * 4 + i] += a[k * 4 + i] * b[j * 4 + k];
            }
        }
    }

    for (int i = 0; i < 16; i++)
    {
        a[i] = result[i];
    }
}

static void createTranslation(float mat[16], float x, float y, float z)
{
    createIdentity(mat);
    mat[12] = x;
    mat[13] = y;
    mat[14] = z;
}

void createLookAt(float posX, float posY, float posZ,
                  float lookAtX, float lookAtY, float lookAtZ, float mat[16])
{
    float dir[3], right[3], up[3];

    up[0] = 0.0f;
    up[1] = 1.0f;
    up[2] = 0.0f;

    dir[0] = (lookAtX - posX);
    dir[1] = (lookAtY - posY);
    dir[2] = (lookAtZ - posZ);
    normalize(dir);

    cross(dir, up, right);
    normalize(right);

    cross(right, dir, up);
    normalize(up);

    for (int i = 0; i < 16; i++)
    {
        mat[i] = 0;
    }

    mat[0] = right[0];
    mat[4] = right[1];
    mat[8] = right[2];
    mat[1] = up[0];
    mat[5] = up[1];
    mat[9] = up[2];
    mat[2] = -dir[0];
    mat[6] = -dir[1];
    mat[10] = -dir[2];
    mat[15] = 1;

    float translation[16];
    createTranslation(translation, -posX, -posY, -posZ);
    multiply(mat, translation);
}

void createOrthographic(float bottom, float top,
                        float left, float right,
                        float near, float far, float mat[16])
{
    for (int i = 0; i < 16; i++)
    {
        mat[i] = 0;
    }

    mat[0] = 2 / (right - left);
    mat[5] = 2 / (top - bottom);
    mat[10] = -2 / (far - near);
    mat[12] = -(right + left) / (right - left);
    mat[13] = -(top + bottom) / (top - bottom);
    mat[14] = -(far + near) / (far - near);
    mat[15] = 1;
}
