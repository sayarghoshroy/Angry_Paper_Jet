#include "hill.h"
#include "main.h"

Hill::Hill(float x, float z)
{
	this->position = glm::vec3(x, 0.0f, z);

	static const GLfloat hill_coords[] = {
		5.0f, 0.0f, 5.0f,
		5.0f, 0.0f, -5.0f,
		0.0f, 10.0f, 0.0f,

		5.0f, 0.0f, -5.0f,
		-5.0f, 0.0f, -5.0f,
		0.0f, 10.0f, 0.0f,

		-5.0f, 0.0f, -5.0f,
		-5.0f, 0.0f, 5.0f,
		0.0f, 10.0f, 0.0f,

		-5.0f, 0.0f, 5.0f,
		5.0f, 0.0f, 5.0f,
		0.0f, 10.0f, 0.0f,
	};

	this->object = create3DObject(GL_TRIANGLES, 12, hill_coords, COLOR_HILL, GL_FILL);
}

void Hill::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}