#pragma once
#include "glm/glm.hpp"


namespace SRE
{
	class Transform
	{
	public:
		Transform();
		Transform(glm::vec3 _vPosition, glm::vec3 _vRotation = glm::vec3(0,0,0), glm::vec3 _vScale = glm::vec3(1,1,1));
		~Transform();

		void SetPosition(const glm::vec3& _vPosition);
		void SetEuler(const glm::vec3& _vEuler);
		void SetScale(const glm::vec3& _vScale);

		void SetMatrix(glm::mat4 _mMatrix);

		glm::vec3 GetPosition() const;
		glm::vec3 GetEuler() const;
		glm::vec3 GetScale() const;

		glm::mat4 GetMatrix() const;
		
	private:

		glm::vec3 m_vPosition;
		glm::vec3 m_vEuler;
		glm::vec3 m_vScale;

		glm::mat4 m_mMatrix;
	};
}
