#include "main.h"
#include "timer.h"
#include "water.h"
#include "plane.h"
#include "checkpoint.h"
#include "bomb.h"
#include "missile.h"
#include "hill.h"
#include "ring.h"
#include "fuel.h"
#include "canon.h"
#include "compass.h"
#include "dash.h"
#include "enemy.h"
#include "arrow.h"
#include "suicide.h"
#include "bits/stdc++.h"
using namespace std;

//using namespace glm;
GLMatrices Matrices;
GLuint	 programID;
GLFWwindow *window;

/**************************
* Custom namable functions *
**************************/

int score = 0;
int hill_count = 1000;
int canons_left = 4;

int fuel = 100;
long int mod_time = 0;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

double x_loc, y_loc, temp_x_loc, temp_y_loc;

int x_eye, y_eye, z_eye;
int x_target, y_target, z_target;
glm::vec3 eye, target, up;
int change = 1, timer = 0, click, click_time = 0, rotation = 0;

int view = 4;
// 0 : top, 1 : tower, 2 : pilot, 3 : heli, 4 : follow

Compass compass;
Plane plane;
Water sea;

int checkpoint_count = 10;
int invalid_checkpoint[16];
Checkpoint checkpoints[16];

Hill hills[2048];

int invalid_bomb[64];
Bomb bombs[64];
int bomb_count = 0;
//Allow upto 50

int invalid_missile[128];
Missile missiles[128];
int missile_count = 0;
//Allow upto 100

int ring_count = 500;
int invalid_ring[512];
Ring rings[512];

int fuel_count = 500;
int taken_fuel[512];
Fuel fuels[512];

int invalid_attack[8192];
Canon canons[8192];
int attacks = 0;

int invalid_enemy[8192];
Enemy enemies[8192];
int enemy_count = 0;

int ufo_time = 0;
int ufo_count = 0;
int invalid_ufo[2048];
Suicide ufos[2048];

int game_over;

Timer t60(1.0 / 60);


void find_cam()
{
    if(view == 3)
    {
        glfwGetCursorPos(window, &x_loc, &y_loc);
        up = plane.y_dir;
        target = plane.position;

        if(click && x_loc != temp_x_loc)
            rotation += (int)((x_loc - temp_x_loc) / abs(x_loc - temp_x_loc));

        glm::vec3 eye_dir = glm::vec3(0, 1, 0);
        glm::mat4 rotate = glm::rotate((float) (rotation * M_PI / 180.0f), eye_dir);
        glm::vec3 rotate_cam = glm::vec3(rotate * glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
        eye = plane.position + plane.y_dir * 3.0f + rotate_cam * 7.0f;

        glm::vec3 unit = eye / glm::length(eye);

        eye = eye + unit * (float) ((screen_zoom > 1) ? (screen_zoom - 1) : (- 1 / screen_zoom));

        if(click_time % 15 == 0)
        {
            temp_x_loc = x_loc;
            temp_y_loc = y_loc;
        }

        click_time = (click_time + 1) % 15;
    }

    else
    {
        up = plane.y_dir;
        target = plane.y_dir * 2.5f + plane.z_dir + plane.position;
        eye = plane.y_dir * 2.5f - plane.z_dir * 7.5f + plane.position;

        if(view == 0)
        {
            eye = plane.position + plane.y_dir * 8.0f;
            target = plane.position;
            up = plane.z_dir;
        }

        else if(view == 1)
        {
            eye = plane.position + glm::vec3(12.0f, 12.0f, 12.0f);
            target = plane.position;
            up = glm::vec3(0.0f, 1.0f, 0.0f);
        }
        else if(view == 2)
        {
            eye = plane.position + plane.z_dir * 6.0f;
            target = plane.position +plane.z_dir * 8.0f;
            up = plane.y_dir;
        }

        else if(view == 4)
        {
        	eye = plane.position + plane.z_dir * (-3.0f) + plane.y_dir * (3.0f);
            target = plane.position;
            up = plane.y_dir;
        }
    }
}

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw()
{
	// clear the color and depth in the frame buffer
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// use the loaded shader program
	// Don't change unless you know what you are doing
	glUseProgram (programID);

	find_cam();

	// Compute Camera matrix (view)
	Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
	// Don't change unless you are sure!!
	// Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

	// Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
	// Don't change unless you are sure!!
	glm::mat4 VP = Matrices.projection * Matrices.view;

	glm::vec3 eye_dash, target_dash, up_dash;

	eye_dash = glm::vec3(0.0f, 0.0f, 1.0f);
	target_dash = glm::vec3(0.0f, 0.0f, 0.0f);
	up_dash = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 VP_dash = Matrices.projection * glm::lookAt(eye_dash, target_dash, up_dash);

	// Send our transformation to the currently bound shader, in the "MVP" uniform
	// For each model you render, since the MVP will be different (at least the M part)
	// Don't change unless you are sure!!
	glm::mat4 MVP;  // MVP = Projection * View * Model

	// Scene render
	sea.draw(VP);
	for(int i = 0; i < checkpoint_count; ++i)
	{
		if(!invalid_checkpoint[i])
		{
			checkpoints[i].draw(VP);
		}
	}

	for(int i = 0; i < hill_count; ++i)
	{
		hills[i].draw(VP);
	}

	for(int i = 0; i < bomb_count; ++i)
	{
		if(!invalid_bomb[i])
			bombs[i].draw(VP);
	}

	for(int i = 0; i < missile_count; ++i)
	{
		if(!invalid_missile[i])
			missiles[i].draw(VP);
	}

	for(int i = 0; i < ring_count; ++i)
	{
		if(!invalid_ring[i])
			rings[i].draw(VP);
	}

	for(int i = 0; i < fuel_count; ++i)
	{
		if(!taken_fuel[i])
			fuels[i].draw(VP);
	}

	for(int i = 0; i < attacks; ++i)
	{
		if(!invalid_attack[i])
			canons[i].draw(VP);
	}

	for(int i = 0; i < enemy_count; ++i)
	{
		if(invalid_enemy[i])
			continue;
		enemies[i].draw(VP);
	}

	glm::vec3 plane_see = glm::vec3(plane.z_dir[0], 0.0f, plane.z_dir[2]);
	float length = sqrt((double) (plane_see[0] * plane_see[0] + plane_see[2] * plane_see[2]));
	float angle = acos(double(plane.z_dir[2] / length));

	if(plane_see[0] < 0)
		angle = - angle + 2 * M_PI;

	if(view == 4)
		compass.draw(VP, angle * (-1.0f));

	Arrow arrow = Arrow(plane.position, plane.z_dir, plane.y_dir);

	for(int i = 0; i < checkpoint_count; ++i)
	{
		if(invalid_checkpoint[i] == 0)
		{
			arrow.draw(checkpoints[i].position, plane.position, VP);
			break;
		}
	}

	for(int i = 0; i < ufo_count; ++i)
	{
		if(!invalid_ufo[i])
			ufos[i].draw(VP);
	}

	plane.draw(VP);

	Dash dash_a = Dash((float)(plane.position[1] / 15.0f * 100.0f), -1.0f, COLOR_RED); //Altitude
	Dash dash_b = Dash((float)(plane.speed / 2.0f * 100), -1.2f, COLOR_VIOLET); //Speed
	Dash dash_c = Dash((float)fuel, -1.4f, COLOR_GREEN); //Fuel

	dash_a.draw(VP_dash);
	dash_b.draw(VP_dash);
	dash_c.draw(VP_dash);
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
	if(button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if(action == GLFW_PRESS) 
		{
			click = 1;
			if(missile_count < 100)
				missiles[missile_count++] = Missile(plane.speed, plane.position, plane.z_dir);
		}
		else if(action == GLFW_RELEASE)
		{
			click = 0;
		}
		return;
	}
	else if(button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if(action == GLFW_PRESS) 
		{
			click = 1;
			if(bomb_count < 50)
				bombs[bomb_count++] = Bomb(plane.speed, plane.position, plane.z_dir);
		}
		else if(action == GLFW_RELEASE)
		{
			click = 0;
		}
		return;
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if(yoffset == 1.0)
		screen_zoom += 0.01;
	else if(yoffset == -1.0)
		screen_zoom -= 0.01;
	if(screen_zoom > 5.0f)
		screen_zoom = 5.0f;
	if(screen_zoom < 0.2f)
		screen_zoom = 0.2f;
}

void tick_input(GLFWwindow *window)
{
    int up  = glfwGetKey(window, GLFW_KEY_UP);
    int down  = glfwGetKey(window, GLFW_KEY_DOWN);

	int left  = glfwGetKey(window, GLFW_KEY_LEFT);
	int right = glfwGetKey(window, GLFW_KEY_RIGHT);

    int q  = glfwGetKey(window, GLFW_KEY_Q);
    int e  = glfwGetKey(window, GLFW_KEY_E);

	int a  = glfwGetKey(window, GLFW_KEY_A);
	int d  = glfwGetKey(window, GLFW_KEY_D);
	int w  = glfwGetKey(window, GLFW_KEY_W);
    int x  = glfwGetKey(window, GLFW_KEY_X);
    int r  = glfwGetKey(window, GLFW_KEY_R);
	int f  = glfwGetKey(window, GLFW_KEY_F);
	
	
	int see_top_view = glfwGetKey(window, GLFW_KEY_U);
	int see_tower_view = glfwGetKey(window, GLFW_KEY_T);
	int see_pilot_view = glfwGetKey(window, GLFW_KEY_P);
	int see_heli_view = glfwGetKey(window, GLFW_KEY_H);
	int see_follow_view = glfwGetKey(window, GLFW_KEY_K);

	glfwSetScrollCallback(window, scroll_callback);

    if(see_top_view)
        view = 0;

    else if(see_tower_view)
        view = 1;

    else if(see_pilot_view)
        view = 2;

	else if(see_heli_view)
        view = 3;

    else if(see_follow_view)
    	view = 4;

    if(q)
        plane.turn_Left_Right(-1);
    else if(e)
        plane.turn_Left_Right(1);

    if(up)
        plane.nose(1);

    else if(down)
        plane.nose(-1);

    if(a)
        plane.roll_Left_Right(-1);

    else if(d)
        plane.roll_Left_Right(1);

    if(w)
        plane.toggle_Speed(1);

    else if(x)
        plane.toggle_Speed(-1);

    if(r)
        plane.go_Up_Down(1);

    else if(f)
        plane.go_Up_Down(-1);
}

void tick_elements() {
	plane.tick();

	if(abs(plane.position[0]) > 3750.0f || abs(plane.position[2]) > 3750.0f )
	{
		printf("You Went Outside the Playzone.\n");
		printf("Mission Failed. Score = %d\n", score);
		game_over = 1;
		return;
	}

	if(plane.position[1] < 0)
	{
		printf("You crashed.\n");
		printf("Mission Failed. Score = %d\n", score);
		game_over = 1;
		return;
	}

	int over_flag = 1;
	for(int i = 0; i < checkpoint_count; ++i)
	{
		if(invalid_checkpoint[i] == 0)
		{
			over_flag = 0;
			break;
		}
	}

	if(over_flag == 1)
	{
		printf("Mission Successful. Congratulations! Score = %d\n", score);
		game_over = 1;
		return;
	}

	compass.tick(plane.x_dir, plane.y_dir, plane.z_dir, plane.position);
	
	for(int i = 0; i < bomb_count; ++i)
	{
		if(invalid_bomb[i])
			continue;
		bombs[i].tick();
		if(bombs[i].position[1] < 0)
			invalid_bomb[i] = 1;

		for(int j = 0; j < checkpoint_count; ++j)
		{
			if(invalid_checkpoint[j])
				continue;
			if(glm::distance(bombs[i].position, checkpoints[j].position) < 9 && bombs[i].position[1] < 0.25)
			{
				score += 500;
				printf("You Destroyed a Checkpoint. Score = %d\n", score);
				invalid_checkpoint[j] = 1;
			}
		}

		for(int j = 0; j < enemy_count; ++j)
		{
			if(invalid_enemy[j])
				continue;
			if(glm::distance(bombs[i].position, enemies[j].position) < 2.0f)
			{
				score += 50;
				printf("You Destroyed a Parachute. Score = %d\n", score);
				invalid_enemy[j] = 1;
				invalid_bomb[i] = 1;
			}
		}

		for(int j = 0; j < ufo_count; ++j)
		{
			if(invalid_ufo[j])
				continue;
			if(glm::distance(bombs[i].position, ufos[j].position) < 7.0f)
			{
				score += 200;
				printf("You Destroyed a UFO. Score = %d\n", score);
				invalid_ufo[j] = 1;
				invalid_bomb[i] = 1;
			}
		}
	}

	for(int i = 0; i < ufo_count; ++i)
	{
		if(invalid_ufo[i] == 1)
			continue;
		ufos[i].tick(plane.position);
		
		if(glm::distance(ufos[i].position, plane.position) < 6.5f)
		{
			score -= 1000;
			printf("A Suicide Bomber rammed into You. Score Decremented by 1000. Score = %d\n", score);
			invalid_ufo[i] = 1;
		}
	}

	for(int i = 0; i < missile_count; ++i)
	{
		if(invalid_missile[i])
			continue;
		missiles[i].tick();
		if(missiles[i].position[1] < 0)
			invalid_missile[i] = 1;

		for(int j = 0; j < checkpoint_count; ++j)
		{
			if(glm::distance(missiles[i].position, checkpoints[j].position) < 9 && missiles[i].position[1] < 0.25)
			{
				score += 500;
				printf("You Destroyed a Checkpoint. Score = %d\n", score);
				invalid_checkpoint[j] = 1;
			}
		}

		for(int j = 0; j < enemy_count; ++j)
		{
			if(invalid_enemy[j])
				continue;
			if(glm::distance(missiles[i].position, enemies[j].position) < 1.75f)
			{
				score += 50;
				printf("You Destroyed a Parachute. Score = %d\n", score);
				invalid_enemy[j] = 1;
				invalid_missile[i] = 1;
			}
		}

		for(int j = 0; j < ufo_count; ++j)
		{
			if(invalid_ufo[j])
				continue;
			if(glm::distance(missiles[i].position, ufos[j].position) < 6.0f)
			{
				score += 200;
				printf("You Destroyed a UFO. Score = %d\n", score);
				invalid_ufo[j] = 1;
				invalid_missile[i] = 1;
			}
		}
	}

	for(int j = 0; j < enemy_count; ++j)
	{
		if(invalid_enemy[j])
			continue;
		if(glm::distance(plane.position, enemies[j].position) < 2.25f)
		{
			score -= 100;
			printf("You hit a Parachute. Score = %d\n", score);
			invalid_enemy[j] = 1;
		}
	}

	for(int i = 0; i < attacks; ++i)
	{
		if(invalid_attack[i])
			continue;
		canons[i].tick();
		if(canons[i].position[1] > 25)
			invalid_attack[i] = 1;

		if(glm::distance(plane.position, canons[i].position) < 0.5)
		{
			score -= 200;
			printf("You were hit by a Canon Ball. Score decremented by 200. Score = %d\n", score);
			invalid_attack[i] = 1;
		}
	}

	for(int i = 0; i < enemy_count; ++i)
	{
		if(invalid_enemy[i])
			continue;
		enemies[i].tick();
		if(enemies[i].position[1] < 0)
			invalid_enemy[i] = 1;
	}

	for(int i = 0; i < hill_count; ++i)
	{
		if( (hills[i].position[2] - plane.position[2]) * (hills[i].position[2] - plane.position[2]) + (hills[i].position[0] - plane.position[0]) * (hills[i].position[0] - plane.position[0]) < 25)
		{
			printf("You went into a No Fly Zone.\n");
			printf("Mission Failed. Score = %d\n", score);
			game_over = 1;
		}
	}

	for(int i = 0; i < ring_count; ++i)
	{
		if(invalid_ring[i])
			continue;
		double calculate =
		(rings[i].position[0] - plane.position[0]) * (rings[i].position[0] - plane.position[0]) +
		(rings[i].position[1] - plane.position[1]) * (rings[i].position[1] - plane.position[1]) +
		(rings[i].position[2] - plane.position[2]) * (rings[i].position[2] - plane.position[2]);
		if(calculate < 4)
		{
			score += 100;
			printf("You went through a Ring. 100 points incremented. Score = %d\n", score);
			invalid_ring[i] = 1;
		}
	}

	for(int i = 0; i < fuel_count; ++i)
	{
		if(taken_fuel[i])
			continue;
		double calculate = glm::distance(fuels[i].position, plane.position);
		if(calculate < 4.5f)
		{
			fuel = 100;
			printf("You just got refueled. Keep Going!\n");
			taken_fuel[i] = 1;
		}
	}

	//attack the plane
	if(mod_time == 60)
	{
		for(int i = 0; i < 4; ++i)
		{
			if(invalid_checkpoint[i])
				continue;
			canons[attacks++] = Canon(checkpoints[i].position, plane.position, plane.z_dir);
		}
	}

	if(mod_time == 60 || mod_time == 120 && enemy_count < 8000)
		enemies[enemy_count++] = Enemy(plane.position, plane.z_dir);

	camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
	/* Objects should be created before any other gl function and shaders */
	// Create the models
	plane = Plane(COLOR_RED);
    sea = Water(1);

    for(int i = 0; i < checkpoint_count; ++i)
    	checkpoints[i] = Checkpoint((float)(rand() % 3000 - 1500), (float) (rand() % 3000 - 1500), 1);

    for(int i = 0; i < hill_count; ++i)
    	hills[i] = Hill((float)(rand() % 5000 - 2500), (float) (rand() % 5000 - 2500));

    for(int i = 0 ; i < ring_count; ++i)
    {
    	rings[i] = Ring((float)((rand() % 5000) - 2500), (float) (rand() % 5000 - 2500));
    }

    for(int i = 0 ; i < fuel_count; ++i)
    {
    	fuels[i] = Fuel((float)((rand() % 4000) - 2000), (float) (rand() % 4000 - 2000));
    }

    compass = Compass(1);

    x_target = y_target = z_target = x_eye = y_eye = z_eye = 0;

	// Create and compile our GLSL program from the shaders
	programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
	// Get a handle for our "MVP" uniform
	Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


	reshapeWindow (window, width, height);

	// Background color of the scene
	glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
	glClearDepth (1.0f);

	glEnable (GL_DEPTH_TEST);
	glDepthFunc (GL_LEQUAL);

	cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
	cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
	cout << "VERSION: " << glGetString(GL_VERSION) << endl;
	cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main()
{
	srand(time(0));
	int width  = 1200;
	int height = 1200;

	window = initGLFW(width, height);

	initGL (window, width, height);

    glfwSetMouseButtonCallback(window, mouse_button_callback);

	/* Draw in loop */
	while (!glfwWindowShouldClose(window)) {
		// Process timers

		if (t60.processTick()) {
			++mod_time;

			if(mod_time == 90)
				--fuel;

			if(mod_time == 180)
			{
				mod_time = 0;
				--fuel;
			}

			++ufo_time;
			if(ufo_time == 1200)
			{
				ufo_time = 0;
				if(ufo_count < 2000)
				{
					ufos[ufo_count++] = Suicide(plane.position);
					printf("Beware. An UFO has just been Spotted.\n");
				}
			}
			// 60 fps
			// OpenGL Draw commands
			draw();
			// Swap Frame Buffer in double buffering
			glfwSwapBuffers(window);

			tick_elements();
			tick_input(window);
			if(game_over == 1)
				return 0;
			if(fuel == 0)
			{
				printf("You ran out of Fuel.\n");
				printf("Mission Failed. Score = %d\n", score);
				game_over = 1;
			}
		}

		// Poll for Keyboard and mouse events
		glfwPollEvents();
	}

	quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
	return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
		   (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
	float top	= screen_center_y + 4 / screen_zoom;
	float bottom = screen_center_y - 4 / screen_zoom;
	float left   = screen_center_x - 4 / screen_zoom;
	float right  = screen_center_x + 4 / screen_zoom;
	Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}