#include "main.h"

#ifndef RING_H
#define RING_H

class Ring {
public:
    Ring() {}
    Ring(float x, float z);
    glm::vec3 position;
    void draw(glm::mat4 VP);   
private:
    VAO *object;
};

#endif