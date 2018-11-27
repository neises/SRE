#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace SRE
{
	using namespace SRE;
	Texture::Texture()
	{
		m_iTextureID = 0;
		m_iWidth = 0;
		m_iHeight = 0;
		m_iBitDepth = 0;
		m_pcFileLocation = "";
	}

	Texture::Texture(const char* fileLoc)
	{
		m_iTextureID = 0;
		m_iWidth = 0;
		m_iHeight = 0;
		m_iBitDepth = 0;
		m_pcFileLocation = fileLoc;
	}

	bool Texture::LoadTexture()
	{
		unsigned char *texData = stbi_load(m_pcFileLocation, &m_iWidth, &m_iHeight, &m_iBitDepth, 0);
		if (!texData)
		{
			printf("Failed to find: %s\n", m_pcFileLocation);
			return false;
		}

		glGenTextures(1, &m_iTextureID);
		glBindTexture(GL_TEXTURE_2D, m_iTextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_iWidth, m_iHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(texData);

		return true;
	}

	bool Texture::LoadTextureA()
	{
		unsigned char *texData = stbi_load(m_pcFileLocation, &m_iWidth, &m_iHeight, &m_iBitDepth, 0);
		if (!texData)
		{
			printf("Failed to find: %s\n", m_pcFileLocation);
			return false;
		}

		glGenTextures(1, &m_iTextureID);
		glBindTexture(GL_TEXTURE_2D, m_iTextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_iWidth, m_iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(texData);

		return true;
	}

	void Texture::UseTexture()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_iTextureID);
	}

	void Texture::ClearTexture()
	{
		glDeleteTextures(1, &m_iTextureID);
		m_iTextureID = 0;
		m_iWidth = 0;
		m_iHeight = 0;
		m_iBitDepth = 0;
		m_pcFileLocation = "";
	}


	Texture::~Texture()
	{
		ClearTexture();
	}
}