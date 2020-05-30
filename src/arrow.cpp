#include "arrow.h"
#include "math.h"
#include "main.h"

Arrow::Arrow(glm::vec3 plane_pos, glm::vec3 plane_z, glm::vec3 plane_y)
{
	this->position = plane_pos + plane_z * (6.5f) + plane_y * (-0.2f) ;
	this->x_dir = glm::vec3(1, 0, 0);
	this->y_dir = glm::vec3(0, 1, 0);
	this->z_dir = glm::vec3(0, 0, 1);
	this->scale = 0.8;

	static GLfloat plane_coords[] = {
		1.0f * scale, 0.0f * scale, 0.0f * scale,
		0.0f * scale, 0.0f * scale, 3.0f * scale,
		0.0f * scale, 0.0f * scale, 1.0f * scale,
		0.0f * scale, 0.0f * scale, 3.0f * scale,
		-1.0f * scale, 0.0f * scale, 0.0f * scale, 
		0.0f * scale, 0.0f * scale, 1.0f * scale,
	};

	this->object = create3DObject(GL_TRIANGLES, 6, plane_coords, COLOR_RED, GL_FILL);
}


void Arrow::draw(glm::vec3 check_point_pos, glm::vec3 plane_pos, glm::mat4 VP)
{	
	float mag_x = check_point_pos[0];
	float mag_y = check_point_pos[2];
	float play_x = plane_pos[0];
	float play_y = plane_pos[2];
	
	glm::mat4 rotation;

	double theta;

	if(mag_x != play_x)
    {
	   	theta = atan(abs((mag_y - play_y) / (mag_x - play_x)));
	   	
	   	if(mag_y > play_y && mag_x > play_x) //Quad 1
	   		theta = theta;
    	else if(mag_y > play_y && mag_x < play_x) //Quad 2
	   		theta = 3.14 - theta;

	   	else if(mag_y < play_y && mag_x < play_x) //Quad 3
	   		theta = -3.14 + theta;
    	else //Quad 4
    		theta = -theta;
    }

    else
    {
    	if(mag_y > play_y)
    		theta = 3.14 / 2;
    	else
    		theta = -3.14 / 2;
    }

    theta -= 3.14 / 2;


	rotation[0] = glm::vec4(cos(theta), 0, sin(theta), 0);
    rotation[1] = glm::vec4(0, 1, 0, 0);
    rotation[2] = glm::vec4(-sin(theta), 0, cos(theta), 0);
    rotation[3] = glm::vec4(0, 0, 0, 1);

    glm::mat4 translate = glm::translate(this->position);

    Matrices.model = glm::mat4(1.0f) * (translate * rotation);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    //draw3DObject(this->structure);
}
