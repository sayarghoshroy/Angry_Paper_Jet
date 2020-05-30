#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL
#ifndef CHECKPOINT_H
#define CHECKPOINT_H

class Checkpoint{
public:
    Checkpoint() {}
    Checkpoint(float x, float y, int code);
    float scale;
    glm::vec3 position;
    void draw(glm::mat4 VP);
private:
    VAO *object;
    VAO *object_a;
};

#endif