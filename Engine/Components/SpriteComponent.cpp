#include "pch.h"
#include "SpriteComponent.h"

namespace nc
{
	bool SpriteComponent::Create(void* data)
	{
		m_owner = static_cast<GameObject*>(data);
		return true;
	}

	void SpriteComponent::Destroy()
	{
	}

	void SpriteComponent::Read(const rapidjson::Value& value)
	{
		json::Get(value, "texture", m_textureName);
		json::Get(value, "origin", m_origin);
		json::Get(value, "rect", m_rect);
	}

	void SpriteComponent::Update()
	{
	}

	void SpriteComponent::Draw()
	{
		Texture* texture = m_owner->m_engine->GetSystem<nc::ResourceManager>()->Get<nc::Texture>(m_textureName, m_owner->m_engine->GetSystem<nc::Renderer>());
		texture->Draw(m_rect, m_owner->m_transform.position, m_owner->m_transform.angle, nc::Vector2{ 1, 1 } * m_owner->m_transform.scale);
	}

}
