#include "pch.h"
#include "PlayerComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/RigidBodyComponent.h"


namespace nc
{
	bool PlayerComponent::Create(void* data)
	{
		m_owner = static_cast<GameObject*>(data);
		return true;
	}

	void PlayerComponent::Destroy()
	{
	}

	void PlayerComponent::Update()
	{
		auto contacts = m_owner->GetContactsWithTag("Floor");
		bool onGround = !contacts.empty();

		// player controller
		nc::Vector2 force{ 0, 0 };
		if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_A) == nc::InputSystem::eButtonState::HELD)
		{
			force.x = -100;
		}
		if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_D) == nc::InputSystem::eButtonState::HELD)
		{
			force.x = 100;
		}
		if (onGround && m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_W) == nc::InputSystem::eButtonState::PRESSED)
		{
			force.y = -1500;
			AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>();
			if (audioComponent)
			{
				audioComponent->Play();
			}

		}

		// apply force
		RigidBodyComponent* component = m_owner->GetComponent<nc::RigidBodyComponent>();
		if (component)
		{
			component->ApplyForce(force);
		}

		// check for coin contact
		auto coinContacts = m_owner->GetContactsWithTag("Pickup");
		for (auto contact : coinContacts)
		{
			contact->m_flags[GameObject::eFlags::DESTROY] = true;
		}

	}

	void PlayerComponent::CollisionEvent(GameObject* gameObject)
	{
	}

}
