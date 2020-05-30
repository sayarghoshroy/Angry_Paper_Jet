#include "plane.h"
#include "main.h"

Plane::Plane(color_t color)
{
	this->position = glm::vec3(0, 5, 0);
	this->yaw = 0;
	this->pitch = 0;
	this->roll = 0;
	this->y_speed = 0;
	this->x_dir = glm::vec3(1, 0, 0);
	this->y_dir = glm::vec3(0, 1, 0);
	this->z_dir = glm::vec3(0, 0, 1);
	this->speed = 1;
	gravity = 0.1;
	scale = 0.5;

	/*
	static GLfloat plane_coords[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 3.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 3.0f,
		-1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};
	*/

	GLfloat wing_coords[] = {

		0.0f * scale, 0.0f * scale, 7.0f * scale,
		5.0f * scale, 0.0f * scale, -3.0f * scale,
		3.0f * scale, 0.0f * scale, -3.0f * scale,

		0.0f * scale, 0.0f * scale, 7.0f * scale,
		-5.0f * scale, 0.0f * scale, -3.0f * scale,
		-3.0f * scale, 0.0f * scale, -3.0f * scale,

	};

	GLfloat body_coords[] = {

		0.0f * scale, 0.0f * scale, 7.0f * scale,
		-3.0f * scale, 0.0f * scale, -3.0f * scale,
		0.0f * scale, -3.0f * scale, -2.0f * scale,

		0.0f * scale, 0.0f * scale, 7.0f * scale,
		3.0f * scale, 0.0f * scale, -3.0f * scale,
		0.0f * scale, -3.0f * scale, -2.0f * scale,		
	};

	this->object_wing = create3DObject(GL_TRIANGLES, 6, wing_coords, COLOR_PLANE, GL_FILL);
	this->object_body = create3DObject(GL_TRIANGLES, 6, body_coords, COLOR_BODY, GL_FILL);
}


void Plane::draw(glm::mat4 VP)
{
	glm::mat4 rotation;
	rotation[0] = glm::vec4(x_dir, 0);
    rotation[1] = glm::vec4(y_dir, 0);
    rotation[2] = glm::vec4(z_dir, 0);
    rotation[3] = glm::vec4(0, 0, 0, 1);

    glm::mat4 translate = glm::translate(this->position);

    Matrices.model = glm::mat4(1.0f) * (translate * rotation);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object_wing);
    draw3DObject(this->object_body);
}


void Plane::tick()
{
	//y_speed -= gravity;
	//this->position += y_dir * y_speed;

	this->position += (this->z_dir * this->speed);
	if(this->position[1] > 15.0)
		this->position[1] = 15.0;
}

void Plane::turn_Left_Right(int turn)
{
	//turn: +1 : Left, -1 : Right
	//change x and z directions

	turn *= -1;

	if(abs(this->yaw) == 360)
		this->yaw = 0;

	this->yaw += turn;

	//change x
	glm::mat4 x_axis    = glm::rotate((float) (turn * M_PI / 180.0f), y_dir);
	glm::vec4 norm_x = glm::vec4(this->x_dir, 1);
	this->x_dir = glm::vec3(x_axis * norm_x);

	//change z
	glm::mat4 z_axis    = glm::rotate((float) (turn * M_PI / 180.0f), y_dir);
	glm::vec4 norm_z = glm::vec4(this->z_dir, 1);
	this->z_dir = glm::vec3(z_axis * norm_z);
	if(this->position[1] > 15.0)
		this->position[1] = 15.0;
}

void Plane::nose(int nosy)
{
	//nosy : 1 : Nose Up, -1 : Nose Down
	//change y and z directions
	nosy *= -1;

	if(abs(this->pitch) == 360)
		this->pitch = 0;

	this->pitch += nosy;

	//change y
	glm::mat4 y_axis    = glm::rotate((float) (nosy * M_PI / 180.0f), x_dir);
	glm::vec4 norm_y = glm::vec4(this->y_dir, 1);
	this->y_dir = glm::vec3(y_axis * norm_y);

	//change x
	glm::mat4 z_axis    = glm::rotate((float) (nosy * M_PI / 180.0f), x_dir);
	glm::vec4 norm_z = glm::vec4(this->z_dir, 1);
	this->z_dir = glm::vec3(z_axis * norm_z);
	if(this->position[1] > 15.0)
		this->position[1] = 15.0;
}

void Plane::roll_Left_Right(int roll_dir)
{
	if(abs(this->roll) == 360)
		this->roll = 0;

	this->roll += roll_dir;

	//change y
	glm::mat4 y_axis    = glm::rotate((float) (roll_dir * M_PI / 180.0f), z_dir);
	glm::vec4 norm_y = glm::vec4(this->y_dir, 1);
	this->y_dir = glm::vec3(y_axis * norm_y);

	//change x
	glm::mat4 x_axis    = glm::rotate((float) (roll_dir * M_PI / 180.0f), z_dir);
	glm::vec4 norm_x = glm::vec4(this->x_dir, 1);
	this->x_dir = glm::vec3(x_axis * norm_x);
	if(this->position[1] > 15.0)
		this->position[1] = 15.0;
}

void Plane::go_Up_Down(int up)
{
	//up : 1 : Up, -1 : Down
	this->position += (glm::vec3(0.0f, 0.1f, 0.0f) * (float)up);
	if(this->position[1] > 15.0)
		this->position[1] = 15.0;
}

void Plane::toggle_Speed(int raise)
{
	//raise: 1 : Increase speed, -1: Decrease Speed
	this->speed += raise * 0.1;
	if(this->speed >= 2.0f)
		this->speed = 2.0f;

	if(this->speed <= 0.0f)
		this->speed = 0.0f;
}
