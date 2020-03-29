main : main.c
	cc -o main main.c -lglfw -lGLEW -lGLU -lGL
clean : 
	rm client serve
