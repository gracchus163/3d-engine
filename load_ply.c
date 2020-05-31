#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "load_ply.h"

int load_ply(char* file, float** vert_buf, unsigned int* vert_len, unsigned int** indices_buf, unsigned int* indices_len) {
	FILE* fp;
	char * line = NULL;
	size_t len = 0;
	fp = fopen(file, "r");
	//fp = fopen("hand.ply", "r");
	if (!fp) {
		printf("file not found\n");
		exit(-1);
	}
	uint verts = 0;
	uint indices = 0;
	float x,y,z,nx,ny,nz,r,g,b,a;
	while (getline(&line, &len, fp) != -1) {
			if (!strcmp("end_header\n", line)) break;
			//printf("%s", line);
			char* temp = NULL;
			if(strstr(line, "element vertex")) {
				temp = strpbrk(line, "0123456789");
			}
			if (temp) {
				printf("read verts %s\n", temp);
				verts = (uint)atoi(temp);					
			}
			temp = NULL;
			if(strstr(line, "element face")) {
				temp = strpbrk(line, "0123456789");
			}
			if (temp) {
				printf("read indices %s\n", temp);
				indices = (uint)atoi(temp);					
			}
	}
	*vert_buf = malloc(sizeof(float)*verts*6);
	printf("header %d", verts);
	printf("indices %d", indices);
	for (int i = 0; i < verts; i++) {
		getline(&line, &len, fp);
		int n = i*6;
		printf("%s", line);
		char* end;
		(*vert_buf)[0+n] = strtof(line, &end);
		(*vert_buf)[1+n] = strtof(end, &end);
		(*vert_buf)[2+n] = strtof(end, &end);
		(*vert_buf)[3+n] = (float)(strtoul(end, &end,0))/256.0;
		(*vert_buf)[4+n] = (float)(strtoul(end, &end,0))/256.0;
		(*vert_buf)[5+n] = (float)(strtoul(end, &end,0))/256.0;
		printf("load x %f y %f z %f r %f g %f b %f\n",
				(*vert_buf)[0+n], (*vert_buf)[1+n], (*vert_buf)[2+n], (*vert_buf)[3+n], (*vert_buf)[4+n], (*vert_buf)[5+n]);
		//sscanf(line, "%f %f %f", x,y,z);
		//(*vert_buf)[0+n] = x; (*vert_buf)[1+n] = y; (*vert_buf)[2+n];
		//(*vert_buf)[3+n] = 1.0f; (*vert_buf)[4+n] = 0.0f; (*vert_buf)[5+n] = 0.0f;

	
	}
	*indices_buf = malloc(sizeof(unsigned int)*3*indices);
	for (int i = 0; i < indices; i++) {
		getline(&line, &len, fp);
		int n = i*3;
		char* end;
		printf("index%s", line);
		strtoul(line, &end, 0); //number of verts per face, 3
		(*indices_buf)[0+n] = (unsigned int)strtoul(end, &end, 0);
		(*indices_buf)[1+n] = (unsigned int)strtoul(end, &end, 0);
		(*indices_buf)[2+n] = (unsigned int)strtoul(end, &end, 0);
		printf("indexs %u %u %u\n",
				(*indices_buf)[0+n],
				(*indices_buf)[1+n],
				(*indices_buf)[2+n]);
	}
	*vert_len = verts;
	*indices_len = indices;
	return 0;
}
