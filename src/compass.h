#include "main.h"

#ifndef COMPASS_H
#define COMPASS_H

class Compass {
public:
    Compass() {}
    Compass(int temp);
    float scale;
	glm::vec3 position;
	glm::vec3 x_dir;
	glm::vec3 y_dir;
	glm::vec3 z_dir;  
	void draw(glm::mat4 VP, float rotation);
    void tick(glm::vec3 x, glm::vec3 y, glm::vec3 z, glm::vec3 position);

private:
	VAO *object;
};
#endif