
const char* vertexSource = "#version 150 core\n\
	in vec3 coord3d;\n\
	in vec3 color;\n\
	out vec3 Color;\n\
	uniform mat4 m_model;\n\
	uniform mat4 m_view;\n\
	uniform mat4 m_proj;\n\
	void main(){\n\
		Color = color;\n\
		gl_Position = m_proj * m_view * m_model * vec4(coord3d, 1.0);}";
const char* fragmentSource = "#version 150 core\n\
	in vec3 Color;\n\
	out vec4 outColor; void main() { outColor = vec4(Color,1.0);}";
