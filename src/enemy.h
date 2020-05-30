#include "main.h"

#ifndef ENEMY_H
#define ENEMY_H

class Enemy {
public:
    Enemy() {}
    Enemy(glm::vec3 plane_location, glm::vec3 plane_z);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void tick();
    double y_speed;
    float rotation;
private:
    VAO *object_a;
    VAO *object_b;
};
#endif // BALL_H
