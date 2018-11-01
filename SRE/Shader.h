#pragma once

#include <string>
#include "GLEW/include/GL/glew.h"


namespace SRE
{

	class Shader
	{
	public:
		Shader(int _sShaderType, const std::string& _sFilename);
		Shader(const std::string& _sFilename);
		~Shader();

		GLuint GetShaderID() const;


	private:
		std::string GetShaderCode(const std::string& _sFilename) const;
		void CompileShaderCode(const std::string& _sShaderCode) const;
		GLint CreateShader(const std::string& _sFilename);


		GLuint m_ShaderID;
		int m_ShaderType;
	};
}
