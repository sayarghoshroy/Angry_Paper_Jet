#include "water.h"
#include "main.h"

Water::Water(int code) {
    this->position = glm::vec3(0, 0, 0);
    
    GLfloat water_coords[] = {
      5000.0f, 0.0f, -5000.0f,
      5000.0f, 0.0f , 5000.0f,
      -5000.0f, 0.0f, -5000.0f,

      5000.0f, 0.0f , 5000.0f,
      -5000.0f, 0.0f, 5000.0f,
      -5000.0f, 0.0f, -5000.0f
    };
    
    this->object = create3DObject(GL_TRIANGLES, 6, water_coords, COLOR_SEA, GL_FILL);
}

void Water::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position);
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}