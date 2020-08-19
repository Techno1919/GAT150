#include "pch.h"
#include "Graphics/Texture.h"
#include "Engine.h"
#include "Objects/GameObject.h"
#include "Core/Json.h"
#include "Components/PlayerComponent.h"
#include "Objects/ObjectFactory.h"

nc::Engine engine;
//nc::ObjectFactory objectFactory;

int main(int, char**)
{
	rapidjson::Document document;

	engine.Startup();

	nc::ObjectFactory::Instance().Initialize();
	nc::ObjectFactory::Instance().Register("PlayerComponent", nc::Object::Instantiate<nc::PlayerComponent>);

	nc::GameObject* player = nc::ObjectFactory::Instance().Create<nc::GameObject>("GameObject");

	player->Create(&engine);
	nc::json::Load("player.txt", document);
	player->Read(document);

	nc::Component* component = nc::ObjectFactory::Instance().Create<nc::Component>("PhysicsComponent");
	component->Create(player);
	player->AddComponent(component);

	component = nc::ObjectFactory::Instance().Create<nc::Component>("SpriteComponent");
	component->Create(player);
	nc::json::Load("sprite.txt", document);
	component->Read(document);
	player->AddComponent(component);

	component = nc::ObjectFactory::Instance().Create<nc::Component>("PlayerComponent");
	component->Create(player);
	player->AddComponent(component);

	// texture
	nc::Texture* background = engine.GetSystem<nc::ResourceManager>()->Get<nc::Texture>("background.png", engine.GetSystem<nc::Renderer>());


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
		player->Update();

		engine.GetSystem<nc::Renderer>()->BeginFrame();

		//draw
		background->Draw({ 0, 0 }, { 1, 1 }, 0);
		player->Draw();

		if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eButtonState::PRESSED)
		{
			quit = true;
		}

		engine.GetSystem<nc::Renderer>()->EndFrame();
	}

	// wait for keyboard enter to exit
	std::getchar();

	engine.Shutdown();

	return 0;
}

/*

	std::string str;
	nc::json::Get(document, "string", str);
	std::cout << str << std::endl;

	bool b;
	nc::json::Get(document, "boolean", b);
	std::cout << b << std::endl;

	int i1;
	nc::json::Get(document, "integer1", i1);
	std::cout << i1 << std::endl;

	int i2;
	nc::json::Get(document, "integer2", i2);
	std::cout << i2 << std::endl;

	float f;
	nc::json::Get(document, "float", f);
	std::cout << f << std::endl;

	nc::Vector2 v2;
	nc::json::Get(document, "vector2", v2);
	std::cout << v2 << std::endl;

	nc::Color color;
	nc::json::Get(document, "color", color);
	std::cout << color << std::endl;*/