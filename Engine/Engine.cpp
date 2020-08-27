#include "pch.h"
#include "Engine.h"

namespace nc
{
	bool Engine::Startup()
	{
		srand(static_cast<unsigned int>(time(nullptr)));

		m_system.push_back(new Renderer);
		m_system.push_back(new InputSystem);
		m_system.push_back(new ResourceManager);
		m_system.push_back(new PhysicsSystem);
		m_system.push_back(new AudioSystem);

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