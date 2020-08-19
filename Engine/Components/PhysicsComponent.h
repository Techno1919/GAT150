#pragma once
#include "Component.h"
#include "Math/Vector2.h"

namespace nc
{
	class PhysicsComponent : public Component
	{
	public:
		virtual bool Create(void* data = nullptr) override;
		virtual void Destroy() override;

		virtual void Update() override;

		void ApplyForce(const nc::Vector2& force) { m_force = force; }

	protected:
		nc::Vector2 m_velocity;
		nc::Vector2 m_force;
		float m_drag{ 1 };
	};
}