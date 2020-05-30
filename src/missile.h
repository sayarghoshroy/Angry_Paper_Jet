#include "main.h"

#ifndef MISSILE_H
#define MISSILE_H


class Missile {
public:
    Missile() {}
    Missile(double plane_speed, glm::vec3 plane_location, glm::vec3 plane_z);
    glm::vec3 position;
    glm::vec3 z_move;
    void draw(glm::mat4 VP);
    void tick();
    float scale;
    double y_speed;
    float rotation;
private:
    VAO *object;
};

#endif // BALL_H
