main : main.c
	cc -o main main.c -lglfw -lGLEW -lGLU -lGL -lm
clean : 
	rm client serve
