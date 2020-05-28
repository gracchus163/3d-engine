main : main.c input.c object.c loadShader.c load_ply.c
	cc -g -o main main.c input.c object.c loadShader.c load_ply.c -lglfw -lGLEW -lGLU -lGL -lm
clean : 
	rm client serve
