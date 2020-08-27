#include "pch.h"
#include "Graphics/Texture.h"
#include "Objects/GameObject.h"
#include "Core/Json.h"
#include "Component/PlayerComponent.h"
#include "Core/Factory.h"
#include "Objects/ObjectFactory.h"
#include "Objects/Scene.h"

nc::Engine engine;
nc::Scene scene;

//Make A demo-durby that updates when a car is destroyed explode and make car look more damaged

int main(int, char**)
{
	engine.Startup();
	
	scene.Create(&engine);

	nc::ObjectFactory::Instance().Initialize();
	nc::ObjectFactory::Instance().Register("PlayerComponent", new nc::Creator<nc::PlayerComponent, nc::Object>);

	rapidjson::Document document;
	nc::json::Load("scene.txt", document);
	scene.Read(document);
	
	for (size_t i = 0; i < 10; i++)
	{
		nc::GameObject* gameObject = nc::ObjectFactory::Instance().Create<nc::GameObject>("ProtoCoin");
		gameObject->m_transform.position = { nc::random(0, 800), nc::random(350, 450) };
		//gameObject->m_transform.angle = nc::random(0, 360);

		scene.AddGameObject(gameObject);
	}

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

