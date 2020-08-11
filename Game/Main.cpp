#include "pch.h"
#include "Graphics/Texture.h"
#include "Resources/ResourceManager.h"
#include "Graphics/Renderer.h"
#include "Input/InputSystem.h"
#include "Core/Timer.h"
#include "Math/Math.h"

nc::InputSystem inputSystem;
nc::ResourceManager resourceManager;
nc::Renderer renderer;
nc::FrameTimer timer;

int main(int, char**)
{
	/*nc::Timer timer;
	for (size_t i = 0; i < 1000; i++) { std::sqrt(rand() % 100); }

	std::cout << timer.ElapsedTicks() << std::endl;
	std::cout << timer.ElapsedSeconds() << std::endl;*/

	inputSystem.Startup();
	renderer.Startup();
	resourceManager.Startup();

	renderer.Create("Yuki's Pixel Game", 800, 600);

	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	nc::Texture* background = resourceManager.Get<nc::Texture>("background.png", &renderer);
	nc::Texture* car = resourceManager.Get<nc::Texture>("cars.png", &renderer);

	float angle{ 0 };
	nc::Vector2 position{ 400,300 };
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
		timer.Tick();

		quit = (inputSystem.GetButtonState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eButtonState::PRESSED);

		//player controller
		if (inputSystem.GetButtonState(SDL_SCANCODE_A) == nc::InputSystem::eButtonState::HELD)
		{
			angle = angle - 200.0f * timer.DeltaTimer();
		}
		if (inputSystem.GetButtonState(SDL_SCANCODE_D) == nc::InputSystem::eButtonState::HELD)
		{
			angle = angle +200.0f * timer.DeltaTimer();
		}
		nc::Vector2 force{ 0,0 };
		if (inputSystem.GetButtonState(SDL_SCANCODE_W) == nc::InputSystem::eButtonState::HELD)
		{
			force = nc::Vector2::forward * 1000.0f;
		}
		if (inputSystem.GetButtonState(SDL_SCANCODE_S) == nc::InputSystem::eButtonState::HELD)
		{
			force = nc::Vector2::forward * -1000.0f;
		}

		inputSystem.Update();
		resourceManager.Update();

		//physics
		force = nc::Vector2::Rotate(force, nc::DegreeToRadians(angle));
		velocity = velocity + force * timer.DeltaTimer();
		velocity = velocity * 0.95f;
		position = position + velocity * timer.DeltaTimer();

		//draw
		renderer.BeginFrame();

		background->Draw({0, 0});
		//{x,y,w,h}
		car->Draw({ 125, 440, 60, 110 }, position, {1,1}, angle);

		renderer.EndFrame();
	}

	inputSystem.Shutdown();
	resourceManager.Shutdown();

	IMG_Quit();
	SDL_Quit();

	return 0;
}

