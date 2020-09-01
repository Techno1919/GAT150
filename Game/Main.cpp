#include "pch.h"
#include "Graphics/Texture.h"
#include "Engine.h"
#include "Objects/GameObject.h"
#include "Core/Json.h"
#include "Components/PlayerComponent.h"
#include "Components/EnemyComponent.h"
#include "Objects/ObjectFactory.h"
#include "Objects/Scene.h"
#include "TileMap.h"

nc::Engine engine;
nc::Scene scene;

int main(int, char**)
{

	engine.Startup();

	nc::ObjectFactory::Instance().Initialize();
	nc::ObjectFactory::Instance().Register("PlayerComponent", new nc::Creator<nc::PlayerComponent, nc::Object>);
	nc::ObjectFactory::Instance().Register("EnemyComponent", new nc::Creator<nc::EnemyComponent, nc::Object>);

	rapidjson::Document document;
	nc::json::Load("Scene.txt", document);

	scene.Create(&engine);
	scene.Read(document);

	rapidjson::Document document1;
	nc::TileMap tileMap;
	nc::json::Load("tileMap.txt", document1);
	tileMap.Read(document1);
	tileMap.Create(&scene);

	/*for (size_t i = 0; i < 10; i++)
	{
		nc::GameObject* gameobject = nc::ObjectFactory::Instance().Create<nc::GameObject>("ProtoBox");
		gameobject->m_transform.position = { nc::random(0, 800), nc::random(0, 400) };
		gameobject->m_transform.angle = nc::random(0, 360);
		scene.AddGameObject(gameobject);
	}*/

	/*for (size_t i = 0; i < 10; i++)
	{
		nc::GameObject* gameobject = nc::ObjectFactory::Instance().Create<nc::GameObject>("ProtoCoin");
		gameobject->m_transform.position = { nc::random(0, 800), nc::random(400, 600) };
		scene.AddGameObject(gameobject);
	}*/

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

		engine.GetSystem<nc::Renderer>()->BeginFrame();

		//draw
		//background->Draw({ 0, 0 }, { 1, 1 }, 0);
		scene.Draw();

		if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eButtonState::PRESSED)
		{
			quit = true;
		}
		if (scene.GetGameState() == nc::gameState::PlayerWin || scene.GetGameState() == nc::gameState::PlayerDead)
		{
			quit = true;
		}

		engine.GetSystem<nc::Renderer>()->EndFrame();
	}

	// wait for keyboard enter to exit
	std::getchar();

	engine.Shutdown();
	scene.Destroy();

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