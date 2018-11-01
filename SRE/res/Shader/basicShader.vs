#version 330 core

in vec3 position;
in vec3 color;

out vec3 Color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float inTime;

void main()
{
	position = inTime * position;
    gl_Position = projection * view * model * vec4(position, 1);
    Color = color;
}