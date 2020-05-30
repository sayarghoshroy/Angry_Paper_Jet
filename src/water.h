#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL
#ifndef WATER_H
#define WATER_H


class Water{
public:
    Water() {}
    Water(int code);
    glm::vec3 position;
    void draw(glm::mat4 VP);
private:
    VAO *object;
};

#endif