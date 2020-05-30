#include "main.h"

#ifndef BOMB_H
#define BOMB_H


class Bomb {
public:
    Bomb() {}
    Bomb(double plane_speed, glm::vec3 plane_location, glm::vec3 plane_z);
    glm::vec3 position;
    glm::vec3 z_move;
    void draw(glm::mat4 VP);
    void tick();
    double y_speed;
    float rotation;
private:
    VAO *object;
};

#endif // BALL_H
