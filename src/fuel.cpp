#include "fuel.h"
#include "math.h"
#include "main.h"

Fuel::Fuel(float x, float z)
{   
	this->scale = 2.0f;
	this->position = glm::vec3(x, (float)( rand() % 4 + 8.0f), z);
    GLfloat fuel_box[] = {
        -1.0f * scale,-1.0f * scale,-1.0f * scale, // triangle 1 : begin
        -1.0f * scale,-1.0f * scale, 1.0f * scale,
        -1.0f * scale, 1.0f * scale, 1.0f * scale, // triangle 1 : end
        1.0f * scale, 1.0f * scale,-1.0f * scale, // triangle 2 : begin
        -1.0f * scale,-1.0f * scale,-1.0f * scale,
        -1.0f * scale, 1.0f * scale,-1.0f * scale, // triangle 2 : end
        1.0f * scale,-1.0f * scale, 1.0f * scale,
        -1.0f * scale,-1.0f * scale,-1.0f * scale,
        1.0f * scale,-1.0f * scale,-1.0f * scale,
        1.0f * scale, 1.0f * scale,-1.0f * scale,
        1.0f * scale,-1.0f * scale,-1.0f * scale,
        -1.0f * scale,-1.0f * scale,-1.0f * scale,
        -1.0f * scale,-1.0f * scale,-1.0f * scale,
        -1.0f * scale, 1.0f * scale, 1.0f * scale,
        -1.0f * scale, 1.0f * scale,-1.0f * scale,
        1.0f * scale,-1.0f * scale, 1.0f * scale,
        -1.0f * scale,-1.0f * scale, 1.0f * scale,
        -1.0f * scale,-1.0f * scale,-1.0f * scale,
        -1.0f * scale, 1.0f * scale, 1.0f * scale,
        -1.0f * scale,-1.0f * scale, 1.0f * scale,
        1.0f * scale,-1.0f * scale, 1.0f * scale,
        1.0f * scale, 1.0f * scale, 1.0f * scale,
        1.0f * scale,-1.0f * scale,-1.0f * scale,
        1.0f * scale, 1.0f * scale,-1.0f * scale,
        1.0f * scale,-1.0f * scale,-1.0f * scale,
        1.0f * scale, 1.0f * scale, 1.0f * scale,
        1.0f * scale,-1.0f * scale, 1.0f * scale,
        1.0f * scale, 1.0f * scale, 1.0f * scale,
        1.0f * scale, 1.0f * scale,-1.0f * scale,
        -1.0f * scale, 1.0f * scale,-1.0f * scale,
        1.0f * scale, 1.0f * scale, 1.0f * scale,
        -1.0f * scale, 1.0f * scale,-1.0f * scale,
        -1.0f * scale, 1.0f * scale, 1.0f * scale,
        1.0f * scale, 1.0f * scale, 1.0f * scale,
        -1.0f * scale, 1.0f * scale, 1.0f * scale,
        1.0f * scale,-1.0f * scale, 1.0f * scale,
    };

    this->object = create3DObject(GL_TRIANGLES, 36,  fuel_box, COLOR_FUEL, GL_FILL);
}

void Fuel::draw(glm::mat4 VP)
{
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate (this->position);
	Matrices.model *= (translate);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	draw3DObject(this->object);
}