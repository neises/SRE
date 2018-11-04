#include "SplineComponent.h"
#include "Transform.h"
#include "Utils.h"
#include "ShaderProgram.h"


namespace SRE
{
	using namespace SRE;

	SplineComponent::SplineComponent() :
		m_iIndex(1)
		, m_fSpeed(1)
		, m_fIntern(0.0f)
		, m_bIsPaused(true)
	{

	}

	SplineComponent::~SplineComponent()
	{

	}

	void SplineComponent::SetSpline(const Spline& _Spline)
	{
		m_SplinePath = _Spline;
	}

	void SplineComponent::SetSpeed(float _fSpeed)
	{
		m_fSpeed = _fSpeed;
	}

	void SplineComponent::SetPaused(bool _bShouldPause)
	{
		m_bIsPaused = _bShouldPause;
	}

	void SplineComponent::Restart()
	{
		m_iIndex = 1;
		m_fIntern = 0.0f;
		m_bIsPaused = false;
	}

	void SplineComponent::Initialize(const Context& _Context, Transform* _pTransform)
	{

	}

	void SplineComponent::Update(const Context& _Context, Transform* _pTransform)
	{
		if (!m_bIsPaused)
		{
			m_fIntern += m_fSpeed * _Context.fDelta;

			if (m_fIntern >= 1.0f)
			{
				
				if (m_iIndex < m_SplinePath.GetNumControlPoints() - 3)
				{
					m_iIndex++;
					m_fIntern = m_fIntern - 1.0f;
				}
				else
				{
					
					m_bIsPaused = true;
				}
			}
		}

		
		glm::vec3 currentPosition = m_SplinePath.ComputePosition(m_iIndex, m_iIndex);

		_pTransform->SetPosition(currentPosition);
	}


	void SRE::SplineComponent::Render(const Context& _Context, Transform* _pTransform, ShaderProgram* _pShader)
	{
		
	}


	glm::vec3 SRE::Spline::ComputePosition(size_t _iStartIndex, float _ft) const
	{
		if (_iStartIndex >= m_aControlPoints.size())
		{
			return m_aControlPoints.back();
		}
		else if (_iStartIndex == 0)
		{
			return m_aControlPoints[_iStartIndex];
		}
		else if (_iStartIndex + 2 >= m_aControlPoints.size())
		{
			return m_aControlPoints[_iStartIndex];
		}

		// Get p0 through p3
		glm::vec3 p0 = m_aControlPoints[_iStartIndex - 1];
		glm::vec3 p1 = m_aControlPoints[_iStartIndex];
		glm::vec3 p2 = m_aControlPoints[_iStartIndex + 1];
		glm::vec3 p3 = m_aControlPoints[_iStartIndex + 2];
		// Compute position according to Catmull-Rom equation
		glm::vec3 position = 0.5f * ((2.0f * p1) + (-1.0f * p0 + p2) * t +
			(2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3) * t * t +
			(-1.0f * p0 + 3.0f * p1 - 3.0f * p2 + p3) * t * t * t);
		return position;
	}

	size_t SRE::Spline::GetNumControlPoints() const
	{

		m_aControlPoints.size();
	}
}




