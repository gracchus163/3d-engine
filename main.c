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
	uniform mat4 m_transform;\n\
	void main(){\n\
		Color = color;\n\
		gl_Position = m_transform * vec4(coord3d, 1.0);}";
const char* fragmentSource = "#version 150 core\n\
	in vec3 Color;\n\
	out vec4 outColor; void main() { outColor = vec4(Color,1.0);}";
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
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
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
	glClear(GL_COLOR_BUFFER_BIT);
	mat4 m_transform;
	glm_mat4_identity(m_transform);

	float move = sinf((float)clock() /CLOCKS_PER_SEC * (2*3.14)/5);
	//float move = 0.5f;
	float angle = (float)clock() / 10000 * 45;
	vec3 axis_z = {0.0f,0.0f,1.0f};
	vec3 move_vec = {move,  0.0f, 0.0f};
	mat4 m_rotate;
	glm_rotate_make(m_rotate, glm_rad(angle), axis_z);
	//glm_mat4_mulv3(m_rotate, move_vec, 1.0f, trans_vec);
	//glm_vec3_rotate_m4(m_rotate, move_vec, trans_vec);
	glm_translate(m_transform, move_vec);
	glm_mat4_mul(m_rotate, m_transform, m_transform);


	GLint uniform_m_transform;
	uniform_m_transform = glGetUniformLocation(shaderProgram, "m_transform");
	glUniformMatrix4fv(uniform_m_transform, 1, GL_FALSE, m_transform[0]);
	GLint coord3dAttrib = glGetAttribLocation(shaderProgram, "coord3d");
	glEnableVertexAttribArray(coord3dAttrib);
	glVertexAttribPointer(coord3dAttrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), 0);
	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));

	//while(!glfwWindowShouldClose(window)) {
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
}
