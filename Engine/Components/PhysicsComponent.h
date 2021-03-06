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
		virtual Object* Clone() override { return new PhysicsComponent{ *this }; }

		virtual void Update() override;

		virtual void ApplyForce(const nc::Vector2& force) { m_force = force; }
		virtual Vector2& GetVelocity() { return m_velocity; }

	protected:
		nc::Vector2 m_velocity;
		nc::Vector2 m_force;
		float m_drag{ 1 };
	};
}