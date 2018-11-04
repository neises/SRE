#pragma once
#include "glm/common.hpp"
#include "glm/gtx/transform.hpp"
#include <assert.h>
#include <memory>
#include <functional>

namespace SRE
{
	template<typename T>
	using unique_ptr_del = std::unique_ptr<T, std::function<void(T*)>>;

	template<class T>
	void SAFE_NEW(T*& obj)
	{
		assert(obj == nullptr);
		obj = new T();
	}

	template<class T>
	void SAFE_DELETE(T*& obj)
	{
		delete obj;
		obj = nullptr;
	}

	struct VertexFormatBasicTexture
	{
		glm::vec3 m_vPosition;
		glm::vec2 m_vTexture;
		VertexFormatBasicTexture(const glm::vec3& _vPosition, const glm::vec2& _vTexture)
		{
			m_vPosition = _vPosition;
			m_vTexture = _vTexture;
		}
	};

	struct VertexFormatBasic
	{
		glm::vec3 m_vPosition;
		glm::vec2 m_vTexture;
		glm::vec3 m_vNormal;
		VertexFormatBasic(const glm::vec3& _vPosition, const glm::vec2& _vTexture, const glm::vec3& _vNormal)
		{
			m_vPosition = _vPosition;
			m_vTexture = _vTexture;
			m_vNormal = _vNormal;
		}
	};

	class ColorHelper
	{

	public:
		static const glm::vec4 Black;
		static const glm::vec4 White;
		static const glm::vec4 Red;
		static const glm::vec4 Green;
		static const glm::vec4 Blue;
		static const glm::vec4 Yellow;
		static const glm::vec4 BlueGreen;
		static const glm::vec4 Purple;
		static const glm::vec4 CornflowerBlue;
		static const glm::vec4 Wheat;
		static const glm::vec4 LightGray;

	private:

	};
	class AppData
	{
	public:

		static const int HEIGHT = 960;
		static const int WIDTH = 1280;
		static constexpr const char* AppCaption = "Test MiniGL App";

	};

	struct Context
	{
	public:
		glm::mat4 mView;
		glm::mat4 mProjection;
		float fDelta;
	};
}