#include "ShaderManager.h"

namespace SRE
{
	using namespace SRE;
	ShaderManager* ShaderManager::m_pShaderManagerInstance = 0;

	ShaderManager::ShaderManager()
	{

	}

	ShaderManager::~ShaderManager()
	{
		for (auto& entry : m_ShaderPrograms)
		{
			delete entry.second;
		}
	}


	ShaderManager* ShaderManager::GetShaderManagerInstance()
	{
		if (m_pShaderManagerInstance == nullptr)
		{
			m_pShaderManagerInstance = new ShaderManager();

		}
		return m_pShaderManagerInstance;
	}

	ShaderProgram* ShaderManager::GetShaderProgram(const std::string& _sVertex_file_path, const std::string& _sFragment_file_path, const std::string& _sProgramName /*= std::string()*/)
	{
		std::string name = _sVertex_file_path + _sFragment_file_path;

		if (!_sProgramName.empty())
		{
			name = _sProgramName;
		}

		auto lb = m_ShaderPrograms.lower_bound(name);

		if (lb != m_ShaderPrograms.end() && !(m_ShaderPrograms.key_comp()(name, lb->first)))
		{
			return lb->second;
		}
		else
		{
			auto shaderProgram = new ShaderProgram(_sVertex_file_path, _sFragment_file_path);
			m_ShaderPrograms.insert(lb, { name, shaderProgram });
			return shaderProgram;
		}
	}

	SRE::ShaderProgram* ShaderManager::GetShaderProgrambyName(const std::string& _sProgramName)
	{
		return m_ShaderPrograms[_sProgramName];
	}

}