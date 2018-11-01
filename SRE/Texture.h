#pragma once

#include "GLEW/include/GL/glew.h"


namespace SRE
{
	class Texture
	{
	public:
		Texture();
		Texture(const char* fileLoc);

		bool LoadTexture();
		bool LoadTextureA();

		void UseTexture();
		void ClearTexture();

		~Texture();

	private:
		GLuint m_iTextureID;
		int m_iWidth, m_iHeight, m_iBitDepth;

		const char* pcFileLocation;
	};
}
