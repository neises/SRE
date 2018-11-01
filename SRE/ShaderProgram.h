#pragma once

#include <unordered_map>
#include "GLEW/include/GL/glew.h"
#include "glm/glm.hpp"

namespace SRE
{
	class ShaderProgram
	{
	public:
		ShaderProgram(const std::string& _sVertex_file_path, const std::string& _sFragment_file_path);
		~ShaderProgram();

		void Activate();
		void Deactivate();
		GLuint GetProgram();

		void Destroy();

		void Attach(std::string const &_sFilename);

		void Link();

		void MakeBasicShader(std::string const &_sVertexFilename, std::string const &_sFragmentFilename);

		GLint GetAttrib(const GLchar* _glAttribName);
		GLint GetUniform(const GLchar* _glUniformName);

		GLint GetUniformLocation(const std::string& name);

		void UpdateProjectionMatrix(glm::mat4 _mProjectionMatrix);

		void UpdateViewMatrix(glm::mat4 _mViewMatrix);

		void SetModel(const glm::mat4& _model);
		void SetView(const glm::mat4& _view);
		void SetProjection(const glm::mat4& _projection);
		void SetColor(const glm::vec3& _color);

		void SetUniform(const GLchar* _glUniformName, float _fValue);
		void SetUniform(const GLchar* _glUniformName, glm::vec3 _vPosition);
		void SetUniform(const GLchar* _glUniformName, glm::mat4 _mMatrix);

	private:
		//ShaderProgram(ShaderProgram const&) = delete;
		//ShaderProgram & operator =(ShaderProgram const&) = delete;


		GLuint	m_ProgramID;
		GLuint	m_ShaderID;
		GLint	m_Status;
		GLint	m_Lenght;

		// Mandatory uniforms
		GLint m_ModelLoc;
		GLint m_ViewLoc;
		GLint m_ProjectionLoc;

		// Probably here, but not mandatory.
		GLint m_ObjectColorLoc;

		// All others "exotic" uniforms that may appear in the shader.
		std::unordered_map<std::string, GLint> m_UniformLocations;

	};
}
