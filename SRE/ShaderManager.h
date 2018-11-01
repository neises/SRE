#pragma once

#include <string>
#include <unordered_map>
#include "ShaderProgram.h"

namespace SRE
{
	using namespace SRE;
	class ShaderManager
	{
	public:
		ShaderManager();
		ShaderManager(const ShaderManager& other) = delete;
		ShaderManager& operator=(const ShaderManager& other) = delete;
		~ShaderManager();

		static ShaderManager* GetShaderManagerInstance();

		ShaderProgram* GetShaderProgram(const std::string& _sVertex_file_path, const std::string& _sFragment_file_path);

	private:
		std::unordered_map<std::string, ShaderProgram*> m_ShaderPrograms;
		static ShaderManager* m_pShaderManagerInstance;
	};

}