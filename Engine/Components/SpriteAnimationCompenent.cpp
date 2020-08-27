#include "pch.h"
#include "SpriteAnimationCompenent.h"
#include "Graphics/Texture.h"

namespace nc
{
	void SpriteAnimationComponent::Create(void* data)
	{
		m_owner = static_cast<GameObject*>(data);
	}

	void SpriteAnimationComponent::Destroy()
	{
	}

	void SpriteAnimationComponent::Read(const rapidjson::Value& value)
	{
		SpriteComponent::Read(value);

		json::Get(value, "numX", m_numX);
		json::Get(value, "numY", m_numY);
		json::Get(value, "numFrames", m_numFrames);
		json::Get(value, "fps", m_fps);

		m_frameRate = 1.0f / m_fps;
	}

	void SpriteAnimationComponent::Update()
	{
		m_frameTimer += m_owner->m_enigne->GetTime().DeltaTimer();
		if (m_frameTimer >= m_frameRate)
		{
			m_frameTimer = 0;
			m_frame++;
			if (m_frame >= m_numFrames)
			{
				m_frame = 0;
			}
		}

		Texture* texture = m_texture = m_owner->m_enigne->GetSystem<nc::ResourceManager>()->Get<nc::Texture>(m_textureName, m_owner->m_enigne->GetSystem<nc::Renderer>());
		Vector2 textureSize = texture->GetSize();

		Vector2 cellCount{ m_numX, m_numY };
		Vector2 cellSize = textureSize / cellCount;

		m_rect.x = static_cast<int>((m_frame % m_numX) * cellSize.x);
		m_rect.y = static_cast<int>((m_frame / m_numX) * cellSize.y);
		m_rect.w = static_cast<int>(cellSize.x);
		m_rect.h = static_cast<int>(cellSize.y);
	}
}
