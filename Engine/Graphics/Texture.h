#pragma once
#include "Resources/Resource.h"
#include "pch.h"
#include "Math/Vector2.h"

namespace nc
{
	class Texture : public Resource
	{
	public:
		bool Create(const std::string& name, void* renderer) override;
		void Destroy() override;

		void Draw(const Vector2& position, float angle = 0, const Vector2& scale = Vector2::one, const Vector2& origin = Vector2::zero, bool flip = false);
		void Draw(const SDL_Rect& source, const Vector2& position, float angle = 0, const Vector2& scale = Vector2::one, const Vector2& origin = Vector2::zero, bool flip = false);
	
		Vector2 GetSize() const;

	protected:
		SDL_Texture* m_texture{nullptr};
		SDL_Renderer* m_renderer{nullptr};
	};
}