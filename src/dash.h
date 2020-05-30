#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL
#ifndef DASH_H
#define DASHs_H

class Dash{
public:
    Dash() {}
    Dash(float percentage, float height, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
private:
    VAO *object;
};

#endif