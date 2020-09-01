#include "pch.h"
#include "EnemyComponent.h"
#include "Objects/GameObject.h"
#include "Objects/Scene.h"
#include "Components/PhysicsComponent.h"

namespace nc
{
	bool EnemyComponent::Create(void* data)
	{
		m_owner = static_cast<GameObject*>(data);
		return true;
	}

	void EnemyComponent::Destroy()
	{
	}

	void EnemyComponent::Update()
	{
		GameObject* player = m_owner->m_scene->Find("Player");
		if (player)
		{
			Vector2 direction = player->m_transform.position - m_owner->m_transform.position;
			Vector2 force = direction.Normalized() * 5.0f;

			PhysicsComponent* physicsComponent = m_owner->GetComponent<PhysicsComponent>();
			physicsComponent->ApplyForce(force);
		}
	}

}
