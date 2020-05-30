#include "ring.h"
#include "math.h"
#include "main.h"

Ring::Ring(float x, float z)
{
	GLfloat pos_x[64], pos_y[64];
	GLfloat ring_coords[1024];
    
    for(int i = 0; i < 30; ++i)
    {
        pos_x[i] = 3.0f * cos(2 * M_PI * i / 30.0f);
        pos_y[i] = 3.0f * sin(2 * M_PI * i / 30.0f);
    }

    this->position = glm::vec3(x, (float)( rand() % 4 + 8.0f), z);

    for(int i = 0; i < 30; ++i)
    {
       ring_coords[18*i]    = pos_x[i];
       ring_coords[18*i+1]  = pos_y[i];
       ring_coords[18*i+2]  = 0.0f;
       ring_coords[18*i+3]  = pos_x[(i+1) % 30];
       ring_coords[18*i+4]  = pos_y[(i+1) % 30];
       ring_coords[18*i+5]  = 0.0f;
       ring_coords[18*i+6]  = 0.8f  * pos_x[i];
       ring_coords[18*i+7]  = 0.8f  * pos_y[i];
       ring_coords[18*i+8]  = 0.0f;
       ring_coords[18*i+9]  = 0.8f  * pos_x[i];
       ring_coords[18*i+10] = 0.8f  * pos_y[i];
       ring_coords[18*i+11] = 0.0f;
       ring_coords[18*i+12] = pos_x[(i+1) % 30];
       ring_coords[18*i+13] = pos_y[(i+1) % 30];
       ring_coords[18*i+14] = 0.0f;
       ring_coords[18*i+15] = 0.8f  * pos_x[(i+1) % 30];
       ring_coords[18*i+16] = 0.8f  * pos_y[(i+1) % 30];
       ring_coords[18*i+17] = 0.0f;
    }

    this->object = create3DObject(GL_TRIANGLES, 180,  ring_coords, COLOR_GREEN, GL_FILL);
}

void Ring::draw(glm::mat4 VP)
{
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate (this->position);
	Matrices.model *= (translate);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	draw3DObject(this->object);
}