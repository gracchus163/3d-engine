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

	GLuint vbo_base, vbo_low, vbo_high;
	glGenBuffers(1, &vbo_base);
	glGenBuffers(1, &vbo_low);
	glGenBuffers(1, &vbo_high);
	GLuint vbo_base_indices, vbo_low_indices, vbo_high_indices;
	glGenBuffers(1, &vbo_base_indices);
	glGenBuffers(1, &vbo_low_indices);
	glGenBuffers(1, &vbo_high_indices);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_base);
	float* verts;
	unsigned int* indices;
	unsigned int* vert_len;
	unsigned int* indices_len;
	vert_len = malloc(sizeof(unsigned int));
	indices_len = malloc(sizeof(unsigned int));
	load_ply("assets/base.ply", &verts, vert_len, &indices, indices_len);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)**vert_len*6, verts, GL_STATIC_DRAW);
	printf("error: %d\n", glGetError());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_base_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*3*(*indices_len), indices, GL_STATIC_DRAW);
	//free(&verts); free(&indices);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_low);
	load_ply("assets/low_cube.ply", &verts, vert_len, &indices, indices_len);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)**vert_len*6, verts, GL_STATIC_DRAW);
	printf("error: %d\n", glGetError());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_low_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*3*(*indices_len), indices, GL_STATIC_DRAW);
	//free(&verts); free(&indices);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_high);
	load_ply("assets/high_cube.ply", &verts, vert_len, &indices, indices_len);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)**vert_len*6, verts, GL_STATIC_DRAW);
	printf("error: %d\n", glGetError());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_high_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*3*(*indices_len), indices, GL_STATIC_DRAW);
	//free(&verts); free(&indices);

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
	/*if (eye_pos[1] < -0.3f) {
		eye_pos[1] -= moveV[1];
	}*/
	glm_look(eye_pos, dir, up, m_view);
	glm_perspective(glm_rad(90.0f), 800.0f/600.0f, 0.1f, 20.0f, m_proj);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_base);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_base_indices);
	GLint uniform_m_view = glGetUniformLocation(shaderProgram, "m_view");
	glUniformMatrix4fv(uniform_m_view, 1, GL_FALSE, m_view[0]);
	GLint uniform_m_proj = glGetUniformLocation(shaderProgram, "m_proj");
	glUniformMatrix4fv(uniform_m_proj, 1, GL_FALSE, m_proj[0]);
	glm_mat4_identity(m_model);
	GLint uniform_m_model;
	uniform_m_model = glGetUniformLocation(shaderProgram, "m_model");
	glm_translate_y(m_model, -2.0f);
	glUniformMatrix4fv(uniform_m_model, 1, GL_FALSE, m_model[0]);
	GLint coord3dAttrib = glGetAttribLocation(shaderProgram, "coord3d");
	glEnableVertexAttribArray(coord3dAttrib);
	glVertexAttribPointer(coord3dAttrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), 0);
	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
	glDrawElements(GL_TRIANGLES, *indices_len*3, GL_UNSIGNED_INT, 0);

	glm_mat4_identity(m_model);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_low);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_low_indices);
	uniform_m_view = glGetUniformLocation(shaderProgram, "m_view");
	glUniformMatrix4fv(uniform_m_view, 1, GL_FALSE, m_view[0]);
	uniform_m_proj = glGetUniformLocation(shaderProgram, "m_proj");
	glUniformMatrix4fv(uniform_m_proj, 1, GL_FALSE, m_proj[0]);
	glm_mat4_identity(m_model);
	uniform_m_model;
	uniform_m_model = glGetUniformLocation(shaderProgram, "m_model");
	glm_translate_y(m_model, 0.5f);
	glUniformMatrix4fv(uniform_m_model, 1, GL_FALSE, m_model[0]);
	coord3dAttrib = glGetAttribLocation(shaderProgram, "coord3d");
	glEnableVertexAttribArray(coord3dAttrib);
	glVertexAttribPointer(coord3dAttrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), 0);
	colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
	glDrawElements(GL_TRIANGLES, *indices_len*3, GL_UNSIGNED_INT, 0);

	glm_mat4_identity(m_model);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_high);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_high_indices);
	uniform_m_view = glGetUniformLocation(shaderProgram, "m_view");
	glUniformMatrix4fv(uniform_m_view, 1, GL_FALSE, m_view[0]);
	uniform_m_proj = glGetUniformLocation(shaderProgram, "m_proj");
	glUniformMatrix4fv(uniform_m_proj, 1, GL_FALSE, m_proj[0]);
	glm_mat4_identity(m_model);
	uniform_m_model;
	uniform_m_model = glGetUniformLocation(shaderProgram, "m_model");
	glm_translate_y(m_model, 1.5f);
	glm_translate_x(m_model, 4.5f);
	glUniformMatrix4fv(uniform_m_model, 1, GL_FALSE, m_model[0]);
	coord3dAttrib = glGetAttribLocation(shaderProgram, "coord3d");
	glEnableVertexAttribArray(coord3dAttrib);
	glVertexAttribPointer(coord3dAttrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), 0);
	colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
	glDrawElements(GL_TRIANGLES, *indices_len*3, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
		movement();
}
	glfwTerminate();
}
