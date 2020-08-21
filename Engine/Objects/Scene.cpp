#include "pch.h"
#include "Scene.h"
#include "GameObject.h"
#include "ObjectFactory.h"

namespace nc
{
	bool Scene::Create(void* data)
	{
		m_engine = static_cast<Engine*>(data);
		return true;
	}

	void Scene::Destroy()
	{
		RemoveAllGameObjects();
	}

	void Scene::Read(const rapidjson::Value& value)
	{
		const rapidjson::Value& objectsValue = value["GameObjects"];
		if (objectsValue.IsArray())
		{
			ReadGameObjects(objectsValue);
		}

	}

	void Scene::Update()
	{
		// iterate through the actors and call Update on each actor
		for (auto gameObject : m_gameObjects)
		{
			gameObject->Update();
		}
		// update
	}

	void Scene::Draw()
	{
		// iterate through the actors and call Draw on each actor
		for (auto gameObject : m_gameObjects)
		{
			gameObject->Draw();
		}
		// draw
	}

	GameObject* Scene::Find(const std::string& name)
	{
		for (auto gameObject : m_gameObjects)
		{
			if (gameObject->m_name == name)
			{
				return gameObject;
			}
		}

		return nullptr;
	}

	void Scene::AddGameObject(GameObject* gameObject)
	{
		m_gameObjects.push_back(gameObject);
		// push back gameObject
	}

	void Scene::RemoveGameObject(GameObject* gameObject)
	{
		auto iter = std::find(m_gameObjects.begin(), m_gameObjects.end(), gameObject);
		if (iter != m_gameObjects.end())
		{
			// destroy (*iter)->
			(*iter)->Destroy();
			// delete 
			delete (*iter);
			// erase iter from m_gameObjects
			m_gameObjects.erase(iter);
		}
	}

	void Scene::RemoveAllGameObjects()
	{
		for (GameObject* gameObject : m_gameObjects)
		{
			// destroy
			gameObject->Destroy();
			// delete
			delete gameObject;
		}
		// clear game objects
		m_gameObjects.clear();
	}
	void Scene::ReadGameObjects(const rapidjson::Value& value)
	{
		for (rapidjson::SizeType i = 0; i < value.Size(); i++)
		{
			const rapidjson::Value& objectValue = value[i];
			if (objectValue.IsObject())
			{
				std::string typeName;
				// read game object “type” name from json (Get)
				json::Get(objectValue, "type", typeName);
				GameObject* gameObject = ObjectFactory::Instance().Create<GameObject>(typeName);// create game object from object factory
					if (gameObject)
					{
						// call game object create, pass in m_engine
						gameObject->Create(m_engine);
						// call game object read
						gameObject->Read(objectValue);
						// add game object to scene
						AddGameObject(gameObject);
					}
			}
		}
	}

}