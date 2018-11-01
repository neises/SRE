#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "Transform.h"


namespace SRE
{
	using namespace SRE;
	Transform::Transform() : m_vScale(glm::vec3(1, 1, 1)),m_vPosition(glm::vec3(0,0,0)), m_vEuler(glm::vec3(0,0,0))
	{

	}

	Transform::Transform(glm::vec3 _vPosition, glm::vec3 _vRotation /*= glm::vec3(0,0,0)*/, glm::vec3 _vScale /*= glm::vec3(1,1,1)*/)
		: m_vPosition(_vPosition), m_vEuler(_vRotation), m_vScale(_vScale)
	{

	}

	Transform::~Transform()
	{
	}

	void Transform::SetPosition(const glm::vec3& _vPosition)
	{
		m_vPosition = _vPosition;
	}

	void Transform::SetEuler(const glm::vec3 & _vEuler)
	{
		m_vEuler = _vEuler;
	}

	void Transform::SetScale(const glm::vec3 & _vScale)
	{
		m_vScale = _vScale;
	}

	void Transform::SetMatrix(glm::mat4 _mMatrix)
	{
		m_mMatrix = _mMatrix;
	}

	glm::vec3 Transform::GetPosition() const
	{
		return m_vPosition;
	}

	glm::vec3 Transform::GetEuler() const
	{
		return m_vEuler;
	}

	glm::vec3 Transform::GetScale() const
	{
		return m_vScale;
	}

	glm::mat4 Transform::GetMatrix() const
	{
		glm::mat4 mat = glm::translate(glm::mat4(1.0f), m_vPosition);
		mat = mat * glm::eulerAngleYXZ(m_vEuler.y, m_vEuler.x, m_vEuler.z);
		mat = glm::scale(mat, m_vScale);

		return mat;
	}

}