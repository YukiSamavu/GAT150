#include "pch.h"
#include "Graphics/Texture.h"
#include "Objects/GameObject.h"
#include "Core/Json.h"
#include "Component/PlayerComponent.h"
#include "Components/EnemyComponent.h"
#include "Core/Factory.h"
#include "Objects/ObjectFactory.h"
#include "Objects/Scene.h"
#include "TileMap.h"
#include "Core/EventManager.h"

nc::Engine engine;
nc::Scene scene;

void OnPlayerDead(const nc::Event& event)
{
	int* pdata = static_cast<int*>(event.data);

	std::cout << "Player Dead : " << *pdata << std::endl ;
}

int main(int, char**)
{
	engine.Startup();
	
	scene.Create(&engine);

	nc::ObjectFactory::Instance().Initialize();
	nc::ObjectFactory::Instance().Register("PlayerComponent", new nc::Creator<nc::PlayerComponent, nc::Object>);
	nc::ObjectFactory::Instance().Register("EnemyComponent", new nc::Creator<nc::EnemyComponent, nc::Object>);

	nc::EventManager::Instance().Subscribe("PlayerDead", &OnPlayerDead);

	rapidjson::Document document;
	nc::json::Load("scene.txt", document);
	scene.Read(document);

	nc::json::Load("tilemap.txt", document);
	nc::TileMap tilemap;
	tilemap.Read(document);
	tilemap.Create(&scene);

	nc::json::Load("Texture/sheet1.png", document);
	tilemap.Read(document);
	tilemap.Create(&scene);

	nc::Vector2 velocity{ 0,0 };

	SDL_Event event;
	bool quit = false;
	while (!quit)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}
		//update
		engine.Update();
		scene.Update();

		if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eButtonState::PRESSED)
		{
			quit = true;
		}

		//draw
		engine.GetSystem<nc::Renderer>()->BeginFrame();
		
		//player->Draw();
		scene.Draw();

		engine.GetSystem<nc::Renderer>()->EndFrame();
	}

	scene.Destroy();
	engine.Shutdown();

	IMG_Quit();

	return 0;
}

