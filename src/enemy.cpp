#include "enemy.h"
#include "main.h"

Enemy::Enemy(glm::vec3 plane_location, glm::vec3 plane_z) {

    this->position = plane_location + (float)(rand() % 200 - 100) * glm::vec3(1.0f, 0.0f, 0.0f) + plane_z * (50.0f);
    this->position[1] = 20.0f;
    this->y_speed = 0.025;
    this->rotation = 0;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
	/*  GLfloat enemy_box[] = {
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, -1.0f,
		0.0f, -2.0f, 0.0f,

		1.0f, 0.0f, -1.0f,
		-1.0f, 0.0f, -1.0f,
		0.0f, -2.0f, 0.0f,

		-1.0f, 0.0f, -1.0f,
		-1.0f, 0.0f, 1.0f,
		0.0f, -2.0f, 0.0f,

		-1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		0.0f, -2.0f, 0.0f,
	};*/

	GLfloat polygon_a[100000];
	GLfloat polygon_b[100000];
	int count = 0;
	int size = 1;
	int n = 25;
	double degrees = 360 / n;
	for (int i = 0; i <= 4*n ; ++i)
	{
		polygon_a[count++] = 0.0f;
		polygon_a[count++] = 0.35;
		polygon_a[count++] = 0.0f;

		polygon_a[count++] = size * (double)cos(i*degrees*M_PI/180);
		polygon_a[count++] = 0.0f;
		polygon_a[count++] = size * (double)sin(i*degrees*M_PI/180);

		polygon_a[count++] = size * (double)cos((i+1)*degrees*M_PI/180);
		polygon_a[count++] = 0.0f;
		polygon_a[count++] = size * (double)sin((i+1)*degrees*M_PI/180);
	}

	count = 0;

	for (int i = 0; i <= 4*n ; ++i)
	{
		polygon_b[count++] = 0.0f;
		polygon_b[count++] = -2.0f;
		polygon_b[count++] = 0.0f;

		polygon_b[count++] = size * (double)cos(i*degrees*M_PI/180);
		polygon_b[count++] = 0.0f;
		polygon_b[count++] = size * (double)sin(i*degrees*M_PI/180);

		polygon_b[count++] = size * (double)cos((i+1)*degrees*M_PI/180);
		polygon_b[count++] = 0.0f;
		polygon_b[count++] = size * (double)sin((i+1)*degrees*M_PI/180);
	}

    this->object_a = create3DObject(GL_TRIANGLES, 12*n, polygon_a, COLOR_ENEMY, GL_FILL);
    this->object_b = create3DObject(GL_TRIANGLES, 12*n, polygon_b, COLOR_VIOLET, GL_FILL);
}

void Enemy::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object_a);
    draw3DObject(this->object_b);
}

void Enemy::tick()
{
    this->position[1] -= this->y_speed;
}