#include "main.h"

#ifndef FUEL_H
#define FUEL_H

class Fuel {
public:
    Fuel() {}
    Fuel(float x, float z);
    glm::vec3 position;
    float scale;
    void draw(glm::mat4 VP);   
private:
    VAO *object;
};

#endif