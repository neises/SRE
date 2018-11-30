#include "ShaderProgram.h"
#include "Shader.h"
#include "glm\gtc\type_ptr.hpp"
#include <memory>
#include "Log.h"


namespace SRE
{
	using namespace SRE;
	typedef std::pair<GLenum, std::wstring> ShaderDefinition;


	ShaderProgram::ShaderProgram(const std::string& _sVertex_file_path, const std::string& _sFragment_file_path)
	{
		Shader vertexShader(_sVertex_file_path);
		Shader fragmentShader(_sFragment_file_path);

		m_ProgramID = glCreateProgram();

		glAttachShader(m_ProgramID, vertexShader.GetShaderID());
		glAttachShader(m_ProgramID, fragmentShader.GetShaderID());

		glLinkProgram(m_ProgramID);


		GLint result = GL_FALSE;
		int infoLogLength;

		// Check the program
		glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &result);
		glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);

		if (infoLogLength > 0)
		{
			std::vector<char> errorMessage(infoLogLength + 1);
			glGetProgramInfoLog(m_ProgramID, infoLogLength, NULL, &errorMessage[0]);

			SRE::Logger::GetLoggerInstance()->L_ERROR(std::string(errorMessage.begin(), errorMessage.end()));
		}

		glDetachShader(m_ProgramID, vertexShader.GetShaderID());
		glDetachShader(m_ProgramID, fragmentShader.GetShaderID());

		m_ModelLoc = glGetUniformLocation(m_ProgramID, "model");
		assert(m_ModelLoc != -1);

		m_ViewLoc = glGetUniformLocation(m_ProgramID, "view");
		assert(m_ViewLoc != -1);

		m_ProjectionLoc = glGetUniformLocation(m_ProgramID, "projection");
		assert(m_ProjectionLoc != -1);

		// Use the shader before setting uniforms!
		Activate();

		// Tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
		glUniform1i(GetUniformLocation("texture0"), 0);
		glUniform1i(GetUniformLocation("texture1"), 1);
		glUniform1i(GetUniformLocation("texture2"), 2);
		glUniform1i(GetUniformLocation("texture3"), 3);

	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(m_ProgramID);
	}

	void ShaderProgram::Activate()
	{
		glUseProgram(m_ProgramID);
	}

	void ShaderProgram::Deactivate()
	{
		glUseProgram(0);
	}


	GLuint ShaderProgram::GetProgram()
	{
		return m_ProgramID;
	}

	void ShaderProgram::Destroy()
	{

	}

	void ShaderProgram::Attach(std::string const &_sFilename)
	{
		Shader shader(_sFilename);

		glAttachShader(m_ProgramID, shader.GetShaderID());

		glDeleteShader(shader.GetShaderID());
	}

	void ShaderProgram::Link()
	{
		GLint result = GL_FALSE;
		int infoLogLength;

		glLinkProgram(m_ProgramID);

		glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &result);

		if (!result)
		{
			glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);
			std::unique_ptr<char[]> buffer(new char[infoLogLength]);
			glGetProgramInfoLog(m_ProgramID, infoLogLength, nullptr, buffer.get());
			SRE::Logger::GetLoggerInstance()->L_ERROR(buffer.get());
		}

		//assert(m_glStatus);

	}

	void ShaderProgram::MakeBasicShader(std::string const &_sVertexFilename, std::string const &_sFragmentFilename)
	{
		Attach(_sVertexFilename);
		Attach(_sFragmentFilename);
		Link();
	}

	GLint ShaderProgram::GetAttrib(const GLchar* _glAttribName)
	{
		GLint retValue = glGetAttribLocation(m_ProgramID, _glAttribName);

		if (retValue == -1)
		{
			std::string tmpString;
			tmpString.append(_glAttribName);
			tmpString.append(" not found in Shader");
			SRE::Logger::GetLoggerInstance()->L_ERROR(tmpString);
		}

		return retValue;
	}

	GLint ShaderProgram::GetUniform(const GLchar* _glUniformName)
	{
		GLint retValue = glGetUniformLocation(m_ProgramID, _glUniformName);

		if (retValue == -1)
		{
			std::string tmpString;
			tmpString.append(_glUniformName);
			tmpString.append(" not found in Shader");
			SRE::Logger::GetLoggerInstance()->L_ERROR(tmpString);
		}

		return retValue;
	}

	GLint ShaderProgram::GetUniformLocation(const std::string& name)
	{
		auto lower_bound = m_UniformLocations.lower_bound(name);

		if (lower_bound != m_UniformLocations.end() && !(m_UniformLocations.key_comp()(name, lower_bound->first)))
		{
			return lower_bound->second;
		}
		else
		{
			GLint uniform = glGetUniformLocation(m_ProgramID, name.c_str());
			m_UniformLocations.insert(lower_bound, { name, uniform });
			return uniform;
		}
	}


	void ShaderProgram::SetModel(const glm::mat4& _model)
	{
		glUniformMatrix4fv(m_ModelLoc, 1, GL_FALSE, glm::value_ptr(_model));
	}

	void ShaderProgram::SetView(const glm::mat4& _view)
	{
		glUniformMatrix4fv(m_ViewLoc, 1, GL_FALSE, glm::value_ptr(_view));
	}

	void ShaderProgram::SetProjection(const glm::mat4& _projection)
	{
		glUniformMatrix4fv(m_ProjectionLoc, 1, GL_FALSE, glm::value_ptr(_projection));
	}

	void ShaderProgram::SetColor(const glm::vec3& _color)
	{
		glUniform3f(m_ObjectColorLoc, _color.x, _color.y, _color.z);
	}

	void ShaderProgram::SetUniform(const GLchar* _glUniformName, float _fValue)
	{
		GLint iUniformLoc = GetUniform(_glUniformName);
		if (iUniformLoc != -1)
		{
			glUniform1f(iUniformLoc, _fValue);
		}
	}

	void ShaderProgram::SetUniform(const GLchar* _glUniformName, glm::vec3 _vPosition)
	{
		GLint iUniformLoc = GetUniformLocation(_glUniformName);
		if (iUniformLoc != -1)
		{
			glUniform3f(iUniformLoc, _vPosition.x, _vPosition.y, _vPosition.z);
		}
	}

	void ShaderProgram::SetUniform(const GLchar* _glUniformName, glm::mat4 _mMatrix)
	{
		GLint iUniformLoc = GetUniform(_glUniformName);
		if (iUniformLoc != -1)
		{
			glUniformMatrix4fv(iUniformLoc, 1, GL_FALSE, glm::value_ptr(_mMatrix));
		}
	}

}