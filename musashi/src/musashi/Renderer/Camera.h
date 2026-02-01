#pragma once

#include <glm/glm.hpp>

namespace musashi
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);	// near & far can be -1 - 1 for this 2D camera

		const glm::vec3& GetPosition() const { return m_Position; }				// the second const means not to modify the var it is called on
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetVPMatrix() const { return m_ViewProjectionMatrix; }

	private:
		void RecalculateViewMatrix();

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;		// for convenience

		glm::vec3 m_Position;
		float m_Rotation = 0.0f;	// 2D camera -> rotates around Z axis

	};
}