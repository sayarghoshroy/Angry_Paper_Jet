#include "compass.h"
#include "main.h"

Compass::Compass(int drop)
{
	this->x_dir = glm::vec3(1.0f, 0.0f, 0.0f);
    this->y_dir = glm::vec3(0.0f, 1.0f, 0.0f);
    this->z_dir = glm::vec3(0.0f, 0.0f, 1.0f);
    this->scale = 0.035;
    this->position = glm::vec3(1.0f, 1.0f, 1.0f);

    GLfloat compass_coords[] = {
		0.0f * scale, 0.0f * scale, -0.1f * scale,
		0.0f * scale, 3.0f * scale, -0.1f * scale,
		3.0 * cos(4 * M_PI / 3) * scale, 3.0 * sin(4 * M_PI / 3) * scale, -0.1f * scale,

		0.0f * scale, 0.0f * scale, -0.1f * scale,
		0.0f * scale, 3.0f * scale, -0.1f * scale,
		-3.0 *cos(4 * M_PI / 3) * scale, 3.0 * sin(4 * M_PI / 3) * scale, -0.1f * scale,
    };

    this->object = create3DObject(GL_TRIANGLES, 6,  compass_coords, COLOR_VIOLET, GL_FILL);
}

void Compass::draw(glm::mat4 VP, float angle)
{
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 point_screen;
	glm::mat4 point_north;
	glm::mat4 translate = glm::translate (this->position);    // glTranslatef
	glm::vec3 axis = glm::vec3(0.0f, 0.0f, 1.0f);
	point_north = glm::rotate((float) (-1.0f * angle), axis);

	point_screen[0] = glm::vec4(x_dir, 0.0);
	point_screen[1] = glm::vec4(y_dir, 0.0);
    point_screen[2] = glm::vec4(z_dir, 0.0);
	point_screen[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
	Matrices.model *= (translate * point_screen * point_north);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	draw3DObject(this->object);
}

void Compass::tick(glm::vec3 x_dir, glm::vec3 y_dir, glm::vec3 z_dir, glm::vec3 position)
{
	this->x_dir = x_dir;
	this->y_dir = y_dir;
	this->z_dir = z_dir;
	this->position = position + y_dir * 3.1f + z_dir * (-2.0f);
}