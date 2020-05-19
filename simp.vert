#version 150 core
in vec3 coord3d;
in vec3 color;
out vec3 Color;
uniform mat4 m_model;
uniform mat4 m_view;
uniform mat4 m_proj;
void main()
{
	Color = color;
	gl_Position = m_proj * m_view * m_model * vec4(coord3d, 1.0);
}
