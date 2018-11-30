#version 430 core

in vec3 inPosition;
in vec2 inUv;
in vec3 inNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	//vec3 position = vec3(inPosition.x * cos(inTime), inPosition.y * cos(inTime), inPosition.z);
	gl_Position = projection * view * model * vec4(inPosition, 1.0);
};