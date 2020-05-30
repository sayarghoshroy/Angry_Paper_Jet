#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL

#ifndef PLANE_H
#define PLANE_H

class Plane
{
public:
	Plane() {}
	Plane(color_t color);

	void draw(glm::mat4 VP);
	void tick();
	void turn_Left_Right(int turn);
	void nose(int nosy);
	void roll_Left_Right(int roll_dir);
	void toggle_Speed(int raise);
	void go_Up_Down(int up);

	glm::vec3 position;
	glm::vec3 x_dir;
	glm::vec3 y_dir;
	glm::vec3 z_dir;
	double yaw;
	double pitch;
	double roll;
	double y_speed;
	float speed;
	double scale;
	double gravity;

private:
	VAO *object_body;
	VAO *object_wing;
};


#endif