#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL

#ifndef SUICIDE_H
#define SUICIDE_H

class Suicide
{
public:
	Suicide() {}
	Suicide(glm::vec3 plane_pos);

	void draw(glm::mat4 VP);
	void tick(glm::vec3 plane_pos);
	glm::vec3 position;
	float rotation;
	float speed;
	float size;

private:
	VAO *object;
};


#endif