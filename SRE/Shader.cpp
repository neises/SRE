#include "Shader.h"
#include <vector>
#include <fstream>
#include "Log.h"
#include <cassert>
#include <assert.h>
#include <memory>
#include "GLEW/include/GL/glew.h"

namespace SRE
{
	using namespace SRE;
	Shader::Shader(int _sShaderType, const std::string& _sFilename)
	{

	}

	Shader::Shader(const std::string& _sFilename)
	{
		m_ShaderID = CreateShader(_sFilename);
		std::string shaderSource = GetShaderCode(_sFilename);

		CompileShaderCode(shaderSource);
	}

	Shader::~Shader()
	{
		glDeleteShader(m_ShaderID);
	}

	GLuint Shader::GetShaderID() const
	{
		return m_ShaderID;
	}

	std::string Shader::GetShaderCode(const std::string& _sFilename) const
	{
		std::ifstream fd(_sFilename.c_str());

		if (fd.fail())
		{
			SRE::Logger::GetLoggerInstance()->L_ERROR("Could not find Shaderfile");
		}

		auto src = std::string(std::istreambuf_iterator<char>(fd), std::istreambuf_iterator<char>());

		return src.c_str();
	}

	void Shader::CompileShaderCode(const std::string& _sShaderCode) const
	{
		GLint result = GL_FALSE;
		int infoLogLength;

		const char* cPointer = _sShaderCode.c_str();
		glShaderSource(m_ShaderID, 1, &cPointer, nullptr);
		glCompileShader(m_ShaderID);

		glGetShaderiv(m_ShaderID, GL_COMPILE_STATUS, &result);

		if (!result)
		{
			glGetShaderiv(m_ShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
			std::unique_ptr<char[]> buffer(new char[infoLogLength]);
			glGetShaderInfoLog(m_ShaderID, infoLogLength, nullptr, buffer.get());
			SRE::Logger::GetLoggerInstance()->L_ERROR(buffer.get());
		}

		//assert(m_glStatus);
	}

	GLint Shader::CreateShader(const std::string& _sFilename)
	{
		// Extract file extension and create the correct shader type
		auto idx = _sFilename.rfind(".");
		auto ext = _sFilename.substr(idx + 1);
		if (ext == "comp") return glCreateShader(GL_COMPUTE_SHADER);
		else if (ext == "frag") return glCreateShader(GL_FRAGMENT_SHADER);
		else if (ext == "geom") return glCreateShader(GL_GEOMETRY_SHADER);
		else if (ext == "tcs")  return glCreateShader(GL_TESS_CONTROL_SHADER);
		else if (ext == "tes")  return glCreateShader(GL_TESS_EVALUATION_SHADER);
		else if (ext == "vert") return glCreateShader(GL_VERTEX_SHADER);
		else return false;
	}

}