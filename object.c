	float cube_vertices[6*6*6] = {
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 
     0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 
     0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 
    -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 

    -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 
     0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 
     0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 
    -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 
    -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 

    -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 
    -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 
    -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 
    -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 

     0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
     0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f,

    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
};
	float pyramid_vertices[6*3*6] = {
	2.0f, 2.0f, 2.0f, 0.7f, 0.0f, 0.0f,
	2.5f, 1.0f, 2.5f, 0.7f, 0.0f, 0.0f,
	2.5f, 1.0f, 1.5f, 0.7f, 0.0f, 0.0f,

	2.0f, 2.0f, 2.0f, 0.0f, 0.5f, 0.0f,
	2.5f, 1.0f, 2.5f, 0.0f, 0.5f, 0.0f,
	1.5f, 1.0f, 2.5f, 0.0f, 0.5f, 0.0f,

	2.0f, 2.0f, 2.0f, 0.3f, 0.3f, 1.0f,
	1.5f, 1.0f, 2.5f, 0.3f, 0.3f, 1.0f,
	1.5f, 1.0f, 1.5f, 0.3f, 0.3f, 1.0f,

	2.0f, 2.0f, 2.0f, 0.0f, 1.0f, 0.6f,
	1.5f, 1.0f, 1.5f, 0.0f, 1.0f, 0.6f,
	2.5f, 1.0f, 1.5f, 0.0f, 1.0f, 0.6f,

	1.5f, 1.0f, 1.5f,  0.8f, 0.0f, 0.5f,
	1.5f, 1.0f, 2.5f, 0.8f, 0.0f, 0.5f,
	2.5f, 1.0f, 1.5f, 0.8f, 0.0f, 0.5f,

	2.5f, 1.0f, 2.5f,  0.8f, 0.0f, 0.5f,
	1.5f, 1.0f, 2.5f, 0.8f, 0.0f, 0.5f,
	2.5f, 1.0f, 1.5f, 0.8f, 0.0f, 0.5f,
	};
