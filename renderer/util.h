#pragma once

void createLookAt(float posX, float posY, float posZ,
                  float lookAtX, float lookAtY, float lookAtZ, float mat[16]);

void createOrthographic(float bottom, float top,
                        float left, float right,
                        float near, float far, float mat[16]);