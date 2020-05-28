#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "load_ply.h"

float* load_ply(int* vert_len) {
	FILE* fp;
	char * line = NULL;
	size_t len = 0;
	fp = fopen("test.ply", "r");
	//fp = fopen("hand.ply", "r");
	if (!fp) {
		printf("file not found\n");
		exit(-1);
	}
	uint verts = 0;
	float x,y,z,nx,ny,nz,r,g,b,a;
	while (getline(&line, &len, fp) != -1) {
			printf("%s", line);
			char* temp = NULL;
			if(strstr(line, "element vertex")) {
				temp = strpbrk(line, "0123456789");
			}
			if (temp) {
				printf("read verts %s\n", temp);
				verts = (uint)atoi(temp);					
			}
			if (!strcmp("end_header\n", line)) break;
	}
	float* buf = malloc(sizeof(float)*verts*6);
	printf("header %d", verts);
	for (int i = 0; i < verts; i++) {
		getline(&line, &len, fp);
		int n = i*6;
		printf("%s", line);
		char* end;
		buf[0+n] = strtof(line, &end);
		buf[1+n] = strtof(end, &end);
		buf[2+n] = strtof(end, &end);
		buf[3+n] = 1.0f;//strtof(end, &end);
		buf[4+n] = 0.0f;//strtof(end, &end);
		buf[5+n] = 0.0f;//strtof(end, &end);
		printf("load x %f y %f z %f r %f g %f b %f\n",
				buf[0+n], buf[1+n], buf[2+n], buf[3+n], buf[4+n], buf[5+n]);
		//sscanf(line, "%f %f %f", x,y,z);
		//buf[0+n] = x; buf[1+n] = y; buf[2+n];
		//buf[3+n] = 1.0f; buf[4+n] = 0.0f; buf[5+n] = 0.0f;

	
	}
	*vert_len = verts;
	return buf;
}
