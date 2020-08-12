#include "pch.h"
#include "Graphics/Texture.h"
#include "Graphics/Renderer.h"
#include "Resources/ResourceManager.h"
#include "Input/InputSystem.h"
#include "Core/Timer.h"
#include "Math/MathStuff.h"

nc::ResourceManager resourceManager;
nc::Renderer renderer;
nc::InputSystem inputSystem;
nc::FrameTimer timer;

int main(int, char**)
{
	/*nc::Timer timer;
	for (size_t i = 0; i < 100; i++) { std::sqrt(rand() % 100); }
	std::cout << timer.ElapsedSeconds() << std::endl;*/

	renderer.Startup();
	inputSystem.Startup();
	renderer.Create("GAT150", 800, 600);

	// create textures
	int width = 128;
	int height = 128;

	
	// texture
	nc::Texture* car = resourceManager.Get<nc::Texture>("cars.png", &renderer);
	nc::Texture* background = resourceManager.Get<nc::Texture>("background.png", &renderer);

	float angle{ 0 };
	nc::Vector2 position{ 400, 300 };
	nc::Vector2 velocity;

	SDL_Event event;
	bool quit = false;
	while (!quit)
	{
		inputSystem.Update();
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}
		
		//update

		timer.Tick();

		//draw
		renderer.BeginFrame();
	
		// render sprite
		background->Draw({ 0, 0 }, { 1, 1 }, 0);
		car->Draw({ 126, 120, 52, 102 }, position, { 1, 1 }, angle);

		if (inputSystem.GetButtonState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eButtonState::PRESSED)
		{
			quit = true;
		}
		if (inputSystem.GetButtonState(SDL_SCANCODE_LEFT) == nc::InputSystem::eButtonState::HELD)
		{
			position.x = position.x - 200.0f * timer.DeltaTime();
		}
		if (inputSystem.GetButtonState(SDL_SCANCODE_RIGHT) == nc::InputSystem::eButtonState::HELD)
		{
			position.x = position.x + 200.0f * timer.DeltaTime();
		}
		if (inputSystem.GetButtonState(SDL_SCANCODE_UP) == nc::InputSystem::eButtonState::HELD)
		{
			position.y = position.y - 200.0f * timer.DeltaTime();
		}
		if (inputSystem.GetButtonState(SDL_SCANCODE_DOWN) == nc::InputSystem::eButtonState::HELD)
		{
			position.y = position.y + 200.0f * timer.DeltaTime();
		}

		
		nc::Vector2 force{ 0, 0 };
		if (inputSystem.GetButtonState(SDL_SCANCODE_W) == nc::InputSystem::eButtonState::HELD)
		{
			force = nc::Vector2::forward * 1000.0f;
		}
		force = nc::Vector2::Rotate(force, nc::DegreesToRadians(angle));

		// physics
		velocity += force * timer.DeltaTime();
		velocity *= 0.98f;
		position += velocity * timer.DeltaTime();

		// player controller
		if (inputSystem.GetButtonState(SDL_SCANCODE_A) == nc::InputSystem::eButtonState::HELD)
		{
			angle = angle - 200.0f * timer.DeltaTime();
		}
		if (inputSystem.GetButtonState(SDL_SCANCODE_D) == nc::InputSystem::eButtonState::HELD)
		{
			angle = angle + 200.0f * timer.DeltaTime();
		}

		renderer.EndFrame();
	}

	// wait for keyboard enter to exit
	std::getchar();

	renderer.Shutdown();
	inputSystem.Shutdown();
	SDL_Quit();

	return 0;
}
