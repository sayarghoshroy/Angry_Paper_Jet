#include "checkpoint.h"
#include "main.h"

Checkpoint::Checkpoint(float x, float z, int code) {
    this->position = glm::vec3(x, 0, z);
    this->scale = 2.0f;
    
    GLfloat water_coords[] = {
      10.0f, 0.1f, -10.0f,
      10.0f, 0.1f , 10.0f,
      -10.0f, 0.1f, -10.0f,

      10.0f, 0.1f , 10.0f,
      -10.0f, 0.1f, 10.0f,
      -10.0f, 0.1f, -10.0f
    };

    GLfloat building_box[] = {
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
    
    this->object = create3DObject(GL_TRIANGLES, 6, water_coords, COLOR_GREEN, GL_FILL);
    this->object_a = create3DObject(GL_TRIANGLES, 36, building_box, COLOR_BLACK, GL_FILL);
}

void Checkpoint::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position);
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object_a);
}