main : main.c input.c object.c loadShader.c
	cc -g -o main main.c input.c object.c loadShader.c -lglfw -lGLEW -lGLU -lGL -lm
clean : 
	rm client serve
