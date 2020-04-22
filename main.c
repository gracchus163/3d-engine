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
vec3 moveV = {0.0f, 0.0f, 0.0f};
vec3 dir = { 2.6f,  -1.2f, 0.0f};
vec3 rightV = {0.0f, 0.0f, 0.0f};
vec3 axis_z = {0.0f,0.0f,1.0f};
float speed = 0.05f;
int firstMouse = 1;
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 800.0f/2.0f;
float lastY = 600.0f/2.0f;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	glm_vec3_zero(rightV);
	glm_vec3_crossn(axis_z, dir, rightV);
	vec3 dirN = {0.0f, 0.0f, 0.0f};
	glm_vec3_normalize_to(dir, dirN);
	glm_vec3_normalize(rightV);
	printf("%f %f %f\n", dir[0], dir[1], dir[2]);
	printf("%f %f %f\n", dirN[0], dirN[1], dirN[2]);
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
	if ((key == GLFW_KEY_W) == GLFW_PRESS) {
		//moveV[1] += speed;
		glm_vec3_muladds(dirN, speed, moveV);
		//glm_vec3_add(dirN, moveV, moveV);
	}
	if ((key == GLFW_KEY_S) == GLFW_PRESS) {
		//moveV[1] -= speed;
		//glm_vec3_sub(moveV, dir, moveV);
		glm_vec3_scale(dirN, speed, dirN);
		glm_vec3_sub(moveV, dirN, moveV);
	}
	if ((key == GLFW_KEY_A) == GLFW_PRESS) {
		glm_vec3_scale(rightV, speed, rightV);
		glm_vec3_sub(moveV, rightV, moveV);
	}
	if ((key == GLFW_KEY_D) == GLFW_PRESS) {
		glm_vec3_scale(rightV, speed, rightV);
		glm_vec3_add(moveV, rightV, moveV);
	}
	if ((key == GLFW_KEY_SPACE) == GLFW_PRESS) {
		moveV[2] += speed;
	}
	if ((key == GLFW_KEY_C) == GLFW_PRESS) {
		moveV[2] -= speed;
	}
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
  
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    vec3 direction;
    direction[0] = cos(glm_rad(yaw)) * cos(glm_rad(pitch));
    direction[1] = sin(glm_rad(pitch));
    direction[2] = sin(glm_rad(yaw)) * cos(glm_rad(pitch));
	glm_normalize_to(dir, direction);
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

	while(!glfwWindowShouldClose(window)) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	mat4 m_model;
	//glm_mat4_identity(m_transform);
	mat4 m_view; //vec3 eye_pos, vec3 center, vec3 up, mat4 dest
	mat4 m_proj;
	//h_v += h_accel;
	//vec3 eye_pos = {h_x+=h_v, 1.5f, 0.2f};
	vec3 temp = {0.0f, 0.0f, 0.0f};
	vec3 eye_pos = {-2.0f, 1.5f, 0.2f};
	//glm_vec3_cross(dir, moveV, moveV);
	printf("%f %f %f\n", moveV[0], moveV[1], moveV[2]);
	//glm_vec3_crossn(dir, moveV, temp);
	glm_vec3_add(eye_pos, moveV, eye_pos);
	printf("%f %f %f\n", temp[0], temp[1], temp[2]);
	//printf("%f %f %f\n", eye_pos[0], eye_pos[1], eye_pos[2]);
	vec3 center = {0.0f, 0.0f, 0.0f};
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
		glm_rotate_make(m_model, glm_rad(45)+move*20, axis_z);
		glm_mat4_mulv(m_model, result, result);
		glUniformMatrix4fv(uniform_m_model, 1, GL_FALSE, m_model[0]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
}
