#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <unistd.h>
#include <stdio.h>
#include <cglm/cglm.h>
#include "input.h"
#include "global.h"
#include "object.h"
#include "util.h"

vec3 moveV = {0.0f, 0.0f, 0.0f};
vec3 dir = { 2.6f,  -1.2f, 0.0f};
vec3 rightV = {0.0f, 0.0f, 0.0f};
vec3 up = {0.0f,1.0f,0.0f};
float speed = 0.05f;
int firstMouse = 1;
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 800.0f/2.0f;
float lastY = 600.0f/2.0f;
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
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1 , &vertexSource, NULL);
	glCompileShader(vertexShader);
	GLint status;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	char buffer[512];
	glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
	printf(buffer);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
	glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);
	printf(buffer);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

while(!glfwWindowShouldClose(window)) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	mat4 m_model;
	mat4 m_view; 
	mat4 m_proj;
	vec3 temp = {0.0f, 0.0f, 0.0f};
	vec3 eye_pos = {-2.0f, 1.5f, 0.2f};
	glm_vec3_add(eye_pos, moveV, eye_pos);
	glm_look(eye_pos, dir, up, m_view);
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

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glm_rotate_make(m_model, glm_rad(45), up);
	glUniformMatrix4fv(uniform_m_model, 1, GL_FALSE, m_model[0]);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	mat4 m_base;
	vec3 scale = {6.0f, 1.0f, 9.0f};
	glm_scale_make(m_base, scale);
	glm_translate_y(m_base, -1.0f);
		glUniformMatrix4fv(uniform_m_model, 1, GL_FALSE, m_base[0]);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0,(void*)(3*sizeof(float)));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glfwSwapBuffers(window);
		glfwPollEvents();
}
	glfwTerminate();
}
