#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL

#ifndef ARROW_H
#define ARROW_H

class Arrow
{
public:
	Arrow() {}
	Arrow(glm::vec3 plane_pos, glm::vec3 plane_z, glm::vec3 plane_y);

	void draw(glm::vec3 check_point_pos, glm::vec3 plane_pos, glm::mat4 VP);

	float scale;
	glm::vec3 position;
	glm::vec3 x_dir;
	glm::vec3 y_dir;
	glm::vec3 z_dir;
	
private:
	VAO *object;
};


#endif