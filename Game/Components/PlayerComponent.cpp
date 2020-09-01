#include "pch.h"
#include "PlayerComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/RigidBodyComponent.h"
#include "Core/EventManager.h"
#include "Objects/Scene.h"

namespace nc
{
	bool PlayerComponent::Create(void* data)
	{
		m_owner = static_cast<GameObject*>(data);

		EventManager::Instance().Subscribe("CollisionEnter", std::bind(&PlayerComponent::OnCollisionEnter, this, std::placeholders::_1), m_owner);
		EventManager::Instance().Subscribe("CollisionExit", std::bind(&PlayerComponent::OnCollisionExit, this, std::placeholders::_1), m_owner);

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
			audioComponent->SetSoundName("jump.wav");
			audioComponent->Play();
		}

		// apply force
		RigidBodyComponent* component = m_owner->GetComponent<nc::RigidBodyComponent>();
		if (component)
		{
			component->ApplyForce(force);

			Vector2 velocity = component->GetVelocity();

			SpriteComponent* spriteComponent = m_owner->GetComponent<SpriteComponent>();
			if (velocity.x <= -0.5f) spriteComponent->Flip();
			if (velocity.x >= -0.5f) spriteComponent->Flip(false);


		}
	}

	void PlayerComponent::OnCollisionEnter(const Event& event)
	{
		GameObject* gameObject = dynamic_cast<GameObject*>(event.sender);
		AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>();

		if (gameObject->m_tag == "Enemy")
		{
			audioComponent->SetSoundName("grunt.wav");
			audioComponent->Play();

			m_owner->m_scene->SetGameState(gameState::PlayerDead);
			m_owner->m_flags[GameObject::eFlags::DESTROY] = true;

			Event event;
			event.type = "PlayerDead";
			EventManager::Instance().Notify(event);
			
		}

		if (gameObject->m_tag == "Pickup")
		{
			m_coins++;
			if (m_coins >= 9)
			{
				m_owner->m_scene->SetGameState(gameState::GameWin);
			}
			gameObject->m_flags[GameObject::eFlags::DESTROY] = true;
			audioComponent->SetSoundName("coin.wav");
			audioComponent->Play();
			
		}

		std::cout << "collision enter: " << gameObject->m_name << std::endl;
	}

	void PlayerComponent::OnCollisionExit(const Event& event)
	{
		GameObject* gameObject = dynamic_cast<GameObject*>(event.sender);

		std::cout << "collision exit: " << gameObject->m_name << std::endl;
	}

}
