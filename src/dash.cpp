#include "dash.h"
#include "main.h"

Dash::Dash(float percentage, float height, color_t color_name)
{
	this->position = glm::vec3(-1.0f, height, 0.0f);

	percentage = (percentage / 100.0f);

	GLfloat dash_coords[] =
	{	
		0.0f, -0.1f, 0.0f,
		0.0f, 0.1f, 0.0f,
		2.0f * percentage, 0.1f, 0.0f,

		0.0f, -0.1f, 0.0f,
		2.0f * percentage, -0.1f, 0.0f,
		2.0f * percentage, 0.1f, 0.0f,
	};

	this->object = create3DObject(GL_TRIANGLES, 6, dash_coords, color_name, GL_FILL);
}

void Dash::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}