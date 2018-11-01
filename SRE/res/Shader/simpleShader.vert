#version 430 core

in vec3 inPosition;
in vec2 inUv;
in vec3 inNormal;

out vec4 vCol;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float inTime;

void main()
{
	TexCoord = inUv;
	//vec3 position = vec3(inPosition.x * cos(inTime), inPosition.y * cos(inTime), inPosition.z);
	gl_Position = projection * view * model * vec4(inPosition, 1.0);
};