#include "main.h"

#ifndef HILL_H
#define HILL_H


class Hill{
public:
    Hill() {}
    Hill(float x, float z);
    glm::vec3 position;
    void draw(glm::mat4 VP);
private:
    VAO *object;
};

#endif