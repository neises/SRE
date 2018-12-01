#pragma once
#include "BaseComponent.h"
#include <vector>
#include "Utils.h"


namespace SRE
{
	class Transform;
	class Mesh;
	class Material;
	class Shader;
	class ShaderProgram;
	class Model;
}

namespace SRE
{
	typedef struct Spline
	{
		// constrol points
		// needs n+2 points and n is the number 
		// of points in the segment
		std::vector<glm::vec3> m_aControlPoints;

		glm::vec3 ComputePosition(size_t _iStartIndex, float _ft) const;

		size_t GetNumControlPoints() const;

	}t_Spline;

	class SplineComponent : public SRE::BaseComponent
	{
	public:
		SplineComponent();
		~SplineComponent();

		void SetSpline(const t_Spline& _Spline);
		void SetSpeed(float _fSpeed);
		void SetPaused(bool _bShouldPause);

		void Restart();

	protected:
		virtual void Initialize(const Context& _Context, Transform* _pTransform) override;
		virtual void Update(const Context& _Context, Transform* _pTransform) override;
		virtual void Render(const Context& _Context, Transform* _pTransform, ShaderProgram* _pShader) override;
	private:

		t_Spline m_SplinePath;
		bool m_bIsPaused;
		size_t m_iIndex;
		float m_fIntern;
		float m_fSpeed;

	};
}
