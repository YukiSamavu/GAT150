#include "pch.h"
#include "Engine.h"

namespace nc
{
	bool Engine::Startup()
	{
		m_system.push_back(new Renderer);
		m_system.push_back(new InputSystem);
		m_system.push_back(new ResourceManager);

		for (auto system : m_system)
		{
			system->Startup();
		}

		//create window
		GetSystem<Renderer>()->Create("Yuki's Pixel Game", 800, 600);

		return true;
	}
	void Engine::Shutdown()
	{
		for (auto system : m_system)
		{
			system->Shutdown();
			delete system;
		}
		m_system.clear();

		SDL_Quit();
	}
	void Engine::Update()
	{
		m_timer.Tick();
		for (auto system : m_system)
		{
			system->Update();
		}
	}
}