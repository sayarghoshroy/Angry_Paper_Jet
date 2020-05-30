#include "suicide.h"
#include "main.h"

Suicide::Suicide(glm::vec3 plane_pos)
{
	this->position = glm::vec3(plane_pos[0] + 400  * ((rand() % 2) * 2 - 1), 15, plane_pos[2] + 400 * ((rand() % 2) * 2 - 1));
	this->rotation = 0;
	this->speed = 0.375;

	size = 5;
	rotation = 0;

	GLfloat polygon[100000];
	int count = 0;
	int n = 25;
	double degrees = 360 / n;
	for (int i = 0; i <= 4*n ; ++i)
	{
		polygon[count++] = 0.0f;
		polygon[count++] = 1.0;
		polygon[count++] = 0.0f;

		polygon[count++] = size * (double)cos(i*degrees*M_PI/180);
		polygon[count++] = 0.0f;
		polygon[count++] = size * (double)sin(i*degrees*M_PI/180);

		polygon[count++] = size * (double)cos((i+1)*degrees*M_PI/180);
		polygon[count++] = 0.0f;
		polygon[count++] = size * (double)sin((i+1)*degrees*M_PI/180);

		polygon[count++] = 0.0f;
		polygon[count++] = -1.0f;
		polygon[count++] = 0.0f;

		polygon[count++] = size * (double)cos(i*degrees*M_PI/180);
		polygon[count++] = 0.0f;
		polygon[count++] = size * (double)sin(i*degrees*M_PI/180);

		polygon[count++] = size * (double)cos((i+1)*degrees*M_PI/180);
		polygon[count++] = 0.0f;
		polygon[count++] = size * (double)sin((i+1)*degrees*M_PI/180);
	}

    this->object = create3DObject(GL_TRIANGLES, 24*n, polygon, COLOR_PLANE, GL_FILL);
}


void Suicide::draw(glm::mat4 VP)
{
	Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}


void Suicide::tick(glm::vec3 plane_pos)
{
	//y_speed -= gravity;
	//this->position += y_dir * y_speed;
	glm::vec3 dir = (plane_pos - this->position);

	this->position += ( (dir / (float)glm::length(dir)) * (float)this->speed);
}

