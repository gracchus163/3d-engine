#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <unistd.h>
#include <stdio.h>
#include <cglm/cglm.h>
#include "input.h"
#include "global.h"
#include "object.h"
#include "loadShader.h"
#include "load_ply.h"

vec3 moveV = {0.0f, 0.0f, 0.0f};
vec3 prev_moveV = {0.0f, 0.0f, 0.0f};
vec3 dir = { 2.6f,  -1.2f, 0.0f};
vec3 rightV = {0.0f, 0.0f, 0.0f};
vec3 up = {0.0f,1.0f,0.0f};
float speed = 0.05f;
int firstMouse = 1;
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 800.0f/2.0f;
float lastY = 600.0f/2.0f;
void movement() {
	glm_vec3_zero(rightV);
	glm_vec3_zero(moveV);
	glm_vec3_crossn(up, dir, rightV);
	vec3 dirN = {dir[0], 0.0f, dir[2]};
	glm_vec3_normalize(dirN);
	glm_vec3_normalize(rightV);

	if (forward) {
		glm_vec3_muladds(dirN, speed, moveV);
	}
	if (backward) {
		glm_vec3_scale(dirN, speed, dirN);
		glm_vec3_sub(moveV, dirN, moveV);
	}
	//watch for double-scaling of direction vector
	if (left) {
		glm_vec3_muladds(rightV, speed, moveV);
	}
	if (right) {
		glm_vec3_scale(rightV, speed, rightV);
		glm_vec3_sub(moveV, rightV, moveV);
	}
	if (jump) {
		moveV[1] += speed;
	}
	if (crouch) {
		moveV[1] -= speed;
	}
}
int main()
{//following https://open.gl/context. installed glfw from pacman
//glew from pacman also. github/recp/cglm for maths library
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glewInit();
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

	GLuint vao_pyramid;
	glGenVertexArrays(1, &vao_pyramid);
	glBindVertexArray(vao_pyramid);
	GLuint vbo_pyramid;
	glGenBuffers(1, &vbo_pyramid);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_pyramid);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(pyramid_vertices), pyramid_vertices, GL_STATIC_DRAW);
	float* verts;
	float* indices;
	int* vert_len;
	int* indices_len;
	vert_len = malloc(sizeof(int));
	indices_len = malloc(sizeof(int));
	verts = load_ply(vert_len);
	printf("mainverts %d %f %f %f %f %f %f\n", *vert_len, verts[0], verts[1], verts[2], verts[3], verts[4], verts[5]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)**vert_len*6, verts, GL_STATIC_DRAW);
	printf("error: %d\n", glGetError());
	for(int i = 0; i < *vert_len; i++) {
		int n = i * 6;
		printf("x %f y %f z %f r %f g %f b %f\n",
				verts[0+n], verts[1+n], verts[2+n], verts[3+n], verts[4+n], verts[5+n]);
	}
	GLuint shaderProgram = glCreateProgram();
	load_shader(shaderProgram);
	glUseProgram(shaderProgram);

	vec3 eye_pos = {-2.0f, 1.5f, 0.2f};
while(!glfwWindowShouldClose(window)) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	mat4 m_model;
	mat4 m_view; 
	mat4 m_proj;

	glm_vec3_add(eye_pos, moveV, eye_pos);
	if (eye_pos[1] < -0.3f) {
		eye_pos[1] -= moveV[1];
	}
	glm_look(eye_pos, dir, up, m_view);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	GLint uniform_m_view = glGetUniformLocation(shaderProgram, "m_view");
	glUniformMatrix4fv(uniform_m_view, 1, GL_FALSE, m_view[0]);
	glm_perspective(glm_rad(90.0f), 800.0f/600.0f, 0.1f, 10.0f, m_proj);
	GLint uniform_m_proj = glGetUniformLocation(shaderProgram, "m_proj");
	glUniformMatrix4fv(uniform_m_proj, 1, GL_FALSE, m_proj[0]);
	glm_mat4_identity(m_model);

	GLint uniform_m_model;
	uniform_m_model = glGetUniformLocation(shaderProgram, "m_model");
	glUniformMatrix4fv(uniform_m_model, 1, GL_FALSE, m_model[0]);
	GLint coord3dAttrib = glGetAttribLocation(shaderProgram, "coord3d");
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(coord3dAttrib);
	glVertexAttribPointer(coord3dAttrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), 0);
	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));

	//glDrawArrays(GL_TRIANGLES, 0, 36);
	glm_rotate_make(m_model, glm_rad(45), up);
	glUniformMatrix4fv(uniform_m_model, 1, GL_FALSE, m_model[0]);
	//glDrawArrays(GL_TRIANGLES, 0, 36);

	mat4 m_base;
	vec3 scale = {6.0f, 1.0f, 9.0f};
	glm_scale_make(m_base, scale);
	glm_translate_y(m_base, -1.0f);
		glUniformMatrix4fv(uniform_m_model, 1, GL_FALSE, m_base[0]);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0,(void*)(3*sizeof(float)));
		//glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_pyramid);
	glEnableVertexAttribArray(coord3dAttrib);
	glEnableVertexAttribArray(colAttrib);
	glm_mat4_identity(m_base);
	glUniformMatrix4fv(uniform_m_model, 1, GL_FALSE, m_base[0]);
	glUniformMatrix4fv(uniform_m_view, 1, GL_FALSE, m_view[0]);
	glUniformMatrix4fv(uniform_m_proj, 1, GL_FALSE, m_proj[0]);
	glVertexAttribPointer(coord3dAttrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), 0);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
	//glDrawArrays(GL_TRIANGLES, 0, 6*3);
	glDrawArrays(GL_TRIANGLES, 0, *vert_len);
	printf("error: %d\n", glGetError());
		glfwSwapBuffers(window);
		glfwPollEvents();
		movement();
}
	glfwTerminate();
}
