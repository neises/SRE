#version 430 core

//Texture coordinates
in vec2 TexCoord;

// our pixel/fragment color
out vec4 FragColor;
// texture sampler
uniform sampler2D ourTexture;

void main()
{
   FragColor = texture(ourTexture, TexCoord);
   //vec4 c = vec4(Uv.y,Uv.x, 0.0f,1.0f);
   //FragColor = vec4(1.0f,0.0f,0.0f,1.0f);
};