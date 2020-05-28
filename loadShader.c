#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>

#include "loadShader.h"

void load_shader(GLuint program) {
	FILE *f = fopen("simp.frag", "rb");
	fseek(f,0,SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);

	char *fragstr = malloc(fsize+1);
	fread(fragstr, 1, fsize, f);
	fclose(f);
	fragstr[fsize] = 0;

	FILE *v = fopen("simp.vert", "rb");
	fseek(v,0,SEEK_END);
	long vsize = ftell(v);
	fseek(v, 0, SEEK_SET);

	char *vertstr = malloc(vsize+1);
	fread(vertstr, 1, vsize, v);
	fclose(v);
	vertstr[vsize] = 0;

	const GLchar* vertchars = vertstr;
	const GLchar* fragchars = fragstr;
	
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1 , &vertchars, NULL);
	glCompileShader(vertexShader);
	GLint status;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	char buffer[512];
	glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
	printf(buffer);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragchars, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
	glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);
	printf(buffer);

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
}
