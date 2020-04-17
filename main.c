#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <unistd.h>
#include <stdio.h>
#include <cglm/cglm.h>
#include <time.h>

const char* vertexSource = "#version 150 core\n\
	in vec3 coord3d;\n\
	in vec3 color;\n\
	out vec3 Color;\n\
	uniform mat4 m_model;\n\
	uniform mat4 m_view;\n\
	uniform mat4 m_proj;\n\
	void main(){\n\
		Color = color;\n\
		gl_Position = m_proj * m_view * m_model * vec4(coord3d, 1.0);}";
const char* fragmentSource = "#version 150 core\n\
	in vec3 Color;\n\
	out vec4 outColor; void main() { outColor = vec4(Color,1.0);}";
int left_pressed = 0;
int right_pressed = 0;
int space_pressed = 0;
int ctrl_pressed = 0;
float h_v = 0.0f;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
		left_pressed = 1;
		h_v+=0.01f;
	}
	else {
		left_pressed = 0;
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		right_pressed = 1;
		h_v-=0.01f;
	}
	else {
		right_pressed = 0;
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		space_pressed = 1;
	}
	else {
		space_pressed = 0;
	}
	if (key == GLFW_KEY_C && action == GLFW_PRESS) {
		ctrl_pressed = 1;
	}
	else {
		ctrl_pressed = 0;
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
	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glewInit();
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	GLuint vbo;
	glGenBuffers(1, &vbo);
	float vertices[] = {
		0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
		1.0f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f
	};
	float cube_vertices[] = {
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 
     0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 
     0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 
    -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 

    -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 
     0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 
     0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 
    -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 
    -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 

    -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 
    -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 
    -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 
    -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 

     0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
     0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f,

    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
};
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

	float h_accel = 0.0f;
//	float h_v = 0.0f;
	float h_x = -1.5f;
	float z_v = 0.0f;
	float z_z = 0.2f;
	while(!glfwWindowShouldClose(window)) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	mat4 m_model;
	//glm_mat4_identity(m_transform);
	mat4 m_view; //vec3 eye_pos, vec3 center, vec3 up, mat4 dest
	mat4 m_proj;
	vec3 axis_z = {0.0f,0.0f,1.0f};
	h_accel = left_pressed ? 0.01f : h_accel;
	h_accel = right_pressed ? -0.01f : h_accel;
	z_v = space_pressed ? 0.01f : 0;
	z_v = ctrl_pressed ? -0.01f : z_v;
	//h_v += h_accel;
	printf("a %f v %f x %f\n", h_accel, h_v, h_x);
	//vec3 eye_pos = {h_x+=h_v, 1.5f, 0.2f};
	vec3 eye_pos = {h_x+=h_v, 1.5f, z_z+=z_v};
	vec3 center = {0.0f, 0.0f, 0.0f};
	vec3 dir = { 2.6f,  -1.2f, 0.0f};
	//glm_lookat(eye_pos, center, axis_z, m_view);
	glm_look(eye_pos, dir, axis_z, m_view);
	GLint uniform_m_view = glGetUniformLocation(shaderProgram, "m_view");
	glUniformMatrix4fv(uniform_m_view, 1, GL_FALSE, m_view[0]);
	glm_perspective(glm_rad(90.0f), 800.0f/600.0f, 1.0f, 10.0f, m_proj);
	GLint uniform_m_proj = glGetUniformLocation(shaderProgram, "m_proj");
	glUniformMatrix4fv(uniform_m_proj, 1, GL_FALSE, m_proj[0]);
	float move = sinf((float)clock() /CLOCKS_PER_SEC * (2*3.14)/5);
	//float move = 0.5f;
	float angle = (float)clock() / 10000 * 45;
	vec3 move_vec = {move,  0.0f, 0.0f};
	glm_rotate_make(m_model, move*20, axis_z);
	//glm_mat4_mulv3(m_rotate, move_vec, 1.0f, trans_vec);
	//glm_vec3_rotate_m4(m_rotate, move_vec, trans_vec);
	//glm_translate(m_transform, move_vec);
	//glm_mat4_mul(m_rotate, m_transform, m_transform);
	vec4 result = {1.0f, 0.0f, 0.0f, 1.0f};
	//printf("%f, %f, %f\n", result[0], result[1], result[2]);
	glm_mat4_mulv(m_model, result, result);
	//printf("%f, %f, %f\n", result[0], result[1], result[2]);


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

	//while(!glfwWindowShouldClose(window)) {
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glm_rotate_make(m_model, move*50, axis_z);
		glm_mat4_mulv(m_model, result, result);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
}
