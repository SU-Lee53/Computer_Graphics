#version 330 core

layout(location = 0) in vec3 in_Position;
uniform vec3 uniformColor;

out vec3 out_Color;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
	gl_Position = projection * view * model * vec4(in_Position, 1.0f);

	out_Color = uniformColor;
}