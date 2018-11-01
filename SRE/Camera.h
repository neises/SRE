#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"

namespace SRE
{

	class Camera
	{
	public:
		glm::mat4 getViewMatrix() const;

		virtual void setPosition(const glm::vec3& position) {}
		virtual void rotate(float yaw, float pitch) {}  // in degrees
		virtual void move(const glm::vec3& offsetPos) {}

		const glm::vec3& getLook() const;
		const glm::vec3& getRight() const;
		const glm::vec3& getUp() const;
		const glm::vec3& getPosition() const;

		float getFOV() const { return mFOV; }
		void setFOV(float fov) { mFOV = fov; }		// in degrees

	protected:
		Camera();

		virtual void updateCameraVectors() {}

		glm::vec3 mPosition;
		glm::vec3 mTargetPos;
		glm::vec3 mLook;
		glm::vec3 mUp;
		glm::vec3 mRight;
		const glm::vec3 WORLD_UP;

		// Euler Angles (in radians)
		float mYaw;
		float mPitch;

		// Camera parameters
		float mFOV; // degrees
	};

	// fps camera
	class FPSCamera : public Camera
	{
	public:

		FPSCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), float yaw = glm::pi<float>(), float pitch = 0.0f); // (yaw) initial angle faces -Z

		virtual void setPosition(const glm::vec3& position);
		virtual void rotate(float yaw, float pitch);	// in degrees
		virtual void move(const glm::vec3& offsetPos);

	private:

		void updateCameraVectors();
	};
}
