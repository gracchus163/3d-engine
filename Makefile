main : main.c input.c util.c object.c
	cc -g -o main main.c input.c util.c object.c -lglfw -lGLEW -lGLU -lGL -lm
clean : 
	rm client serve
