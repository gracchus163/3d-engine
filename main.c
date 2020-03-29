#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <unistd.h>
#include <stdio.h>

const char* vertexSource = "#version 150 core\n\
	in vec2 position;\n\
	in vec3 color;\n\
	out vec3 Color;\n\
	void main(){\n\
		Color = color;\n\
		gl_Position = vec4(position, 0.0, 1.0);}";
const char* fragmentSource = "#version 150 core\n\
	in vec3 Color;\n\
	out vec4 outColor; void main() { outColor = vec4(Color,1.0);}";
int main()
{//following https://open.gl/context. installed glfw from pacman
//glew from pacman also
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
		0.0f, 0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f
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

	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);
	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(2*sizeof(float)));

	while(!glfwWindowShouldClose(window)) {
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
}
