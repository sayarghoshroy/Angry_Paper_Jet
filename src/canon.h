#include "main.h"

#ifndef CANON_H
#define CANON_H


class Canon {
public:
    Canon() {}
    Canon(glm::vec3 enemy_location, glm::vec3 plane_location, glm::vec3 plane_z);
    glm::vec3 position;
    glm::vec3 move;
    void draw(glm::mat4 VP);
    void tick();
    float scale;
    double speed;
    float rotation;
private:
    VAO *object;
};

#endif // BALL_H
