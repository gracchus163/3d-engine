main : main.c
	cc -g -o main main.c -lglfw -lGLEW -lGLU -lGL -lm
clean : 
	rm client serve
