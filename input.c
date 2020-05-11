#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <stdio.h>
#include <cglm/cglm.h>
#include "global.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	glm_vec3_zero(rightV);
	glm_vec3_crossn(up, dir, rightV);
	vec3 dirN = {dir[0], 0.0f, dir[2]};
	glm_vec3_normalize(dirN);
	glm_vec3_normalize(rightV);
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
	if ((key == GLFW_KEY_W) == GLFW_PRESS) {
		glm_vec3_muladds(dirN, speed, moveV);
	}
	if ((key == GLFW_KEY_S) == GLFW_PRESS) {
		glm_vec3_scale(dirN, speed, dirN);
		glm_vec3_sub(moveV, dirN, moveV);
	}
	if ((key == GLFW_KEY_D) == GLFW_PRESS) {
		glm_vec3_scale(rightV, speed, rightV);
		glm_vec3_sub(moveV, rightV, moveV);
	}
	if ((key == GLFW_KEY_A) == GLFW_PRESS) {
		glm_vec3_scale(rightV, speed, rightV);
		glm_vec3_add(moveV, rightV, moveV);
	}
	if ((key == GLFW_KEY_SPACE) == GLFW_PRESS) {
		moveV[1] += speed;
	}
	if ((key == GLFW_KEY_C) == GLFW_PRESS) {
		moveV[1] -= speed;
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

    dir[0] = cos(glm_rad(yaw)) * cos(glm_rad(pitch));
    dir[1] = sin(glm_rad(pitch));
    dir[2] = sin(glm_rad(yaw)) * cos(glm_rad(pitch));
	printf("%f %f %f\n", dir[0], dir[1], dir[2]);
}
