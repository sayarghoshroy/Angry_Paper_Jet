#include "canon.h"
#include "math.h"
#include "main.h"

Canon::Canon(glm::vec3 enemy_location, glm::vec3 plane_location, glm::vec3 plane_z) {

    this->position = enemy_location;
    this->move = plane_location + plane_z * 3.0f + enemy_location * (-1.0f);
    this->move = this->move * (float)(1 / sqrt( (double)((this->move[0] * this->move[0]) + (this->move[1] * this->move[1]) + (this->move[2] * this->move[2]))));

    this->speed = 0.002;
    this->rotation = 0;
    this->scale = 0.5;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat bomb_box[] = {
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

    this->object = create3DObject(GL_TRIANGLES, 12*3, bomb_box, COLOR_BLACK, GL_FILL);
}

void Canon::draw(glm::mat4 VP) {
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

void Canon::tick()
{
    this->position += this->move * (2.0f);
}