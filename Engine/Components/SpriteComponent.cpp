#include "pch.h"
#include "SpriteComponent.h"
#include "Graphics/Texture.h"


namespace nc
{
	void SpriteComponent::Create(void* data)
	{
		m_texture = m_owner->m_enigne->GetSystem<nc::ResourceManager>()->Get<nc::Texture>("cars.png", m_owner->m_enigne->GetSystem<nc::Renderer>());
	}

	void SpriteComponent::Destroy()
	{
	}

	void SpriteComponent::Update()
	{
	}

	void SpriteComponent::Draw()
	{
		//{x,y,w,h}
		m_texture->Draw({ 125, 440, 64, 110 }, m_owner->m_transform.position, { 1,1 }, m_owner->m_transform.angle);
	}
}
