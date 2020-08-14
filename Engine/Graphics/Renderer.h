#pragma once
#include "Core/System.h"
#include <SDL.h>

namespace nc
{
	class Renderer : public System
	{
	public:
		virtual bool Startup() override;
		virtual void Shutdown() override;
		virtual void Update() override;

		bool Create(const std::string name, int width, int height);
		void BeginFrame();
		void EndFrame();

		friend class Texture;

	protected:
		SDL_Window* m_window;
		SDL_Renderer* m_renderer;
	};
}