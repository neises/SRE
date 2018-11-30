#version 430 core
 
in vec3 inPosition;			// vertices position
in vec2 inUv;				// texturcoordinates
in vec3 inNormal;			// normales

uniform mat4 model;			// model matrix
uniform mat4 view;			// view matrix
uniform mat4 projection;	// projection matrix

out vec3 FragPos;          
out vec3 Normal;
out vec2 TexCoord;


void main()
{
	// we are now transforming the lightvector into objectspace/modelspace see main.cpp for this
    //FragPos = vec3(model * vec4(inPosition, 1.0f));			// fragment position in world space
    //Normal = mat3(transpose(inverse(model))) * inNormal;	   // normal direction in world space
	FragPos = inPosition;
	Normal = inNormal;

	TexCoord = inUv;

	gl_Position = projection * view *  model * vec4(inPosition, 1.0f);
}